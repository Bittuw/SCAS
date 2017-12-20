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
		std::cout << error.what();
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
			// TODO ����������� ���������
			// TODO �������
		}
		else { // �����������
			_controllerMessagesList.clear();
			temp_localConnection->readControllerNotifies(event - 1, _controllerMessagesList);
			parseControllerNotify();
			// TODO ����������� ���������
			// TODO �������
		}
	}
}
/////////////// ��������� ��������
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

void NotifiedThread::parseControllerNotify() {

	size_t i = 0;

	for each (auto message in _controllerMessagesList) {
		switch (message.first) {
		case ZG_NF_CTR_NEW_EVENT:
			temp_localConnection->readControllerEvent(i, _controllerEventList);
			// TODO ���������� �������
			// TODO ����� ���� ����
			break;
		case ZG_NF_CTR_CLOCK: 
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
