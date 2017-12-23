#pragma once
#include "stdafx.h"
#include "Connection.h"
#include "DataStructs.h"
//Connection::Connection() {}

Connection::Connection(std::unique_ptr<AvailableConnection> availableConnection) :
_e_newInfo(std::make_shared<HANDLE>(CreateEvent(NULL, TRUE, FALSE, NULL))),
_e_destroyed(std::make_shared<HANDLE>(CreateEvent(NULL, TRUE, FALSE, NULL))),
errorStatus(NotDefined),
_converterMessageList({}),
_controllerMessageList({})
{
	if (
			availableConnection->converterPorts == nullptr ||
			availableConnection->converterInfo == nullptr ||
			!availableConnection->portType
		)
		throw ConstructError(std::string("Bad initialize data!"));

	_data = std::move(availableConnection);

	commonConverterSettings = { 0 };
	commonConverterSettings.nNMask = ZG_NF_CVT_CTR_EXIST | ZG_CVTNF_CONNECTION_CHANGE | ZG_NF_CVT_CTR_DBL_CHECK | ZG_NF_CVT_ERROR;
	commonConverterSettings.nScanCtrsPeriod = 2000;

	commonControllerSettings = { 0 };
	commonControllerSettings.nNMask = ZG_NF_CTR_NEW_EVENT | ZG_NF_CTR_CLOCK | ZG_NF_CTR_ADDR_CHANGE | ZG_NF_CTR_KEY_TOP | ZG_N_CTR_ERROR;
	commonControllerSettings.nCheckStatePeriod = 1500;
	commonControllerSettings.nClockOffs = 30;

	temp_controllerEvents.resize(5);
}

Connection::~Connection()
{// TODO log trace
	SetEvent(*_e_destroyed);
	try {
		tryCloseConverter();
	}
	catch (std::exception& error) {
		std::cout << error.what();
	}
}

void Connection::setNewConnactionInfo(std::unique_ptr<AvailableConnection> pointer) { // Нужна проверка
	_data = std::move(pointer);
	if (!initialConnections());
		// TODO Throw connection
	// TODO обнуление всех значений и сигнал евентом
}

/////////////// Открытые сценарии
ErrorCode Connection::initialConnections() noexcept {
	auto result = NotDefined;

	try {
		if (tryOpenConverter()) {
			scanControllers();
			openControllers();
			SetEvent(*_e_newInfo);
			updateControllerInfo(CLEAR);
			result = Success;
		}
	}
	catch (const std::exception& error) {
		result = errorStatus;
		std::cout << error.what();
	}
	
	return result;
}

ErrorCode Connection::closeConnections() noexcept  {
	auto result = NotDefined;

	try {
		tryCloseConverter();
		updateControllerInfo(CLEAR);
		result = Success;
	}
	catch (const std::exception& error) {
		result = errorStatus;
		std::cout << error.what();
	}
	return result;
}

ErrorCode Connection::reconnect() noexcept {
	auto result = NotDefined;

	try {
		tryCloseConverter();
		if (tryOpenConverter()) {
			scanControllers();
			openControllers();
			SetEvent(*_e_newInfo);
		}
		updateControllerInfo(CLEAR);
		result = Success;
	}
	catch(const std::exception& error) {
		result = errorStatus;
		std::cout << error.what();
	}

	return result;
}

ErrorCode Connection::getConnectionStatus(_Out_ bool& connection) noexcept {
	auto result = NotDefined;

	try {
		(getStatus() != ZP_CS_DISCONNECTED) ? connection = true : connection = false;
		updateControllerInfo(CLEAR);
		result = Success;
	}
	catch(const std::exception& error) {
		result = errorStatus;
		std::cout << error.what();
	}

	return result;
}

ErrorCode Connection::setNotifications(_Out_ std::vector<HANDLE>& waitingArray) noexcept {
	auto result = NotDefined;

	try {
		trySetNotifications(waitingArray);
		updateControllerInfo(CLEAR);
		result = Success;
	}
	catch (const std::exception& error) {
		result = errorStatus;
		std::cout << error.what();
	}

	return result;
}

ErrorCode Connection::closeNotifications() {
	auto result = NotDefined;

	try {
		tryCloseNotifications();
		updateControllerInfo(CLEAR);
		result = Success;
	}
	catch (const std::exception& error) {
		result = errorStatus;
		std::cout << error.what();
	}

	return result;
}

ErrorCode Connection::readConverterNotifies(std::vector<std::pair<UINT, LPARAM>>& converterMessageList) noexcept {
	auto result = NotDefined;

	try {
		readConverterNotify(converterMessageList);
		updateControllerInfo(CLEAR);
		result = Success;
	}
	catch (const std::exception& error) {
		result = errorStatus;
		std::cout << error.what();
	}
	return result;
}

ErrorCode Connection::readControllerNotifies(const int controller, _Out_ std::vector<std::pair<UINT, LPARAM>>& controllerMessageList) noexcept {
	auto result = NotDefined;

	try {
		readControllerNotify(controller, controllerMessageList);
		updateControllerInfo(CLEAR);
		result = Success;
	}
	catch (const std::exception& error) {
		result = errorStatus;
		std::cout << error.what();
	}
	return result;
}

ErrorCode Connection::readControllerEvent(const int controller, _Out_ std::vector<_ZG_CTR_EVENT>& controllerEventsList) {
	auto result = NotDefined;

	try {
		ReadControllerEvents(controller, controllerEventsList);
		updateControllerInfo(CLEAR);
		result = Success;
	}
	catch (const std::exception& error) {
		result = errorStatus;
		std::cout << error.what();
	}
	return result;
}
/////////////// Открытые сценарии

/////////////// Приватные сценарии
bool Connection::tryOpenConverter() {
	ZeroMemory(&temp_Params, sizeof(temp_Params));
	temp_Params.nType = _data->portType;
	for (size_t i = 0; i < _data->converterPorts->size(); i++) {
		temp_Params.pszName = _data->converterPorts->at(i).szName;
		try {
			openConverter();
		}
		catch (const std::exception& error) {
			if (typeid(error) == typeid(OpenFailed) && i < _data->converterPorts->size() - 1)
				continue;
			else {
				std::cout << error.what();
			}
		}
		if (_hConvector != NULL) {
			updateConverterInfo(true);
			return true;
		}
	}

	errorStatus = ConverterOpenFail;
	updateConverterInfo(false);
	return false;
}

void Connection::tryCloseConverter() {
	closeControllers();
	closeConverter();
}

void Connection::scanControllers() {

	//TODO log trace
	INT MaxCount = 0;
	HRESULT hrController;
	_ZG_FIND_CTR_INFO mControllerInfo;
	_data->controllersInfo->clear(); 

	if (ZG_Cvt_SearchControllers(_hConvector, MaxCount, NULL) != S_OK)
		throw SearchError(std::string("Error while search controllers"));

	while ((hrController = ZG_Cvt_FindNextController(_hConvector, &(_ZG_FIND_CTR_INFO&)mControllerInfo)) == S_OK) {
		// TODO log trace
		_data->controllersInfo->push_back(mControllerInfo);
	}

	if (hrController != ZP_S_NOTFOUND) {
		errorStatus = ConverterCommandFail;
		throw SearchError(std::string("Error while search controllers"));
	}
}

void Connection::openControllers() {
	unsigned int i = 0;
	for each (_ZG_FIND_CTR_INFO controller in *(_data->controllersInfo))
	{
		try {
			openController(i);
			readControllerIdxs();
			updateControllerInfo(ADD);
		}
		catch (const std::exception& error) {
			updateControllerInfo(ADDERR);
		}
		i++;
	}
}

void Connection::closeControllers() {
	if (!_hControllersList.empty()) {
		updateControllerInfo(REBASE);
		_hControllersList.clear();
	}
}

void Connection::updateConverterInfo(bool connection) {
	switch (connection) {
	case true:
		_data->converterStatus = connection;
		break;
	case false:
		ZG_CloseHandle(_hConvector);
		_hConvector = NULL;
		ZeroMemory(&*_data->converterDetailInfo, sizeof(*_data->converterDetailInfo));
		_data->converterStatus = connection;
		break;
	/*default:
		errorStatus = ConnectionCommandFail;
		throw CommandError(std::string("updateConverterInfo: not avaliable parametr"));*/
	}
}

void Connection::updateControllerInfo(Action action, int number ) {
	switch (action)
	{
	case ADD:
		_hControllersList.push_back(temp_hController);
		_data->controllersDetailInfo->push_back(temp_controllersDetailInfo);
		_data->controllersIndexWriteRead->push_back(temp_controlerIndexWriteRead);
		_data->controllersStatus->push_back(true);
		break;
	case ADDERR:
		_hControllersList.push_back(temp_hController);
		_data->controllersDetailInfo->push_back(temp_controllersDetailInfo);
		_data->controllersIndexWriteRead->push_back(temp_controlerIndexWriteRead);
		_data->controllersStatus->push_back(false);
		break;
	case CLOSE:
		if (number >= 0) {
			ZG_CloseHandle(_hControllersList.at(number));
			_data->controllersStatus->at(number) = false;
			ZeroMemory(&_data->controllersDetailInfo->at(number), sizeof(_data->controllersDetailInfo->at(number)));
			ZeroMemory(&_data->controllersStatus->at(number), sizeof(_data->controllersStatus->at(number)));
			ZeroMemory(&_data->controllersIndexWriteRead->at(number), sizeof(&_data->controllersIndexWriteRead->at(number)));
		}
		else {
			errorStatus = ConnectionCommandFail;
			throw CommandError(std::string("updateControllerInfo number: " + number + ' ' + action));
		}
		break;
	case CLEAR:
		temp_writeIndex = temp_readIndex = currentControllerNumber = NULL;
		temp_hController = NULL;
		ZeroMemory(&temp_Params, sizeof(temp_Params));
		ZeroMemory(&temp_controllersDetailInfo, sizeof(temp_controllersDetailInfo));
		ZeroMemory(&temp_controlerIndexWriteRead, sizeof(temp_controlerIndexWriteRead));
		_converterMessageList.clear();
		_controllerMessageList.clear();
		break;
	case CHANGE: // TODO
		break;
	case REBASE:
		for each (auto controller in _hControllersList)
		{
			ZG_CloseHandle(controller);
		}
		_data->controllersStatus->clear();
		_data->controllersDetailInfo->clear();
		_data->controllersStatus->clear();
		_data->controllersIndexWriteRead->clear();
		break;
	default:
		errorStatus = ConnectionCommandFail;
		throw CommandError(std::string("updateControllerInfo number: " + number + ' ' + action));
		break;
	}
}

void Connection::trySetNotifications(_Out_ std::vector<HANDLE>& waitingArray) {
	waitingArray.clear();
	
	auto temp_commonConverterSettings  = commonConverterSettings;
	auto eventConverter = CreateEvent(NULL, TRUE, FALSE, NULL);
	temp_commonConverterSettings.hEvent = eventConverter;
	cvt_SetNotification(temp_commonConverterSettings);
	waitingArray.push_back(eventConverter);

	for (size_t i = 0; i < _hControllersList.size(); i++) {
		if (_data->controllersStatus->at(i) == true)
			try {
				auto temp_commonControllerSettings = commonControllerSettings;
				auto eventController = CreateEvent(NULL, TRUE, FALSE, NULL);
				temp_commonControllerSettings.hEvent = eventController;
				temp_commonControllerSettings.nReadEvIdx = _data->controllersIndexWriteRead->at(i).first;
				temp_hController = _hControllersList.at(i);
				ctr_SetNotification(temp_commonControllerSettings);
				waitingArray.push_back(eventController);
			}
			catch (const std::exception& error) {
				errorStatus = ControllerCommandFail;
				std::cout << error.what() << "\n";
			}
	}

}

void Connection::tryCloseNotifications() {
	cvt_SetNotification();

	try {
		for (size_t i = 0; i < _hControllersList.size(); i++) {
			temp_hController = _hControllersList.at(i);
			ctr_SetNotification();
			updateControllerInfo(CLOSE, i);
		}
	}
	catch (const std::exception& error) {
		std::cout << error.what();
	}
}

void Connection::readConverterNotify(_Out_ std::vector<std::pair<UINT, LPARAM>>& _converterMessage) {
	cvt_GetNextMessage();
	_converterMessage = _converterMessageList;
	_converterMessageList.clear();
}

void Connection::readControllerNotify(const int controller, std::vector<std::pair<UINT, LPARAM>>& controllerMessageList) {
	temp_hController = _hControllersList.at(controller);
	currentControllerNumber = controller;
	ctr_GetNextMessage();
	controllerMessageList = _controllerMessageList;
}
/////////////// Приватные сценарии

/////////////// Низкоуровневые функции
void Connection::openConverter() {
	_data->mutex->lock();
	if (ZG_Cvt_Open(&_hConvector, &temp_Params, &*_data->converterDetailInfo) != S_OK) {
		_data->mutex->unlock();
		errorStatus = ConverterOpenFail;
		throw OpenFailed(std::string("ZG_Cvt_Open"), std::string("Converter: " + std::to_string(_data->converterInfo->nSn)));
	}
	_data->mutex->unlock();
}

void Connection::closeConverter() {
	if (!_hControllersList.empty())
		closeControllers();
	updateConverterInfo(false);
}

ZP_CONNECTION_STATUS Connection::getStatus() {
	ZP_CONNECTION_STATUS status;
	_data->mutex->lock();
	if (ZG_Cvt_GetConnectionStatus(_hConvector, &status) != S_OK) {
		_data->mutex->unlock();
		errorStatus = ConnectionCommandFail;
		throw CommandError(std::string("getStatus"));
	}
	_data->mutex->unlock();
	return status;
}

void Connection::openController(const int controller) {
	auto address = (unsigned int)_data->controllersInfo->at(controller).nAddr;
	_data->mutex->lock();
	if (ZG_Ctr_Open(&temp_hController, _hConvector, address, 0, &temp_controllersDetailInfo, ZG_CTR_UNDEF) != S_OK) {
		_data->mutex->unlock();
		errorStatus = ControllerOpenFail;
		throw OpenFailed(std::string("ZG_Ctr_Open"), std::string("Controller: " + std::to_string(_data->controllersInfo->at(controller).nAddr) + std::string(" at Converter: ") + std::to_string(_data->converterInfo->nSn)));
	}
	_data->mutex->unlock();
}

void Connection::readControllerIdxs() {
	_data->mutex->lock();
	if (ZG_Ctr_ReadEventIdxs(temp_hController, &temp_writeIndex, &temp_readIndex) != S_OK) {
		_data->mutex->lock();
		errorStatus = ControllerCommandFail;
		throw OpenFailed(std::string("Connection controller address: " + std::to_string(_data->controllersDetailInfo->at(currentControllerNumber).nAddr)), std::string("Controller"));
	}
	_data->mutex->unlock();
	temp_controlerIndexWriteRead = std::make_pair(temp_writeIndex, temp_readIndex);
}

int Connection::readEvents(int& startFrom, const int read, const int needToReed) {
	bool transfusion = false;
	temp_controllerEvents.resize(5);
	int reading = temp_controllerEvents.size();

	if (startFrom + 5 > _data->controllersDetailInfo->at(currentControllerNumber).nMaxEvents) {
		transfusion = true;
		reading = _data->controllersDetailInfo->at(currentControllerNumber).nMaxEvents - startFrom;
		startFrom = _data->controllersDetailInfo->at(currentControllerNumber).nMaxEvents - reading;
		temp_controllerEvents.resize(reading);
	}
	if (startFrom + 5 > (startFrom + needToReed - read)) {
		reading = (startFrom + reading) - ((startFrom + reading) - needToReed);
		temp_controllerEvents.resize(reading);
	}

	_data->mutex->lock();
	if (ZG_Ctr_ReadEvents(temp_hController, startFrom, temp_controllerEvents.data(), reading, NULL, NULL) != S_OK) {
		_data->mutex->unlock();
		errorStatus = ControllerCommandFail;
		throw CommandError(std::string("ZG_Ctr_ReadEvents at: " + std::to_string(_data->converterDetailInfo->nSn)));
	}
	_data->mutex->unlock();

	if (transfusion) {
		transfusion = false;
		startFrom = 0;
	}
	else {
		startFrom += reading;
	}

	return reading;
}

void Connection::updateControllerReadIndex(const int newIndex) {
	_data->mutex->lock();
	if (ZG_Ctr_WriteEventIdxs(temp_hController, 0x2, 0, newIndex) != S_OK) {
		_data->mutex->unlock();
		throw CommandError(std::string("Some error"));
	}
	_data->mutex->unlock();
}

void Connection::closeController(const int number) {
	updateControllerInfo(CLOSE, number);
}
/////////////// Низкоуровневые функции

/////////////// Низкоуровневые функции команды
void Connection::cvt_SetNotification(_ZG_CVT_NOTIFY_SETTINGS settings) {
	_data->mutex->lock();
	if (ZG_Cvt_SetNotification(_hConvector, &settings) != S_OK) {
		_data->mutex->unlock();
		errorStatus = ConverterCommandFail;
		throw CommandError(std::string("ZG_Cvt_SetNotification"));
	}
	_data->mutex->unlock();
}

void Connection::ctr_SetNotification(_ZG_CTR_NOTIFY_SETTINGS settings) {
	_data->mutex->lock();
	if (ZG_Ctr_SetNotification(temp_hController, &settings) != S_OK) {
		_data->mutex->unlock();
		errorStatus = ControllerCommandFail;
		throw CommandError(std::string("ZG_Ctr_SetNotification at: " + std::to_string(currentControllerNumber)));
	}
	_data->mutex->unlock();
}

HRESULT Connection::cvt_GetNextMessage() {
	HRESULT result;
	UINT messageType;
	LPARAM temp_converterMessage;
	_converterMessageList.clear();

	_data->mutex->lock();
	while ((result = ZG_Cvt_GetNextMessage(_hConvector, &messageType, &temp_converterMessage)) == S_OK) {
		_converterMessageList.push_back(std::make_pair(messageType, temp_converterMessage));
	}
	_data->mutex->unlock();

	if (result == ZP_S_NOTFOUND)
		result = S_OK;
	else {
		errorStatus = ConverterCommandFail;
		throw CommandError(std::string("ZG_Cvt_GetNextMessage"));
	}

	return result;
}

HRESULT Connection::ctr_GetNextMessage() {
	HRESULT result;
	UINT messageType;
	LPARAM temp_controllerMessage;
	_controllerMessageList.clear();

	_data->mutex->lock();
	while ((result = ZG_Ctr_GetNextMessage(temp_hController, &messageType, &temp_controllerMessage)) == S_OK) {
		_controllerMessageList.push_back(std::make_pair(messageType, temp_controllerMessage));
	}
	_data->mutex->unlock();

	if (result == ZP_S_NOTFOUND)
		result = S_OK;
	else {
		throw CommandError(std::string("ZG_Cvt_GetNextMessage"));
	}

	return result;
}

void Connection::ReadControllerEvents(const int controller, _Out_ std::vector<_ZG_CTR_EVENT>& controllerEventList) {
	temp_hController = _hControllersList.at(controller);
	currentControllerNumber = controller;
	readControllerIdxs();
	_data->controllersIndexWriteRead->at(controller) = temp_controlerIndexWriteRead;
	int i = 0;
	int countOfEvents;
	int read = 0;
	int startFrom = temp_readIndex;

	if (temp_writeIndex > temp_readIndex)
		countOfEvents = temp_writeIndex - temp_readIndex;

	if (temp_writeIndex <= temp_readIndex) 
		countOfEvents = _data->controllersDetailInfo->at(controller).nMaxEvents - temp_readIndex + temp_writeIndex;
	

	while (read < countOfEvents) {
		read += readEvents(startFrom, read, countOfEvents);
		//i = (read - temp_readIndex);
		auto lastSize = controllerEventList.size();
		//controllerEventList.resize(lastSize + read);
		controllerEventList.insert(controllerEventList.end(), temp_controllerEvents.begin(), temp_controllerEvents.end());
		updateControllerReadIndex(startFrom);
	}
}
/////////////// Низкоуровневые функции команды

#ifdef _DEBUG
bool Connection::StaticTest() {
	
	HANDLE *_hSearch = new HANDLE;
	HRESULT hrSearch;
	INT_PTR nPortCount;
	std::unique_ptr<Connection> tempConnection = nullptr;
	ZP_PORT_TYPE portType = ZP_PORT_IP;
	_ZG_CVT_OPEN_PARAMS _searchParams;
	ZeroMemory(&_searchParams, sizeof(_searchParams));
	std::unique_ptr<AvailableConnection> tempAvailableConnection(new AvailableConnection);

	if (!CheckZGError(ZG_SearchDevices(_hSearch, &((_ZP_SEARCH_PARAMS &)_searchParams), FALSE, TRUE), _T("ZG_SearchDevices")))
		throw SearchError(std::string("Error in search")); // TODO log trace

	while ((hrSearch = ZG_FindNextDevice(*_hSearch, &*(tempAvailableConnection->converterInfo), &(*tempAvailableConnection->converterPorts)[0], tempAvailableConnection->converterPorts->size(), &nPortCount)) == S_OK) {
		auto temp = bool();
		tempAvailableConnection->portType = ZP_PORT_IP;
		tempConnection = std::make_unique<Connection>(std::move(tempAvailableConnection));
		tempConnection->initialConnections();
		tempConnection->reconnect();
		tempConnection->getConnectionStatus(temp);
		tempConnection->closeConnections();
		tempConnection->getConnectionStatus(temp);
		tempConnection->reconnect();
		_converterInfoListTest->push_back(std::move(tempConnection));

		_tprintf(TEXT("1 convertor found\n"));

		tempAvailableConnection = std::move(std::unique_ptr<AvailableConnection>(new AvailableConnection));
	}
	ZG_CloseHandle(*_hSearch);
	//_converterInfoListTest->clear();
	delete _hSearch;
	
	return true;
}
#endif