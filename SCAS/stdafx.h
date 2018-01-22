// stdafx.h: включаемый файл дл€ стандартных системных включаемых файлов
// или включаемых файлов дл€ конкретного проекта, которые часто используютс€, но
// не часто измен€ютс€
//

#pragma once

#include "targetver.h"
#include <algorithm>
#include <exception>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <memory>
#include <stdio.h>
#include <tchar.h>
#include <vector>
#include <queue>
#include <list>
#include <map>
#include <locale.h>
#include <thread>
#include <mutex>
#include <mysql_devapi.h>
#include <ZGuard.h>
#include <ZPort.h>
#include "Logger.h"
#if !defined(ZGUARD_LINKONREQUEST)
#pragma comment(lib, "ZGuard.lib")
#elif !defined(ZPORT_LINKONREQUEST)
#pragma comment(lib, "ZGuard.lib")
#endif // !ZGUARD_LINKONREQUEST
#include "Exceptions.h"
#include "SpecialList.h"


// TODO: ”становите здесь ссылки на дополнительные заголовки, требующиес€ дл€ программы
