// stdafx.h: включаемый файл дл€ стандартных системных включаемых файлов
// или включаемых файлов дл€ конкретного проекта, которые часто используютс€, но
// не часто измен€ютс€
//

#pragma once

#include "targetver.h"

#include <exception>
#include <iostream>
#include <memory>
#include <stdio.h>
#include <tchar.h>
#include <vector>
#include <locale.h>
#include <ZGuard.h>
#include <ZPort.h>
#include <thread>
#if !defined(ZGUARD_LINKONREQUEST)
#pragma comment(lib, "ZGuard.lib")
#elif !defined(ZPORT_LINKONREQUEST)
#pragma comment(lib, "ZGuard.lib")
#endif // !ZGUARD_LINKONREQUEST
#include <Utils.h>
#include "Exceptions.h"
#include "SearchDevice.h"
#include "Connection.h"
//#include "FindDevices.h"



// TODO: ”становите здесь ссылки на дополнительные заголовки, требующиес€ дл€ программы
