#pragma once

#ifndef DATA_STRUCTS
#define DATA_STRUCTS

#include <memory>
#include <vector>
#include <mutex>
#include "Zguard.h"
#include "SpecialList.h"

struct Available_Connection {

	std::shared_ptr<_ZG_ENUM_IPCVT_INFO> converterInfo = nullptr; // ����� ����������  � ���������� TODO to binary file
	std::shared_ptr<_ZG_CVT_INFO> converterDetailInfo = nullptr; // ���������� ����� �������� ����������
	std::shared_ptr<std::vector<_ZP_PORT_INFO>> converterPorts = nullptr; // ������ ������ ���������� TODO to binary file
	bool converterStatus = false; // ������� �� ����������
	
	std::shared_ptr<std::vector<_ZG_FIND_CTR_INFO>> controllersInfo = nullptr; // ������ ������������ TODO to binary file
	std::shared_ptr<std::vector<_ZG_CTR_INFO>> controllersDetailInfo = nullptr; // ���������� ����� �������� ����������
	std::shared_ptr<std::vector<bool>> controllersStatus = nullptr; // ����������� �����������
	std::shared_ptr<std::vector<std::pair<int, int>>> controllersIndexWriteRead = nullptr; // ������ ���������� ������� ������/������

	ZP_PORT_TYPE portType; // ��� �����������

	std::shared_ptr<std::mutex> mutex = nullptr; // ������� �������

	Available_Connection(const Available_Connection&) = default;


	Available_Connection() :
		converterInfo(new _ZG_ENUM_IPCVT_INFO),
		converterDetailInfo(new _ZG_CVT_INFO),
		converterPorts(new  std::vector<_ZP_PORT_INFO>),
		controllersInfo(new std::vector<_ZG_FIND_CTR_INFO>),
		controllersStatus(new std::vector<bool>),
		controllersDetailInfo(new std::vector<_ZG_CTR_INFO>),
		controllersIndexWriteRead(new std::vector<std::pair<int, int>>),
		mutex(new std::mutex)
	{
		ZeroMemory(&*converterInfo, sizeof(*converterInfo));
		converterInfo->cbSize = sizeof(_ZG_ENUM_IPCVT_INFO);
		converterPorts->resize(2);
	}

	~Available_Connection() {
		converterInfo = nullptr;
		converterDetailInfo = nullptr;
		converterPorts = nullptr;
		controllersInfo = nullptr;
		controllersStatus = nullptr;
		controllersDetailInfo = nullptr;
		controllersIndexWriteRead = nullptr;
		mutex = nullptr;
	}

	bool operator< (const Available_Connection &right) {
		return converterInfo->nSn < right.converterInfo->nSn;
	}
};

//extern const std::unique_ptr<SpecialList> _converterInfoListTest;
extern const std::unique_ptr<HANDLE> _globalExitThread;
extern const std::unique_ptr<HANDLE> _globalNotifiedThreadReset;


extern LPCTSTR EventTypeList[];
extern LPCTSTR DirectList[];
#endif