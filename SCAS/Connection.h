#pragma once

struct AvailableConnection;
enum ErrorCode;

enum Action {
	ADD = 1, // Добавить контроллер
	CLOSE = 2, // Закрыть контроллер (+ очистка части, func->erase)
	CLEAR = 3, // Очистка буферов 
	CHANGE = 4, // Изменение ,
	REBASE = 5 // Переоткрытие или закрытие соединения
};

class Connection // TODO добавить поле статуса соединения
{
public:
	Connection(std::unique_ptr<AvailableConnection>);
	~Connection();

	/////////////// Сценарии TODO если exception то нужно читать ошибку и делать соответствующие выводы
	void setNewConnactionInfo(std::unique_ptr<AvailableConnection>);
	//int addController(_ZG_FIND_CTR_INFO); // TODO сделать условие
	//void removeController(const int);
	ErrorCode initialConnections() noexcept; // Отрытие конвертора и создание/открытие контроллеров DONE
	ErrorCode closeConnections() noexcept; // Закрыть все подключения DONE
	ErrorCode reconnect() noexcept; // Пересоздать соединение DONE
	ErrorCode getConnectionStatus(_Out_ bool&) noexcept; // Статус подключения конвертора DONE
	ErrorCode setNotifications(_Out_ std::vector<HANDLE>&) noexcept; // Установка уведомлений
	ErrorCode closeNotifications(); // Закрыть уведомления DONE
	ErrorCode readConverterNotifies(_Out_ std::vector<std::pair<UINT, LPARAM>>&) noexcept; // Чтение уведомлений конвертора DONE
	ErrorCode readControllerNotifies(const int, _Out_ std::vector<std::pair<UINT, LPARAM>>&) noexcept; // Чтение уведомления контроллера DONE
	ErrorCode readControllerEvent(const int, _Out_ std::vector<_ZG_CTR_EVENT>&); // Чтение событий контроллера
	//ErrorCode addController(_ZG_FIND_CTR_INFO); // Добавить контроллер
	//ErrorCode removeController(); // Удалить контроллер (полностью)
	//ErrorCode reconnect();
	//AvailableConnection storeData();
	//AvailableConnection restoreData();
	///////////////

	/////////////// Оборачиваемые функции библиотеки SDK Guard

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
	
	std::vector<std::pair<UINT, LPARAM>> _converterMessageList; // Прочитанные уведомления конвертора
	std::vector<std::pair<UINT, LPARAM>> _controllerMessageList; // Прочитанные уведомление контроллера
	std::vector<HANDLE> _hControllersList; // Список открытых контроллеров
	HANDLE _hConvector = NULL; // Конвертер
	_ZG_CVT_OPEN_PARAMS temp_Params; // Параметры открытия конвертора
	_ZG_CVT_NOTIFY_SETTINGS commonConverterSettings; // Общие настройки уведомлений от конвертора
	_ZG_CTR_NOTIFY_SETTINGS commonControllerSettings; // Общие найстройки уведомлений от контоллеров

	/////////////// Временная информация о текущем контроллере
	int temp_writeIndex = 0, temp_readIndex = 0;
	HANDLE temp_hController = NULL;
	_ZG_CTR_INFO temp_controllersDetailInfo;
	std::pair<int, int> temp_controlerIndexWriteRead;
	std::vector<_ZG_CTR_EVENT> temp_controllerEvents;
	///////////////

	/////////////// Приватные сценарии // TODO обработка исключений для итераций вызовов и вызов новых исключений
	bool tryOpenConverter(); // Попытка открытия конвертора DONE / итерация обработана
	void tryCloseConverter(); // Попытка закрытия конвертора DONE
	void scanControllers(); // Сканирование контроллеров DONE / итерация (возможно)
	void openControllers(); // Подключение контроллерров DONE / итерация
	void closeControllers(); // Закртыие контрллеров DONE
	void updateConverterInfo(bool); // Обновление информации о конверторе DONE
	void updateControllerInfo(Action, int = 0); // Обновление информации о контроллере DONE
	void trySetNotifications(_Out_ std::vector<HANDLE>&); // Установка уведомлений / итерация DONE
	void tryCloseNotifications(); // Закрыть все уведомления DONE
	void readConverterNotify(_Out_ std::vector<std::pair<UINT, LPARAM>>&); // Считать уведомление контроллера
	void readControllerNotify(const int, _Out_ std::vector<std::pair<UINT, LPARAM>>&); // Считать уведомление конвертора
	///////////////

	/////////////// Низкоуровневые функции-команды
	void cvt_SetNotification(_ZG_CVT_NOTIFY_SETTINGS = {}); // Установка уведомления для конвертора DONE
	void ctr_SetNotification(const int, _ZG_CTR_NOTIFY_SETTINGS = {}); // Установка уведомления для контроллера DONE
	HRESULT cvt_GetNextMessage(); // TODO cvt_GetNextMessage
	HRESULT ctr_GetNextMessage(const int); // TODO ctr_GetNextMessage
	void ReadControllerEvents(const int, _Out_ std::vector<_ZG_CTR_EVENT>&); // Чтение событий
	/////////////// Низкоуровневые функции-команды

	/////////////// Низкоуровневые функции
	void openConverter(); // DONE
	void closeConverter(); // DONE
	ZP_CONNECTION_STATUS getStatus(); // DONE
	void openController(const int); // DONE
	void readControllerIdxs(int = -1); // DONE
	int ReadEvents(const int, const int); // Читай до 5 событий за рас
	void closeController(const int);  // DONE
	///////////////

};

