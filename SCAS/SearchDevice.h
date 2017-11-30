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

	//static thread* StartThread() // TODO ¬опрос с созданием потока через статик

#ifdef _DEBUG
	static bool StaticTest();
#endif

private:
	
	std::unique_ptr<std::set<std::shared_ptr<AvailableConnection>>> _localAvaliableConnectionsSet;
	std::unique_ptr<std::vector<std::shared_ptr<Connection>>> _localConverterList = std::unique_ptr<std::vector<std::shared_ptr<Connection>>>(new std::vector<std::shared_ptr<Connection>>);
	std::unique_ptr<HANDLE> _hSearch;
	std::unique_ptr<AvailableConnection> _connectionData;
	std::unique_ptr<Connection> _currentConnection;
	std::unique_ptr<_ZP_SEARCH_PARAMS> _searchParams;
};

