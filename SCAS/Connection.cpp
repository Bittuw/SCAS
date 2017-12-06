#pragma once
#include "stdafx.h"
#include "Connection.h"

//Connection::Connection() {}

Connection::Connection(std::unique_ptr<AvailableConnection> availableConnection) :
_e_newInfo(std::make_shared<HANDLE>(CreateEvent(NULL, TRUE, FALSE, NULL))),
_e_destroyed(std::make_shared<HANDLE>(CreateEvent(NULL, TRUE, FALSE, NULL)))
{
	if (
			availableConnection->converterPorts == nullptr ||
			availableConnection->converterInfo == nullptr ||
			availableConnection->portType == nullptr //||
			//(*availableConnection)->connection != nullptr
		)
		throw ConstructError(std::string("Bad initialize data!"));

	_connectionData = std::move(availableConnection);
}

Connection::~Connection()
{// TODO log trace
	SetEvent(*_e_destroyed); // TODO проверить, успеет ли дойти событие до уведомляемого потока

	if (!_hControllersList.empty()) {
		for (size_t i = 0; i < _hControllersList.size(); i++)
			ZG_CloseHandle(*(_hControllersList[i]));

		_hControllersList.clear();
	}

	if (_hConvector != nullptr)
			ZG_CloseHandle(*_hConvector);

	_hConvector = nullptr;
}

bool Connection::initialConnections() {
	if (openConnection()) {
		scanControllers();
		openControllers();
		SetEvent(*_e_newInfo);
		return true;
	}
	return false;
}

void Connection::setNewConnactionInfo(std::unique_ptr<AvailableConnection> pointer) {
	_connectionData = std::move(pointer);
	// TODO обнуление всех значений и сигнал евентом
}

bool Connection::openConnection() {
	_ZG_CVT_OPEN_PARAMS openConvectorParams;
	ZeroMemory(&openConvectorParams, sizeof(openConvectorParams));

	for (unsigned int i = 0; i < _countof(_connectionData->converterPorts); i++) {
		// TODO log trace
		_hConvector = std::unique_ptr<HANDLE> (new HANDLE);		

		openConvectorParams.pszName = (_connectionData->converterPorts[i]).szName;
		openConvectorParams.nType = *(_connectionData->portType);
		
		if (!CheckZGError(ZG_Cvt_Open(&*_hConvector, &openConvectorParams, &*_connectionData->converterDetailInfo), _T("ZG_Cvt_Open")))
			throw OpenFailed(std::string("Connection converter port: " + *(WCHAR*)(_connectionData->converterPorts[i]).szName), std::string("Convector"));
		else {
			_connectionData->isConverterJoinable = true;
			return true;
		}
	}

	_connectionData->isConverterJoinable = false;
	return false;
}

void Connection::closeConnection() {
	closeControllers();
	ZG_CloseHandle(*_hConvector);
	_connectionData->isConverterJoinable = false;
}

void Connection::scanControllers() {

	//TODO log trace
	INT MaxCount = 0;
	HRESULT hrController;
	_ZG_FIND_CTR_INFO mControllerInfo;
	_connectionData->controllersInfo->clear();

	if (!CheckZGError(ZG_Cvt_SearchControllers(*_hConvector, MaxCount, NULL), _T("ZG_Cvt_SearchControllers")))
		throw InitializationSearchError(std::string("test message"));

	while ((hrController = ZG_Cvt_FindNextController(*_hConvector, &(_ZG_FIND_CTR_INFO&)mControllerInfo)) == S_OK) {
		// TODO log trace
		_connectionData->controllersInfo->push_back(mControllerInfo);
	}

	if (hrController != ZP_S_NOTFOUND)
		throw SearchError(std::string("Error while search controllers"));
}

//bool Connection::openController(const int controllerAddress) {
//	// TODO log trace
//	auto temp_hController = std::unique_ptr<HANDLE> (new HANDLE);
//	_ZG_CTR_INFO rCtrInfo;
//	ZeroMemory(&rCtrInfo, sizeof(rCtrInfo));
//
//	if (!CheckZGError(ZG_Ctr_Open(&*_hController, &*_hConvector, controllerAddress, 0, &rCtrInfo, ZG_CTR_UNDEF), _T("ZG_Ctr_Open")))
//		throw OpenFailed(std::string("Connection controller address: " + controllerAddress), std::string("Controller"));
//
//	isOpenController = true;
//	_addrOfOpenController = controllerAddress;
//	return true;
//}

void Connection::openControllers() {
	for each (_ZG_FIND_CTR_INFO controller in *(_connectionData->controllersInfo))
	{
		auto temp_hController = std::make_unique<HANDLE>(new HANDLE);
		_ZG_CTR_INFO rCtrInfo;
		int writeIndex, readIndex;

		ZeroMemory(&rCtrInfo, sizeof(rCtrInfo));

		if (!CheckZGError(ZG_Ctr_Open(&*temp_hController, &*_hConvector, controller.nAddr, 0, &rCtrInfo, ZG_CTR_UNDEF), _T("ZG_Ctr_Open"))) 
			throw OpenFailed(std::string("Connection controller address: " + controller.nAddr), std::string("Controller"));

		if (!CheckZGError(ZG_Ctr_ReadEventIdxs(&*temp_hController, &writeIndex, &readIndex), _T("ZG_Ctr_ReadEventIdxs")))
			throw OpenFailed(std::string("Connection controller address: " + controller.nAddr), std::string("Controller"));
		
		_hControllersList.push_back(std::move(temp_hController));
		_connectionData->controllersDetailInfo->push_back(rCtrInfo);
		_connectionData->controlersIndexWriteRead->push_back(std::make_pair(writeIndex, readIndex));
	}
}

//void Connection::closeController() {
//	ZG_CloseHandle(*_hController);
//	isOpenController = false;
//	//_addrOfOpenController = 0;
//	// TODO log trace
//}

void Connection::closeControllers() {
	if (!_hControllersList.empty()) {
		for (size_t i = 0; i < _hControllersList.size(); i++)
			ZG_CloseHandle(*(_hControllersList[i]));
		_hControllersList.clear();
	}
}

void Connection::cvt_SetNotification(_ZG_CVT_NOTIFY_SETTINGS notifySetting ) {
	_connectionData->connectionMutex->lock();
	if (!CheckZGError(ZG_Cvt_SetNotification(&*_hConvector, &notifySetting), _T("ZG_Cvt_SetNotification"))) {
		_connectionData->connectionMutex->unlock();
		throw CommandError(std::string("ZG_Cvt_SetNotification"));
	}
	_connectionData->connectionMutex->unlock();
}

void Connection::ctr_SetNotification(const int position, _ZG_CTR_NOTIFY_SETTINGS notifySetting) {
	_connectionData->connectionMutex->lock();
	if (!CheckZGError(ZG_Ctr_SetNotification(&*_hControllersList[position], &notifySetting), _T("ZG_Cvt_SetNotification"))) {
		_connectionData->connectionMutex->unlock();
		throw CommandError(std::string("ZG_Ctr_SetNotification at: " + position));
	}
	_connectionData->connectionMutex->unlock();
}

HANDLE* const Connection::get_hConvertor() {
	if (_hConvector == nullptr)
		throw std::runtime_error("Null pointer: maybe you forgot to open connection!");
	return &*_hConvector;
} 

std::shared_ptr<std::vector<std::unique_ptr<HANDLE>>> Connection::get_hController() {
	if (_hControllersList.empty())
		throw std::runtime_error("Null pointer: maybe you forgot to open connection!");
	return std::shared_ptr<std::vector<std::unique_ptr<HANDLE>>> (&_hControllersList);
}

//std::vector<_ZG_FIND_CTR_INFO>* const Connection::get_controllersInfo() {
//	if (_connectionData->controllersInfo->empty())
//		throw std::runtime_error("Info vector is empty, scanControllers!");
//	return &(*(_connectionData->controllersInfo));
//}

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
	*(tempAvailableConnection->portType) = ZP_PORT_IP;

	if (!CheckZGError(ZG_SearchDevices(_hSearch, &((_ZP_SEARCH_PARAMS &)_searchParams), FALSE, TRUE), _T("ZG_SearchDevices")))
		throw SearchError(std::string("Error in search")); // TODO log trace

	while ((hrSearch = ZG_FindNextDevice(*_hSearch, &*(tempAvailableConnection->converterInfo), tempAvailableConnection->converterPorts, _countof(tempAvailableConnection->converterPorts), &nPortCount)) == S_OK) {
		try {
			tempConnection = std::unique_ptr<Connection> (new Connection(std::move(tempAvailableConnection)));
			tempConnection->initialConnections();
			_convertorsInfoList->push_back(std::move(tempConnection));
		}
		catch (std::exception error) {
			// TODO log trace and to log base
			std::cout << error.what() << "\n";
			//throw SearchError(std::string(error.what()));
		}

		_tprintf(TEXT("1 convertor found\n"));
		
		tempAvailableConnection = std::move(std::unique_ptr<AvailableConnection>(new AvailableConnection));
	}
	ZG_CloseHandle(*_hSearch);
	_convertorsInfoList->clear();
	return true;
}
#endif