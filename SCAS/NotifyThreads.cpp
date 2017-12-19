#include "stdafx.h"
#include "NotifyThreads.h"
#include "NotifiedThread.h"
#include "DataStructs.h"

bool NotifyThreads::isRunning = false;

NotifyThreads::NotifyThreads() :
	_e_clearing(_converterInfoListTest->_e_clearing),
	_e_newlist(_converterInfoListTest->_e_newlist),
	_e_pushing(_converterInfoListTest->_e_pushing),
	_e_localExitThread(std::make_shared<HANDLE>(CreateEvent(NULL, TRUE, FALSE, NULL)))
{
	/*std::thread NotifyThread(&NotifyThreads::beginListning, this);
	NotifyThread.detach();*/
}


NotifyThreads::~NotifyThreads(){
	isRunning = false;
}

void NotifyThreads::runListening() {
	if (!isRunning) {
		try {
			std::thread NotifyThread(&NotifyThreads::beginListning, new NotifyThreads);
			NotifyThread.detach();
			isRunning = true;
		}
		catch (const std::exception& error) {
			std::cout << error.what();
		}
	}
	else {
		// TODO Throw log trace
	}
}

void NotifyThreads::beginListning() {
	std::vector<HANDLE> _waitingArray = {*_globalExitThread, *_e_newlist , *_e_pushing};

	while (*_globalExitThread) {

		auto event = (unsigned long)WaitForMultipleObjects(_waitingArray.size(), _waitingArray.data(), FALSE, INFINITE);

		switch (event) {
		case 0:
			SetEvent(*_e_localExitThread);
			ExitThread(0);
			break;
		case 1:
			// TODO log trace
			createNotifiedThreads();
			break;
		case 2:
			// TODO log trace
			createNotifiedThreads();
			break;
		default:
			//TODO log-trace
			ExitThread(0);
		}
	}
}

void NotifyThreads::createNotifiedThreads() {
	createThreads(_converterInfoListTest->untreatedConnections);
}
 
void NotifyThreads::createThreads(const int count) { // TODO make thread
	auto indexOfUntreated = _converterInfoListTest->size() - count;
	for (int i = indexOfUntreated; i < count; i++) {

		auto temp = _converterInfoListTest->at(i);
		NotifiedThread::runListening( temp, _e_localExitThread);
		_converterInfoListTest->untreatedConnections--;
	}
}

void NotifyThreads::StaticTest() {
	runListening();
	runListening();
}