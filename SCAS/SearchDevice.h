#pragma once
struct AvailableConnection;

struct MainInfo
{
	_ZG_ENUM_IPCVT_INFO converterInfo;
	_ZP_PORT_INFO converterPorts[2];
	std::vector<_ZG_FIND_CTR_INFO>* controllersInfo;
	ZP_PORT_TYPE portType;
};


//struct AvailableConnection { // TODO возможная замена для MainInfo
//	_ZG_ENUM_IPCVT_INFO converterInfo; // Общая информация  о конверторе
//	std::vector<_ZP_PORT_INFO> converterPorts; // Список портов
//	std::vector<_ZG_FIND_CTR_INFO> controllersInfo; // Список конверторов
//	ZP_PORT_TYPE portType; // Тип подключения
//	Connection* connection; // Соединение (Для работы с конвертором/контроллеро)м
//};

//std::shared_ptr<std::vector<AvailableConnetion>> convertorsInfoList = std::make_shared<std::vector<AvailableConnetion>>(new std::vector<AvailableConnetion>);


class SearchDevice
{

public:
	SearchDevice(_ZP_SEARCH_PARAMS *const);
	~SearchDevice();

	void scanNetwork();
	void addInfoList(std::unique_ptr<std::vector<AvailableConnection>> *);
	//void compareList();

	//static thread* StartThread() // TODO Вопрос с созданием потока через статик

#ifdef _DEBUG
	static bool StaticTest();
#endif

private:

	HANDLE* _hSearch;
	MainInfo* _MainInfo;
	_ZP_SEARCH_PARAMS* const _searchParams;
};

