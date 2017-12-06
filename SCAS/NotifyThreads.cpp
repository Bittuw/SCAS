#include "stdafx.h"
#include "NotifyThreads.h"


NotifyThreads::NotifyThreads() :
	_e_clearing(_converterInfoListTest->_e_clearing),
	_e_newlist(_converterInfoListTest->_e_newlist),
	_e_localExitThread(std::make_shared<HANDLE>(CreateEvent(NULL, TRUE, FALSE, NULL)))
{
	_localConverterList = _converterInfoListTest->getCopyList();
}


NotifyThreads::~NotifyThreads()
{

}


void NotifyThreads::beginListning() {
	const HANDLE _waitongArray[] = {*_globalExitThread, *_e_newlist};

	while (!*_globalExitThread) {

		auto event = WaitForMultipleObjects(_countof(_waitongArray), _waitongArray, FALSE, INFINITY);

		unsigned long temp = event;
		switch (event) {
		case WAIT_OBJECT_0 + 0:
			ExitThread(0);
			break;
		case WAIT_OBJECT_0 + 1:
			createNotifiedThreads();
			break;
		default:
			//TODO log-trace
			ExitThread(0);
		}
	}
}

void NotifyThreads::createNotifiedThreads() {
	auto _needSize = (size_t)_converterInfoListTest->size();

	if (_notifiedThreadsList.empty()) {
		createThreads(_converterInfoListTest->size());
	}
	else {
		if ( _needSize > _notifiedThreadsList.size()) {
			createThreads(_needSize - _notifiedThreadsList.size());
		}
	}
}
 
void NotifyThreads::createThreads(const int count) { // TODO make thread
	for (int i = 0; i <= count; i++) {
	//	auto pointer = std::unique_ptr<std::thread>(); // TODO сделать создание потока NotifiedThread
	//	_notifiedThreadsList.push_back(pointer);
	}
}