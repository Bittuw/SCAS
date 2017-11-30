#pragma once
#include "Connection.h"
#include "SpecialList.h"
class Connection;

struct AvailableConnection { // TODO возможная замена для MainInfo
	std::unique_ptr<_ZG_ENUM_IPCVT_INFO> converterInfo = nullptr; // Общая информация  о конверторе
	_ZP_PORT_INFO converterPorts[2]; // Список портов
	std::unique_ptr<std::vector<_ZG_FIND_CTR_INFO>> controllersInfo = nullptr; // Список конверторов
	std::unique_ptr<ZP_PORT_TYPE> portType = nullptr; // Тип подключения
	std::unique_ptr<std::mutex> connectionMutex = nullptr; // Мьютетс доступа
	bool isJoinable = false;
	//_ZG_CVT_OPEN_PARAMS openConverterParams; // TODO параметры подключения (Возможность задать)

	AvailableConnection() :
		converterInfo(new _ZG_ENUM_IPCVT_INFO),
		controllersInfo(new std::vector<_ZG_FIND_CTR_INFO>),
		portType(new ZP_PORT_TYPE),
		connectionMutex(new std::mutex)
	{
		ZeroMemory(&*converterInfo, sizeof(*converterInfo));
		converterInfo->cbSize = sizeof(_ZG_ENUM_IPCVT_INFO);
	}

	~AvailableConnection() { // TODO delete connection
		converterInfo = nullptr;
		controllersInfo = nullptr;
		portType = nullptr;
	}

	bool operator< (const AvailableConnection &right) {
		return converterInfo->nSn < right.converterInfo->nSn;
	}
};

static const auto _convertorsInfoList = std::unique_ptr<std::list<std::shared_ptr<Connection>>>(new std::list<std::shared_ptr<Connection>>);
static const auto _converterInfoListTest = std::unique_ptr<SpecialList>(&*(new SpecialList));
static const auto _globalExitThread = std::make_unique<HANDLE>(CreateEvent(NULL, TRUE, FALSE, NULL));
static const auto _globalNotifiedThreadReset = std::make_unique<HANDLE>(CreateEvent(NULL, TRUE, FALSE, NULL));
