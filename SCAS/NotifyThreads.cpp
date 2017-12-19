#include "stdafx.h"
#include "NotifyThreads.h"
#include "NotifiedThread.h"
#include "DataStructs.h"

NotifyThreads::NotifyThreads() :
	_e_clearing(_converterInfoListTest->_e_clearing),
	_e_newlist(_converterInfoListTest->_e_newlist),
	_e_localExitThread(std::make_shared<HANDLE>(CreateEvent(NULL, TRUE, FALSE, NULL)))
{
	std::thread NotifyThread(&NotifyThreads::beginListning, this);
	NotifyThread.detach();
}


NotifyThreads::~NotifyThreads(){}

void NotifyThreads::runListening() {
	if (!isRunning) {
		NotifyThreads notifies;
	}
	else {
		
	}
}

void NotifyThreads::beginListning() {
	std::vector<HANDLE> _waitingArray = {*_globalExitThread, *_e_newlist };

	while (*_globalExitThread) {

		auto event = (unsigned long)WaitForMultipleObjects(_waitingArray.size(), _waitingArray.data(), FALSE, INFINITE);

		switch (event) {
		case 0:
			ExitThread(0);
			break;
		case 1:
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
	/*else { // TODO сделать
		if ( _needSize > _notifiedThreadsList.size()) {
			createThreads(_needSize - _notifiedThreadsList.size());
		}
	}*/
}
 
void NotifyThreads::createThreads(const int count) { // TODO make thread
	for (int i = 0; i < count; i++) {

		auto temp = _converterInfoListTest->at(i);
		auto pointer = std::unique_ptr<std::thread>(new std::thread([&temp, this]()  {
			(new NotifiedThread(temp, _e_localExitThread))->startListining();
		}));
		pointer->join();
	}
}

