#include "stdafx.h"
#include "NotifiedThread.h"
#include "Connection.h"
#include "DataStructs.h"

NotifiedThread::NotifiedThread(std::shared_ptr<Connection> connection, std::shared_ptr<HANDLE> e_localExitThread) :
	_localConnection(connection),
	_e_localExitThread(e_localExitThread),
	_waitingArray(std::make_unique<std::vector<HANDLE>>())
{
	if (auto temp_localConnection = _localConnection.lock()) {
		_e_newInfo = temp_localConnection->_e_newInfo;
		_e_destroyed = temp_localConnection->_e_destroyed;
		getNewPointers(temp_localConnection);
		refreshWaitingArray();
	}
	else {
		// Throw connection
	}
}


NotifiedThread::~NotifiedThread()
{
}

void NotifiedThread::runListening(std::shared_ptr<Connection> connection, std::shared_ptr<HANDLE> localEvent) {
	try {
		std::thread NotifiedThread(&NotifiedThread::startListining, new NotifiedThread(connection, localEvent));
		NotifiedThread.detach();
	}
	catch (const std::exception& error) {
		std::cout << error.what();
	}
}

void NotifiedThread::startListining() {
	while (!_localConnection.expired()) {
		auto connection = _localConnection.lock();

		auto event = WaitForMultipleObjects(_waitingArray->size(), _waitingArray->data(), FALSE, INFINITE);

		switch (event) {
		case 0: // —ценарий 1
			ExitThread(0);
			break;
		case 1: // —ценарий 2
			ExitThread(0); 
			break;
		case 2: // —ценарий 3: ”ничтожение Connection
			ResetEvent(_waitingArray->at(event));
			ExitThread(0);
			break;
		case 3: // —ценарий 4: Ќовые данные Connection
			clearNotifyList();
			getNewPointers(_localConnection.lock());
			createNotifies();
			ResetEvent(_waitingArray->at(event));
			refreshWaitingArray();
			break;
		default:
			if((size_t)4 <= (size_t)event <= (size_t)4 + _waitingArray->size()) // —ценарий 5

				break;
			else { // —ценарий 6
				// TODO throw exception
				break;
			}
		}
	}
}

bool NotifiedThread::createNotifies() {
	if (auto temp_localConnection = _localConnection.lock()) {

		switch (temp_localConnection->setNotifications(_e_NotifiesList))

		try {
			//temp_localConnection->cvt_SetNotification(_converterNotifySettings);
			//
			//for (size_t i = 0; i < temp_hControllers->size(); i++) { // TODO ERROR

			//	_controllerNotifySettings.nReadEvIdx = temp_localConnection->_data->controlersIndexWriteRead->at(i).first; // TODO ERROR
			//	auto controllerEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
			//	_controllerNotifySettings.hEvent = &controllerEvent;

			//	temp_localConnection->ctr_SetNotification(i, _controllerNotifySettings);

			//	_e_getControllersNotifyList.push_back(std::move(controllerEvent));
			//}
		}
		catch (CommandError e) {
			std::cout << e.what() << "\n";
			return false;
		}
	}
	else {
		// TODO если weak_ptr пуст
		return false;
	}

	return true;
}

//void NotifiedThread::closeNotifies() {
//	try {
//		auto temp_localConnection = _localConnection.lock();
//		auto temp_hControllers = _hConctrollers.lock();
//
//		_e_getConverterNotify = nullptr;
//		_e_getControllersNotifyList.clear();
//
//		temp_localConnection->cvt_SetNotification();
//
//		for (size_t i = 0; i < temp_hControllers->size(); i++) {
//			temp_localConnection->ctr_SetNotification(i);
//		}
//	}
//	catch (const std::exception& error) {
//		std::cout << error.what() << "\n";
//	}
//
//	refreshWaitingArray();
//}


void NotifiedThread::refreshWaitingArray() {
	_waitingVariableArray.clear();
	_waitingArray->clear();
	
	if (!_e_NotifiesList.empty()) {
		std::copy(_e_NotifiesList.begin(), _e_NotifiesList.end(), _waitingVariableArray.begin());
	}

	*_waitingArray = _waitingConstArray;
	std::copy(_waitingVariableArray.begin(), _waitingVariableArray.end(), _waitingArray->end());
}

void NotifiedThread::getNewPointers(std::shared_ptr<Connection>& temp_localConnection) {
	//_hConverter = std::make_shared<HANDLE>(temp_localConnection->get_hConvertor());
	//_hConctrollers = temp_localConnection->get_hController();
	//_waitingConstArray = { *_globalExitThread, *_e_localExitThread, *temp_localConnection->_e_destroyed, *temp_localConnection->_e_newInfo, };
	//_waitingVariableArray = _waitingConstArray;
}

void NotifiedThread::clearNotifyList() {
	//_e_getConverterNotify = nullptr;
	_e_NotifiesList.clear();
}