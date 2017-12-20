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
		case 0: // Сценарий 1 global Закрыть уведомления
			temp_localConnection = _localConnection.lock();
			temp_localConnection->closeConnections();
			temp_localConnection = nullptr;
			ExitThread(0);
			break;
		case 1: // Сценарий 2 local
			ExitThread(0); 
			break;
		case 2: // Сценарий 3: Уничтожение Connection
			ResetEvent(_waitingArray->at(event));
			ExitThread(0);
			break;
		case 3: // Сценарий 4: Новые данные Connection
			createNotifies();
			ResetEvent(_waitingArray->at(event));
			refreshWaitingArray();
			break;
		case WAIT_TIMEOUT:
			break;
		default: // Остальные 
			if ((size_t)4 <= (size_t)event <= _waitingArray->size()) { // Сценарий 5
				ResetEvent(_waitingArray->at(event));
				switchDevice(event - 4);
			}
			else { // Сценарий 6
				// TODO throw exception
				break;
			}
		}
	}
}

/////////////// Приватные сценарии
bool NotifiedThread::createNotifies() {
	if (temp_localConnection = _localConnection.lock()) {
		temp_localConnection->setNotifications(_e_NotifiesList); // TODO пока без проверки на ошибки
	}
	else {
		// TODO если weak_ptr пуст
		return false;
	}
	temp_localConnection = nullptr;
	return true;
}

void NotifiedThread::switchDevice(const int event) {
	temp_localConnection = _localConnection.lock();
	if (temp_localConnection) {
		if (event == 0) { // Конвертер
			_converterMessagesList.clear();
			temp_localConnection->readConverterNotifies(_converterMessagesList);
			// TODO расшифровка сообщения
			// TODO реакция
		}
		else { // Контроллеры
			_controllerMessagesList.clear();
			temp_localConnection->readControllerNotifies(event - 1, _controllerMessagesList);
			parseControllerNotify();
			// TODO расшифровка сообщения
			// TODO реакция
		}
	}
}
/////////////// Приватные сценарии
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
			// TODO считывание событий
			// TODO вывод куда хочу
			break;
		case ZG_NF_CTR_CLOCK: 
			// TODO вызов функции установки текущего времени
			break;
		case ZG_NF_CTR_KEY_TOP: 
			// TODO хз
			break;
		case ZG_NF_CTR_ADDR_CHANGE: 
			// TODO обновить информацию о контроллере
			break;
		case ZG_NF_CTR_ERROR:
			// TODO ошибки
			break;
		default:
			// TODO критические ошибки
			break;
		}

		i++;
	}
}
