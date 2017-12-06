#include "stdafx.h"
#include "NotifiedThread.h"
#include "Connection.h"
#include "DataStructs.h"

NotifiedThread::NotifiedThread(std::shared_ptr<Connection> connection, std::shared_ptr<HANDLE> e_localExitThread) :
	_localConnection(connection),
	_e_localExitThread(e_localExitThread),
	_e_getConverterNotify(std::make_unique<HANDLE>(CreateEvent(NULL, TRUE, FALSE, NULL))),
	_waitingArray(std::make_unique<std::vector<HANDLE>>(*(new std::vector<HANDLE>)))
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


void NotifiedThread::startListining() {
	while (!_localConnection.expired()) {
		
		auto event = WaitForMultipleObjects(_waitingArray->size(), _waitingArray->data(), FALSE, INFINITE);

		switch (event) {
		case 0: // Сценарий 1
			ExitThread(0);
			break;
		case 1: // Сценарий 2
			ExitThread(0); 
			break;
		case 2: // Сценарий 3: Уничтожение Connection
			ResetEvent(_waitingArray->at(event));
			ExitThread(0);
			break;
		case 3: // Сценарий 4: Новые данные Connection
			clearNotifyList();
			getNewPointers(_localConnection.lock());
			createNotifies();
			ResetEvent(_waitingArray->at(event));
			refreshWaitingArray();
			break;
		default:
			if(4 <= event <= 4 + _waitingArray->size()) // Сценарий 5

				break;
			else { // Сценарий 6
				// TODO throw exception
				break;
			}
		}
	}
}

bool NotifiedThread::createNotifies() {
	if (auto temp_localConnection = _localConnection.lock()) {

		auto temp_hConverter = _hConverter.lock();
		auto temp_hControllers = _hConctrollers.lock();

		_ZG_CVT_NOTIFY_SETTINGS _converterNotifySettings = { 0 };
		_ZG_CTR_NOTIFY_SETTINGS _controllerNotifySettings = { 0 };

		_converterNotifySettings.nNMask = ZG_NF_CVT_CTR_EXIST | ZG_NF_CVT_CTR_CHANGE | ZG_CVTN_CONNECTION_CHANGE | ZG_NF_CVT_ERROR;
		_converterNotifySettings.hEvent = &*_e_getConverterNotify;
		_converterNotifySettings.nScanCtrsPeriod = 2000; // Период сканирования контроллеров

		_controllerNotifySettings.nNMask = ZG_NF_CTR_NEW_EVENT | ZG_NF_CTR_CLOCK | ZG_NF_CTR_KEY_TOP;
		_controllerNotifySettings.nCheckStatePeriod = 500;

		try {
			temp_localConnection->cvt_SetNotification(_converterNotifySettings);
			
			for (size_t i = 0; i < temp_hControllers->size(); i++) {

				_controllerNotifySettings.nReadEvIdx = temp_localConnection->_connectionData->controlersIndexWriteRead->at(i).first; // TODO ERROR
				auto controllerEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
				_controllerNotifySettings.hEvent = &controllerEvent;

				temp_localConnection->ctr_SetNotification(i, _controllerNotifySettings);

				_e_getControllersNotifyList.push_back(std::move(controllerEvent));
			}
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

	if (!_e_getConverterNotify)
		_waitingVariableArray.push_back(*_e_getConverterNotify);

	if (!_e_getControllersNotifyList.empty())
		_waitingVariableArray.insert(_waitingVariableArray.end(), _e_getControllersNotifyList.begin(), _e_getControllersNotifyList.end());

	*_waitingArray = _waitingConstArray;
	_waitingArray->insert(_waitingArray->end(), _waitingVariableArray.begin(), _waitingVariableArray.end());
}

void NotifiedThread::getNewPointers(std::shared_ptr<Connection>& temp_localConnection) {
	_hConverter = std::make_shared<HANDLE>(temp_localConnection->get_hConvertor());
	_hConctrollers = temp_localConnection->get_hController();
	_waitingConstArray = { *_globalExitThread, *_e_localExitThread, *temp_localConnection->_e_destroyed, *temp_localConnection->_e_newInfo, };
	_waitingVariableArray = _waitingConstArray;
}

void NotifiedThread::clearNotifyList() {
	_e_getConverterNotify = nullptr;
	_e_getControllersNotifyList.clear();
}