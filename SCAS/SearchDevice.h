#pragma once
struct AvailableConnection;

class SearchDevice // in Thread
{

	//TODO ZG_SearchDevice
public:
	SearchDevice(std::unique_ptr<_ZP_SEARCH_PARAMS>);
	~SearchDevice();

	void scanNetwork();
	//void setDevicesList();
	//void compareList();

	//static thread* StartThread() // TODO Вопрос с созданием потока через статик

#ifdef _DEBUG
	static bool StaticTest();
#endif

private:
	
	std::set<std::shared_ptr<AvailableConnection>> _localAvaliableConnectionsSet; // Локальный список найденных конверторов
	std::vector<std::shared_ptr<Connection>> _localConverterList; // Локальный список подключенных конверторов
	std::unique_ptr<HANDLE> _hSearch; // Дескриптор поиска
	std::unique_ptr<AvailableConnection> _connectionData; // Текущий найденный конвертер
	std::unique_ptr<Connection> _currentConnection; // Текущий подключенный конвертер
	std::unique_ptr<_ZP_SEARCH_PARAMS> _searchParams; // Параметры поиска
};

