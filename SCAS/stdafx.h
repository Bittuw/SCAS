// stdafx.h: ���������� ���� ��� ����������� ��������� ���������� ������
// ��� ���������� ������ ��� ����������� �������, ������� ����� ������������, ��
// �� ����� ����������
//

#pragma once

#include "targetver.h"
#include <algorithm>
#include <exception>
#include <iostream>
#include <memory>
#include <stdio.h>
#include <tchar.h>
#include <vector>
#include <list>
#include <set>
#include <locale.h>
#include <thread>
#include <mutex>
#include <ZGuard.h>
#include <ZPort.h>
#if !defined(ZGUARD_LINKONREQUEST)
#pragma comment(lib, "ZGuard.lib")
#elif !defined(ZPORT_LINKONREQUEST)
#pragma comment(lib, "ZGuard.lib")
#endif // !ZGUARD_LINKONREQUEST
#include <Utils.h>
#include "Exceptions.h"
#include "SpecialList.h"


// TODO: ���������� ����� ������ �� �������������� ���������, ����������� ��� ���������
