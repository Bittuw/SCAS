#pragma once
struct MainInfo
{
	 _ZG_ENUM_IPCVT_INFO converterInfo;
	_ZP_PORT_INFO converterPorts[2];
	std::vector<_ZG_FIND_CTR_INFO>* controllersInfo;
	ZP_PORT_TYPE portType = ZP_PORT_IP;
};

std::shared_ptr<std::vector<MainInfo>> convertorsInfoList = std::make_shared<std::vector<MainInfo>>(new std::vector<MainInfo>);

class SearchDevice
{

public:
	SearchDevice(const _ZP_SEARCH_PARAMS);
	//SearchDevice(shared_ptr<std::vector<MainInfo>>)
	~SearchDevice();

	void scanNetwork();
	void compareList();

	//static thread* createThread() // TODO ¬опрос с созданием потока через статик
private:

	HANDLE* _hSearch;
	MainInfo* _MainInfo;
	const _ZP_SEARCH_PARAMS _searchParams;
};

