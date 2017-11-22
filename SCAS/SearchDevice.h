#pragma once

struct MainInfo
{
	_ZG_ENUM_IPCVT_INFO converterInfo;
	_ZP_PORT_INFO converterPorts[2];
	std::vector<_ZG_FIND_CTR_INFO>* controllersInfo;
	ZP_PORT_TYPE portType;
};


struct AvailableConnetion { // TODO ��������� ������ ��� MainInfo
	_ZG_ENUM_IPCVT_INFO converterInfo; // ����� ����������  � ����������
	std::vector<_ZP_PORT_INFO> converterPorts; // ������ ������
	std::vector<_ZG_FIND_CTR_INFO> controllersInfo; // ������ �����������
	ZP_PORT_TYPE portType; // ��� �����������
	Connection* connection; // ���������� (��� ������ � �����������/������������)
};
//std::shared_ptr<std::vector<MainInfo>> convertorsInfoList = std::make_shared<std::vector<MainInfo>>(new std::vector<MainInfo>);

class SearchDevice
{

public:
	SearchDevice(_ZP_SEARCH_PARAMS *const);
	~SearchDevice();

	void scanNetwork();
	void compareList();

	//static thread* createThread() // TODO ������ � ��������� ������ ����� ������

#ifdef _DEBUG
	static bool TestClass();
#endif

private:

	HANDLE* _hSearch;
	MainInfo* _MainInfo;
	_ZP_SEARCH_PARAMS* const _searchParams;
};

