#include "stdafx.h"
#include "DataStructs.h"

const std::unique_ptr<std::list<std::shared_ptr<Connection>>> _convertorsInfoList = std::make_unique<std::list<std::shared_ptr<Connection>>>();
const std::unique_ptr<SpecialList> _converterInfoListTest = std::make_unique<SpecialList>();
const std::unique_ptr<HANDLE> _globalExitThread = std::make_unique<HANDLE>(CreateEvent(NULL, TRUE, FALSE, NULL));
const std::unique_ptr<HANDLE> _globalNotifiedThreadReset = std::make_unique<HANDLE>(CreateEvent(NULL, TRUE, FALSE, NULL));
const std::unique_ptr<std::vector<_ZG_CTR_EVENT>> testList = std::make_unique<std::vector<_ZG_CTR_EVENT>>();

LPCTSTR EventTypeList[] = {
	TEXT(""),
	TEXT("Open button"),				// ������� ������� �������
	TEXT("Key not found"),				// ���� �� ������ � ����� ������
	TEXT("Open key"),					// ���� ������, ����� �������
	TEXT("Key unscheduled"),			// ���� ������, ������ �� ��������
	TEXT("Open RS485"),					// ������� ���������� �� ����
	TEXT("Door is blocked (key)"),		// ���� ������, ����� �������������
	TEXT("Door is blocked (button)"),	// ������� ������� ��������������� ����� �������
	TEXT("Door is broken"),				// ����� ��������
	TEXT("Door is left open"),			// ����� ��������� �������� (timeout)
	TEXT("Passage"),					// ������ ���������
	TEXT("Sensor 1"),					// �������� ������ 1
	TEXT("Sensor 2"),					// �������� ������ 2
	TEXT("Controller is rebooted"),		// ������������ �����������
	TEXT("Button is disabled"),			// ������������� ������ ����������
	TEXT("Double pass"),				// ������� �������� �������
	TEXT("Door opened"),				// ����� ������� ������
	TEXT("Door closed"),				// ����� �������
	TEXT("Power off"),					// ������� �������
	TEXT("Power is on (ElectroControl)"),	// ��������� ��������������
	TEXT("Power is off (ElectroControl)"),	// ��������� ��������������
	TEXT("Enable the lock (trigger)"),		// ��������� ����� (�������)
	TEXT("Disable the lock (trigger)"),	// ���������� ����� (�������)
	TEXT("Changed state Mode"),			// ��������� ��������� �����
	TEXT("Changed state Fire"),			// ��������� ��������� ������
	TEXT("Changed state Security"),		// ��������� ��������� ������
	TEXT("Unknown key"),				// ����������� ����
	TEXT("Passage in the gateway"),		// �������� ���� � ����
	TEXT("Blocked the entrance to the gateway (busy)"),		// ������������ ���� � ���� (�����)
	TEXT("Allowed to enter the gateway"),	// �������� ���� � ����
	TEXT("AntiPassBack"),				// ������������ ������ (�����������)
	TEXT("Hotel40"),
	TEXT("Hotel41")
};
//
LPCTSTR DirectList[] = {
	TEXT(""),
	TEXT("IN"),   // ����
	TEXT("OUT")   // �����
};