#pragma once
struct AvailableConnection;

class Connection
{
public:
	//Connection(const _ZG_ENUM_IPCVT_INFO, const std::vector<_ZP_PORT_INFO>, const ZP_PORT_TYPE);
	Connection();
	Connection(std::unique_ptr<AvailableConnection>); // TODO рассмотреть варинат с внешней информацие о конверторе
	~Connection();

	bool openConnection();
	void closeConnection();
	void scanControllers();
	bool openController(int);
	void closeController();
	void setPtr(std::unique_ptr<AvailableConnection>);
	//bool prepareForNewData(std::unique_ptr<AvailableConnection>); // TODO переиспользование экземпл€ра
	//static Connection getAutoConnected(); // јвтосоединение либо через конструктор
#ifdef _DEBUG 
	static bool StaticTest();
#endif

	HANDLE* const get_hConvertor();
	HANDLE* const get_hController();
	std::vector<_ZG_FIND_CTR_INFO>* const get_controllersInfo();

	std::unique_ptr<AvailableConnection> _connectionData;
private:

	bool isOpenConvertor = false;
	bool isOpenController = false;
	int _addrOfOpenController;

	std::unique_ptr<HANDLE> _hConvector = nullptr;
	std::unique_ptr<HANDLE> _hController = nullptr;
};

