#include "stdafx.h"
#include "DataStructs.h"

const std::unique_ptr<std::list<std::shared_ptr<Connection>>> _convertorsInfoList = std::make_unique<std::list<std::shared_ptr<Connection>>>();
const std::unique_ptr<SpecialList> _converterInfoListTest = std::make_unique<SpecialList>();
const std::unique_ptr<HANDLE> _globalExitThread = std::make_unique<HANDLE>(CreateEvent(NULL, TRUE, FALSE, NULL));
const std::unique_ptr<HANDLE> _globalNotifiedThreadReset = std::make_unique<HANDLE>(CreateEvent(NULL, TRUE, FALSE, NULL));