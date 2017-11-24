// stdafx.h: включаемый файл для стандартных системных включаемых файлов
// или включаемых файлов для конкретного проекта, которые часто используются, но
// не часто изменяются
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
#include "ListListener.h"
//#include "FindDevices.h"



// TODO: Установите здесь ссылки на дополнительные заголовки, требующиеся для программы
// TODO Заменить include в .cpp на icnlude в .h