#pragma once

#include "DataBaseStructs.h"

class Connection;

enum ErrorCode {
	NotDefined = 0,
	Success = 1,
	ConverterOpenFail = 2,
	ConverterCommandFail = 3,
	ControllerOpenFail = 4,
	ControllerCommandFail = 5,
	ConnectionCommandFail = 6
};

struct AvailableConnection {

	std::shared_ptr<_ZG_ENUM_IPCVT_INFO> converterInfo = nullptr; // Общая информация  о конверторе TODO to binary file
	std::shared_ptr<_ZG_CVT_INFO> converterDetailInfo = nullptr; // Информация после открытия соединения
	std::shared_ptr<std::vector<_ZP_PORT_INFO>> converterPorts = nullptr; // Список портов конвертора TODO to binary file
	bool converterStatus = false; // Создано ли соединение
	
	std::shared_ptr<std::vector<_ZG_FIND_CTR_INFO>> controllersInfo = nullptr; // Список контроллеров TODO to binary file
	std::shared_ptr<std::vector<_ZG_CTR_INFO>> controllersDetailInfo = nullptr; // Информация после открытия соединения
	std::shared_ptr<std::vector<bool>> controllersStatus = nullptr; // Доступность контроллера
	std::shared_ptr<std::vector<std::pair<int, int>>> controllersIndexWriteRead = nullptr; // Список указателей индеков записи/чтения

	ZP_PORT_TYPE portType; // Тип подключения

	std::unique_ptr<std::mutex> mutex = nullptr; // Мьютетс доступа
	

	AvailableConnection() :
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

	~AvailableConnection() {
		converterInfo = nullptr;
		converterDetailInfo = nullptr;
		converterPorts = nullptr;
		controllersInfo = nullptr;
		controllersStatus = nullptr;
		controllersDetailInfo = nullptr;
		controllersIndexWriteRead = nullptr;
		mutex = nullptr;
	}

	bool operator< (const AvailableConnection &right) {
		return converterInfo->nSn < right.converterInfo->nSn;
	}
};

extern const std::unique_ptr<SpecialList> _converterInfoListTest;
extern const std::unique_ptr<HANDLE> _globalExitThread;
extern const std::unique_ptr<HANDLE> _globalNotifiedThreadReset;
//extern const std::unique_ptr<std::vector<_ZG_CTR_EVENT>> testList;

extern LPCTSTR EventTypeList[];
extern LPCTSTR DirectList[];
