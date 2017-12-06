#include "stdafx.h"
#include "NotifiedThread.h"


NotifiedThread::NotifiedThread(std::shared_ptr<Connection> connection, std::shared_ptr<HANDLE> e_localExitThread) :
	_localConnection(connection),
	_e_localExitThread(e_localExitThread),
	_e_getConverterNotify(std::make_unique<HANDLE>(CreateEvent(NULL, TRUE, FALSE, NULL)))
{
	if (auto temp_localConnection = _localConnection.lock()) {
		_hConverter = std::make_shared<HANDLE>(temp_localConnection->get_hConvertor());
		_hConctrollers = temp_localConnection->get_hController();
		_e_newInfo = temp_localConnection->_e_newInfo;
		_e_destroyed = temp_localConnection->_e_destroyed;
		_waitingFirstArray = { *_globalExitThread, *_e_localExitThread, *temp_localConnection->_e_newInfo, *temp_localConnection->_e_destroyed };
		_waitingSecondArray = _waitingFirstArray;
	}
	else {
		// TODO throw connection
	}
}


NotifiedThread::~NotifiedThread()
{
}


void NotifiedThread::startListining() {
	while (!_localConnection.expired()) {
		auto const& const_waitingFirstArray = _waitingFirstArray;
		auto eventFirst = WaitForMultipleObjects(const_waitingFirstArray.size(), const_waitingFirstArray.data(), FALSE, INFINITY);

		switch (eventFirst)
		{
		case 0:
			// TODO log trace
			ExitThread(0);
			break;
		case 1:
			// TODO log trace
			ExitThread(0);
			break;
		case 2:
			ResetEvent(_waitingFirstArray.at(2));
			createNotify();
			break;
		default:
			// TODO log trace
			break;
		}

		_waitingSecondArray.push_back(*_e_getConverterNotify);
		_waitingSecondArray.insert(_waitingSecondArray.end(), _e_getControllersNotifyList.begin(), _e_getControllersNotifyList.end());
		auto const& const_waitingSecondArray = _waitingSecondArray;

		auto eventSecond = WaitForMultipleObjects(const_waitingSecondArray.size(), const_waitingSecondArray.data(), FALSE, INFINITY);

		}
	//while (!_localConnection.expired()) {
	//	if (auto temp_localConnection = _localConnection.lock()) {

	//		auto const& const_waitingFirstArray = _waitingFirstArray;
	//		auto eventFirst = WaitForMultipleObjects(_waitingFirstArray.size(), _waitingFirstArray.data(), FALSE, INFINITY);

	//		switchFirstEvent(eventFirst);
	//		
	//	}
	//	else {
	//		// TODO log trace срочно завтра проверить
	//	}
	//}
}

bool NotifiedThread::createNotify() {
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

				_controllerNotifySettings.nReadEvIdx = temp_localConnection->_connectionData->controlersIndexWriteRead->at(i).first;
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

void NotifiedThread::waitFirstEvent() {
	auto const& const_waitingFirstArray = _waitingFirstArray;
	auto eventFirst = WaitForMultipleObjects(const_waitingFirstArray.size(), const_waitingFirstArray.data(), FALSE, INFINITY);

	switch (eventFirst)
	{
	case 0:
		// TODO log trace
		ExitThread(0);
		break;
	case 1:
		// TODO log trace
		ExitThread(0);
		break;
	case 2:
		ResetEvent(_waitingFirstArray.at(2));
		createNotify();
		waitSecondEvent();
		break;
	default:
		// TODO log trace
		break;
	}
}

void NotifiedThread::waitSecondEvent() {
	_waitingSecondArray.push_back(*_e_getConverterNotify);
	_waitingSecondArray.insert(_waitingSecondArray.end(), _e_getControllersNotifyList.begin(), _e_getControllersNotifyList.end());
	auto const& const_waitingSecondArray = _waitingSecondArray;

	while(!_waitingFirstArray.at(2)) {
		auto eventSecond = WaitForMultipleObjects(const_waitingSecondArray.size(), const_waitingSecondArray.data(), FALSE, INFINITY);

		switch (eventSecond)
		{
		case 0:
			// TODO log trace
			ExitThread(0);
			break;
		case 1:
			// TODO log trace
			ExitThread(0);
			break;
		case 2:
			break;
		default:
			break;
		}
	}
}