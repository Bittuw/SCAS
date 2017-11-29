#pragma once
struct AvailableConnection;

struct MainInfo
{
	_ZG_ENUM_IPCVT_INFO converterInfo;
	_ZP_PORT_INFO converterPorts[2];
	std::vector<_ZG_FIND_CTR_INFO>* controllersInfo;
	ZP_PORT_TYPE portType;
};


//struct AvailableConnection { // TODO ��������� ������ ��� MainInfo
//	_ZG_ENUM_IPCVT_INFO converterInfo; // ����� ����������  � ����������
//	std::vector<_ZP_PORT_INFO> converterPorts; // ������ ������
//	std::vector<_ZG_FIND_CTR_INFO> controllersInfo; // ������ �����������
//	ZP_PORT_TYPE portType; // ��� �����������
//	Connection* connection; // ���������� (��� ������ � �����������/�����������)�
//};

//std::shared_ptr<std::vector<AvailableConnetion>> convertorsInfoList = std::make_shared<std::vector<AvailableConnetion>>(new std::vector<AvailableConnetion>);


class SearchDevice
{

public:
	SearchDevice(std::unique_ptr<_ZP_SEARCH_PARAMS>);
	~SearchDevice();

	void scanNetwork();
	void addInfoList(std::unique_ptr<std::vector<AvailableConnection>>*);
	//void setDevicesList();
	//void compareList();

	//static thread* StartThread() // TODO ������ � ��������� ������ ����� ������

#ifdef _DEBUG
	static bool StaticTest();
#endif

private:

	std::unique_ptr<std::list<std::shared_ptr<Connection>>> _localConverterList = std::unique_ptr<std::list<std::shared_ptr<Connection>>>(new std::list<std::shared_ptr<Connection>>);
	std::unique_ptr<HANDLE> _hSearch;
	std::unique_ptr<AvailableConnection> _connectionData;
	std::unique_ptr<Connection> _currentConnection;
	std::unique_ptr<_ZP_SEARCH_PARAMS> _searchParams;
};

