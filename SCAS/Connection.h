#pragma once

struct AvailableConnection;

class Connection // TODO добавить поле статуса соединения
{
public:
	Connection(std::unique_ptr<AvailableConnection>);
	~Connection();

	///////////////
	void setNewConnactionInfo(std::unique_ptr<AvailableConnection>);
	int addController(_ZG_FIND_CTR_INFO); // TODO сделать условие
	void removeController(const int);
	bool initialConnections();
	///////////////

	/////////////// оборачиваемые функции библиотеки SDK Guard
	void _SetNotification();
	void cvt_SetNotification(_ZG_CVT_NOTIFY_SETTINGS);
	void cvt_SetNotification();
	void ctr_SetNotification(const int, _ZG_CTR_NOTIFY_SETTINGS);
	void ctr_SetNotification(const int);
	HRESULT cvt_GetNextMessage(); // TODO cvt_GetNextMessage
	HRESULT ctr_GetNextMessage(const int); // TODO ctr_GetNextMessage
	///////////////

#ifdef _DEBUG 
	static bool StaticTest();
#endif

	///////////////
	HANDLE* const get_hConvertor();
	std::shared_ptr<std::vector<HANDLE>> get_hController();
	///////////////

	///////////////
	std::unique_ptr<AvailableConnection> _data; // Принимает новый ресур
	std::shared_ptr<HANDLE> _e_newInfo = nullptr; // Событие перезаписи данных **оставить
	std::shared_ptr<HANDLE> _e_destroyed = nullptr; // Событие уничтожения объекта **оставить
	///////////////

private:
	//int _addrOfOpenController;
	
	std::vector<HANDLE> _hControllersList;
	HANDLE _hConvector;
	
	void closeConverter();
	void scanControllers(); 
	void openControllers();
	void closeControllers();

	/////////////// Низкоуровневые функции подключения
	void openController(const int);
	void openConverter();
	void closeController(const int);
	///////////////
};

