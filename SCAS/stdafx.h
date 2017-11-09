// stdafx.h: включаемый файл дл€ стандартных системных включаемых файлов
// или включаемых файлов дл€ конкретного проекта, которые часто используютс€, но
// не часто измен€ютс€
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <vector>
#include <locale.h>
#include <ZGuard.h>
#include <ZPort.h>
#if !defined(ZGUARD_LINKONREQUEST)
#pragma comment(lib, "ZGuard.lib")
#elif !defined(ZPORT_LINKONREQUEST)
#pragma comment(lib, "ZGuard.lib")
#endif // !ZGUARD_LINKONREQUEST
#include <Utils.h>


// TODO: ”становите здесь ссылки на дополнительные заголовки, требующиес€ дл€ программы
