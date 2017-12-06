#pragma once
struct AvailableConnection;

class Connection
{
public:
	//Connection(const _ZG_ENUM_IPCVT_INFO, const std::vector<_ZP_PORT_INFO>, const ZP_PORT_TYPE);
	//Connection();
	Connection(std::unique_ptr<AvailableConnection>);
	~Connection();

	///////////////
	void setNewConnactionInfo(std::unique_ptr<AvailableConnection>);
	void addController(_ZG_CTR_INFO);
	void removeController(const int);
	bool initialConnections();
	///////////////

	///////////////
	void cvt_SetNotification(_ZG_CVT_NOTIFY_SETTINGS);
	void ctr_SetNotification(const int, _ZG_CTR_NOTIFY_SETTINGS);
	HRESULT cvt_GetNextMessage(); // TODO cvt_GetNextMessage
	HRESULT ctr_GetNextMessage(const int); // TODO ctr_GetNextMessage
	///////////////

#ifdef _DEBUG 
	static bool StaticTest();
#endif

	///////////////
	HANDLE* const get_hConvertor();
	std::shared_ptr<std::vector<std::unique_ptr<HANDLE>>> get_hController();
	//std::vector<_ZG_FIND_CTR_INFO>* const get_controllersInfo();
	///////////////

	///////////////
	std::unique_ptr<AvailableConnection> _connectionData;
	std::shared_ptr<HANDLE> _e_newInfo = nullptr; //Событие перезаписи данных
	std::shared_ptr<HANDLE> _e_destroyed = nullptr; // Событие уничтожения объекта
	///////////////

private:
	//int _addrOfOpenController;
	 
	std::unique_ptr<HANDLE> _hConvector = nullptr;
	std::vector<std::unique_ptr<HANDLE>> _hControllersList;

	bool openConnection();
	void closeConnection();
	void scanControllers();
	//bool openController(int); 
	void openControllers();
	//void closeController();
	void closeControllers();
	//void clearInfo();
};

