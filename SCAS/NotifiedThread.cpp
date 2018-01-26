#include "stdafx.h"
#include "NotifiedThread.h"
#include "Connection.h"
#include "DataStructs.h"

NotifiedThread::NotifiedThread(std::shared_ptr<Connection> connection) :
	_localConnection(connection),
	_e_localExitThread(std::make_shared<HANDLE>(CreateEvent(NULL, TRUE, FALSE, NULL))),
	_waitingArray(std::make_unique<std::vector<HANDLE>>()),
	_e_NotifiesList({}),
	_converterMessagesList({}),
	_controllerMessagesList({}),
	_controllerEventList({})
{
	if (auto temp_localConnection = _localConnection.lock()) {
		_e_newInfo = temp_localConnection->_e_newInfo;
		_e_destroyed = temp_localConnection->_e_destroyed;
		_waitingConstArray = { *_globalExitThread, *_e_localExitThread, *_e_destroyed, *_e_newInfo };
		refreshWaitingArray();
	}
	else {
		// Throw connection
	}
}


NotifiedThread::~NotifiedThread()
{
}

void NotifiedThread::runListening(std::shared_ptr<Connection> connection) {
	try {
		std::thread NotifiedThread(&NotifiedThread::startListining, new NotifiedThread(connection));
		NotifiedThread.detach();
	}
	catch (const std::exception& error) {
		Log(MessageTypes::ERR) << error.what();
	}
}

void NotifiedThread::startListining() {
	while (!_localConnection.expired()) {

		auto event = WaitForMultipleObjects(_waitingArray->size(), _waitingArray->data(), FALSE, INFINITE);

		switch (event) { 
		case 0: // �������� 1 global ������� �����������
			temp_localConnection = _localConnection.lock();
			temp_localConnection->closeConnections();
			temp_localConnection = nullptr;
			ExitThread(0);
			break;
		case 1: // �������� 2 local
			ExitThread(0); 
			break;
		case 2: // �������� 3: ����������� Connection
			ResetEvent(_waitingArray->at(event));
			ExitThread(0);
			break;
		case 3: // �������� 4: ����� ������ Connection
			createNotifies();
			ResetEvent(_waitingArray->at(event));
			refreshWaitingArray();
			break;
		case WAIT_TIMEOUT:
			break;
		default: // ��������� 
			if ((size_t)4 <= (size_t)event <= _waitingArray->size()) { // �������� 5
				ResetEvent(_waitingArray->at(event));
				switchDevice(event - 4);
			}
			else { // �������� 6
				// TODO throw exception
				break;
			}

			refreshWaitingArray();
		}
	}
}

/////////////// ��������� ��������
bool NotifiedThread::createNotifies() {
	if (temp_localConnection = _localConnection.lock()) {
		temp_localConnection->setNotifications(_e_NotifiesList); // TODO ���� ��� �������� �� ������
	}
	else {
		// TODO ���� weak_ptr ����
		return false;
	}
	temp_localConnection = nullptr;
	return true;
}

void NotifiedThread::switchDevice(const int event) {
	temp_localConnection = _localConnection.lock();
	if (temp_localConnection) {
		if (event == 0) { // ���������
			_converterMessagesList.clear();
			temp_localConnection->readConverterNotifies(_converterMessagesList);
			parseConverterNotify();
			// TODO ����������� ���������
			// TODO �������
		}
		else { // �����������
			_controllerMessagesList.clear();
			temp_localConnection->readControllerNotifies(event - 1, _controllerMessagesList);
			parseControllerNotify(event - 1);
			// TODO ����������� ���������
			// TODO �������
		}
	}
}
/////////////// ��������� ��������

void NotifiedThread::parseConverterNotify() {
	size_t i = 0;
	PZG_FIND_CTR_INFO tempController;

	for each (auto message in _converterMessagesList) {
		switch (message.first) {
		case ZG_N_CVT_CTR_INSERT:
			tempController = (PZG_FIND_CTR_INFO)(message.second);
			auto add = *(_ZG_FIND_CTR_INFO*)tempController;
			temp_localConnection->addController(add);
			//_tprintf(TEXT("Controller added: %d\r\n"), add.nSn);
			Log(MessageTypes::EVENT) << std::string("Constroller added: " + std::to_string(add.nSn));
			createNotifies();
			break;
		case ZG_N_CVT_CTR_REMOVE:
			tempController = (PZG_FIND_CTR_INFO)(message.second);
			auto remove = *(_ZG_FIND_CTR_INFO*)tempController;
			temp_localConnection->removeController(remove);
			Log(MessageTypes::EVENT) << std::string("Constroller removed: " + std::to_string(remove.nSn));
			createNotifies();
			break;
		case ZG_N_CVT_CTR_CHANGE:
			break;
		case ZG_N_CVT_ERROR:
			break;
		case ZG_CVTN_CONNECTION_CHANGE:
			break;
		default:
			// TODO ����������� ������
			break;
		}
		i++;
	}
}

void NotifiedThread::parseControllerNotify(const int& controller) {

	size_t i = 0;

	for each (auto message in _controllerMessagesList) {
		switch (message.first) {
		case ZG_NF_CTR_NEW_EVENT:
			temp_localConnection->readControllerEvent(i, _controllerEventList);
			parseCotrollerEvents(controller);
			//*testList = _controllerEventList;
			// TODO ���������� �������
			// TODO ����� ���� ����
			_controllerEventList.clear();
			break;
		case ZG_NF_CTR_CLOCK: 
			temp_localConnection->setControllerTime(controller);
			// TODO ����� ������� ��������� �������� �������
			break;
		case ZG_NF_CTR_KEY_TOP: 
			// TODO ��
			break;
		case ZG_NF_CTR_ADDR_CHANGE: 
			// TODO �������� ���������� � �����������
			break;
		case ZG_NF_CTR_ERROR:
			// TODO ������
			break;
		default:
			// TODO ����������� ������
			break;
		}
		i++;
	}
}

void NotifiedThread::parseCotrollerEvents(const int& controller) {
	PZG_CTR_EVENT tempEvent;

	for each (auto event in _controllerEventList)
	{
		tempEvent = &event;
		_ZG_EV_TIME time;
		ZG_CTR_DIRECT direct;
		INT nKeyIdx, nKeyBank;

		switch (tempEvent->nType)
		{
		case ZG_EV_BUT_OPEN:
			ZG_Ctr_DecodePassEvent(temp_localConnection->getControllerHandle(controller), tempEvent->aData, &time, &direct, &nKeyIdx, &nKeyBank);
			_tprintf(TEXT("%.2d.%.2d %.2d:%.2d:%.2d %s %s (key_idx: %d, bank#: %d)\n"),
				time.nDay, time.nMonth,
				time.nHour, time.nMinute, time.nSecond,
				DirectList[direct],
				EventTypeList[tempEvent->nType],
				nKeyIdx, nKeyBank);
			break;
		case ZG_EV_KEY_NOT_FOUND:
			ZG_Ctr_DecodePassEvent(temp_localConnection->getControllerHandle(controller), tempEvent->aData, &time, &direct, &nKeyIdx, &nKeyBank);
			_tprintf(TEXT("%.2d.%.2d %.2d:%.2d:%.2d %s %s (key_idx: %d, bank#: %d)\n"),
				time.nDay, time.nMonth,
				time.nHour, time.nMinute, time.nSecond,
				DirectList[direct],
				EventTypeList[tempEvent->nType],
				nKeyIdx, nKeyBank);
			break;
		case ZG_EV_KEY_OPEN:
			ZG_Ctr_DecodePassEvent(temp_localConnection->getControllerHandle(controller), tempEvent->aData, &time, &direct, &nKeyIdx, &nKeyBank);
			_tprintf(TEXT("%.2d.%.2d %.2d:%.2d:%.2d %s %s (key_idx: %d, bank#: %d)\n"),
				time.nDay, time.nMonth,
				time.nHour, time.nMinute, time.nSecond,
				DirectList[direct],
				EventTypeList[tempEvent->nType],
				nKeyIdx, nKeyBank);
			break;
		case ZG_EV_PASSAGE:
			ZG_Ctr_DecodePassEvent(temp_localConnection->getControllerHandle(controller), tempEvent->aData, &time, &direct, &nKeyIdx, &nKeyBank);
			_tprintf(TEXT("%.2d.%.2d %.2d:%.2d:%.2d %s %s (key_idx: %d, bank#: %d)\n"),
				time.nDay, time.nMonth,
				time.nHour, time.nMinute, time.nSecond,
				DirectList[direct],
				EventTypeList[tempEvent->nType],
				nKeyIdx, nKeyBank);
			break;
		case ZG_EV_KEY_ACCESS:
			break;
		case ZG_EV_NO_OPEN:
			break;
		default:
			break;
		}
	}
}

/////////////// �������
void NotifiedThread::refreshWaitingArray() {
	try {
		_waitingVariableArray.clear();
		_waitingArray->clear();

		if (!_e_NotifiesList.empty()) {
			_waitingVariableArray.resize(_e_NotifiesList.size());
			std::copy(_e_NotifiesList.begin(), _e_NotifiesList.end(), _waitingVariableArray.begin());
		}

		*_waitingArray = _waitingConstArray;
		_waitingArray->resize(_waitingArray->size() + _waitingVariableArray.size());
		std::copy(_waitingVariableArray.begin(), _waitingVariableArray.end(), _waitingArray->end() - _waitingVariableArray.size());
	}
	catch (const std::exception& error) {
		std::cout << error.what();
	}
}
/////////////// �������