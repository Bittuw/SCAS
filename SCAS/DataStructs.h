#pragma once

class Connection;

struct AvailableConnection {
	std::unique_ptr<_ZG_ENUM_IPCVT_INFO> converterInfo = nullptr; // Общая информация  о конверторе
	std::unique_ptr<_ZG_CVT_INFO> converterDetailInfo = nullptr; // Информация после открытия соединения
	_ZP_PORT_INFO converterPorts[2]; // Список портов конвертора

	std::unique_ptr<std::vector<_ZG_FIND_CTR_INFO>> controllersInfo = nullptr; // Список конверторов
	std::unique_ptr<std::vector<_ZG_CTR_INFO>> controllersDetailInfo = nullptr; // Информация после открытия соединения
	std::unique_ptr<std::vector<std::pair<int, int>>> controlersIndexWriteRead = nullptr; // Список указателей индеков чтения/записи

	std::unique_ptr<ZP_PORT_TYPE> portType = nullptr; // Тип подключения

	std::unique_ptr<std::mutex> connectionMutex = nullptr; // Мьютетс доступа
	//std::unique_ptr<std::vector<std::mutex>> controllersMutexs = nullptr; // Список мютексов доступа к контроллерам

	bool isConverterJoinable = false; // Создано ли соединение
	//std::vector<bool> isControllersJoinable; // C какими контроллерами открыто соединение

	AvailableConnection() :
		converterInfo(new _ZG_ENUM_IPCVT_INFO),
		converterDetailInfo(new _ZG_CVT_INFO),

		controllersInfo(new std::vector<_ZG_FIND_CTR_INFO>),
		controllersDetailInfo(new std::vector<_ZG_CTR_INFO>),
		controlersIndexWriteRead(new std::vector<std::pair<int, int>>),

		portType(new ZP_PORT_TYPE),
		connectionMutex(new std::mutex)
	{
		ZeroMemory(&*converterInfo, sizeof(*converterInfo));
		converterInfo->cbSize = sizeof(_ZG_ENUM_IPCVT_INFO);
	}

	~AvailableConnection() {
		converterInfo = nullptr;
		converterDetailInfo = nullptr;
		controllersInfo = nullptr;
		controllersDetailInfo = nullptr;
		portType = nullptr;
		connectionMutex = nullptr;
	}

	bool operator< (const AvailableConnection &right) {
		return converterInfo->nSn < right.converterInfo->nSn;
	}
};

extern const std::unique_ptr<std::list<std::shared_ptr<Connection>>> _convertorsInfoList;
extern const std::unique_ptr<SpecialList> _converterInfoListTest;
extern const std::unique_ptr<HANDLE> _globalExitThread;
extern const std::unique_ptr<HANDLE> _globalNotifiedThreadReset;