#pragma once

struct AvailableConnection;
enum ErrorCode;

enum Action {
	ADD = 1,
	CLOSE = 2,
	CLEAR = 3
};

class Connection // TODO добавить поле статуса соединения
{
public:
	Connection(std::unique_ptr<AvailableConnection>);
	~Connection();

	/////////////// Сценарии
	void setNewConnactionInfo(std::unique_ptr<AvailableConnection>);
	//int addController(_ZG_FIND_CTR_INFO); // TODO сделать условие
	//void removeController(const int);
	ErrorCode initialConnections() noexcept; // Отрытие конвертора и создание/открытие контроллеров DONE
	ErrorCode closeConnections() noexcept; // Закрыть все подключения DONE
	ErrorCode reconnect() noexcept; // 
	ErrorCode getConnectionStatus(_Out_ bool&) noexcept; // Статус подключения конвертора DONE
	//ErrorCode addController(_ZG_FIND_CTR_INFO); // Добавить контроллер
	//ErrorCode removeController(); // Удалить контроллер (полностью)
	//ErrorCode reconnect();
	//AvailableConnection storeData();
	//AvailableConnection restoreData();
	///////////////

	/////////////// Оборачиваемые функции библиотеки SDK Guard
	//void _SetNotification();
	//void cvt_SetNotification(_ZG_CVT_NOTIFY_SETTINGS);
	void cvt_SetNotification();
	void ctr_SetNotification(const int, _ZG_CTR_NOTIFY_SETTINGS);
	void ctr_SetNotification(const int);
	///////////////

#ifdef _DEBUG 
	static bool StaticTest();
#endif

	/////////////// 
	std::unique_ptr<AvailableConnection> _data; // Принимает структуру хранения информации
	std::shared_ptr<HANDLE> _e_newInfo = nullptr; // Событие перезаписи данных **оставить
	std::shared_ptr<HANDLE> _e_destroyed = nullptr; // Событие уничтожения объекта **оставить
	///////////////

	ErrorCode errorStatus;

private:
	
	std::vector<HANDLE> _hControllersList;
	HANDLE _hConvector = NULL;
	_ZG_CVT_OPEN_PARAMS temp_Params;

	/////////////// Временная информация о текущем контроллере
	int temp_writeIndex = 0, temp_readIndex = 0;
	HANDLE temp_hController = NULL;
	_ZG_CTR_INFO temp_controllersDetailInfo;
	std::pair<int, int> temp_controlersIndexWriteRead;
	///////////////

	/////////////// Приватные сценарии
	bool tryOpenConverter(); // Попытка открытия конвертора DONE
	void tryCloseConverter(); // Попытка закрытия конвертора DONE
	void scanControllers(); // Сканирование контроллеров DONE
	void openControllers(); // Подключение контроллерров DONE
	void closeControllers(); // Закртыие контрллеров DONE
	void updateConverterInfo(bool); // Обновление информации о конверторе DONE
	void updateControllerInfo(Action, int = 0); // Обновление информации о контроллере DONE
	///////////////

	/////////////// Низкоуровневые функции команды
	HRESULT cvt_GetNextMessage(); // TODO cvt_GetNextMessage
	HRESULT ctr_GetNextMessage(const int); // TODO ctr_GetNextMessage
	/////////////// 

	/////////////// Низкоуровневые функции подключения
	void openConverter(); // DONE
	void closeConverter(); // DONE
	ZP_CONNECTION_STATUS getStatus(); // DONE
	void openController(const int); // DONE
	void readControllerIdxs(const int); // DONE
	void closeController(const int);  // DONE
	///////////////
};

