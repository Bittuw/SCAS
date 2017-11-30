#include "stdafx.h"
#include "NotifyThreads.h"


NotifyThreads::NotifyThreads() :
	_e_clearing(_converterInfoListTest->_e_clearing),
	_e_newlist(_converterInfoListTest->_e_newlist)
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

		switch (event) {
		case WAIT_OBJECT_0 + 0:
			break;
		case WAIT_OBJECT_0 + 1:
				continue;
			break;
		default:
			//TODO log-trace
			ExitThread(0);
		}
	}
}

bool NotifyThreads::createNotifiedThreads() {
	return false;
}

