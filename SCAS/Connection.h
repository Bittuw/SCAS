#pragma once

class Connection
{
public:
	Connection(const _ZG_ENUM_IPCVT_INFO, const std::vector<_ZP_PORT_INFO>, const ZP_PORT_TYPE);
	//Connection(MainInfo* const); // TODO рассмотреть варинат с внешней информацие о конверторе
	//Connection(const _ZG_ENUM_IPCVT_INFO, const std::vector<_ZP_PORT_INFO>, const ZP_PORT_TYPE); // Автосоединение с конвертором
	~Connection();

	bool openConnection();
	void scanControllers();
	bool openController(int);
	void closeController();

	//static Connection getAutoConnected(); // Автосоединение либо через конструктор
#ifdef _DEBUG 
	static bool TestConnection();
#endif

	HANDLE* const get_hConvertor();
	HANDLE* const get_hController();
	std::vector<_ZG_FIND_CTR_INFO>* const get_controllersInfo();

private:

	bool isOpenConvertor = false;
	bool isOpenController = false;
	int _addrOfOpenController;

	HANDLE* _hConvector = nullptr;
	HANDLE* _hController = nullptr;
	//MainInfo* _mainInfo;

	std::vector<_ZG_FIND_CTR_INFO> _controllersInfo;
	const std::vector<_ZP_PORT_INFO> _convertorPorts;
	const _ZG_ENUM_IPCVT_INFO _convertorInfo;

	const ZP_PORT_TYPE _portType;
	
};

