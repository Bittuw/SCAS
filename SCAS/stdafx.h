// stdafx.h: ���������� ���� ��� ����������� ��������� ���������� ������
// ��� ���������� ������ ��� ����������� �������, ������� ����� ������������, ��
// �� ����� ����������
//

#pragma once

#include "targetver.h"

#include <exception>
#include <iostream>
#include <memory>
#include <stdio.h>
#include <tchar.h>
#include <vector>
#include <set>
#include <list>
#include <locale.h>
#include <thread>
#include <mutex>
#include <thread>
#include <ZGuard.h>
#include <ZPort.h>
#if !defined(ZGUARD_LINKONREQUEST)
#pragma comment(lib, "ZGuard.lib")
#elif !defined(ZPORT_LINKONREQUEST)
#pragma comment(lib, "ZGuard.lib")
#endif // !ZGUARD_LINKONREQUEST
#include <Utils.h>
#include "DataStructs.h"
#include "Exceptions.h"




// TODO: ���������� ����� ������ �� �������������� ���������, ����������� ��� ���������
