#pragma once

#include "DataStructs.h"
#include "Main_Connection_Info.h"
//
//struct Available_Connection;
//
//enum Action {
//	ADD = 0, // Добавить контроллер
//	CLOSE = 1, // Закрыть контроллер (+ очистка части, func->erase)
//	CLEAR = 2, // Очистка буферов 
//	CHANGE = 3, // Изменение ,
//	REBASE = 4, // Переоткрытие или закрытие соединения
//	ADDERR = 5,
//	CHANGEERR = 6
//};
//
//static std::string ActionList[]{
//	std::string("ADD"),
//	std::string("CLOSE"),
//	std::string("CLEAR"),
//	std::string("CHANGE"),
//	std::string("REBASE"),
//	std::string("ADDERR"),
//	std::string("CHANGEERR")
//};
//
//class Connection // TODO необходиом обрабатывать ErrorCode
//{
//public:
//	Connection(std::unique_ptr<Available_Connection>&);
//	~Connection();
//
//	/////////////// Сценарии TODO если exception то нужно читать ошибку и делать соответствующие выводы
//	void setNewConnactionInfo(std::unique_ptr<Available_Connection>);
//	//int addController(_ZG_FIND_CTR_INFO); // TODO сделать условие
//	//void removeController(const int);
//	Main_Connection_Basic_Info_Types::Connection_Error_Code initialConnections() noexcept; // Отрытие конвертора и создание/открытие контроллеров DONE
//	Main_Connection_Basic_Info_Types::Connection_Error_Code closeConnections() noexcept; // Закрыть все подключения DONE
//	Main_Connection_Basic_Info_Types::Connection_Error_Code reconnect() noexcept; // Пересоздать соединение DONE
//	Main_Connection_Basic_Info_Types::Connection_Error_Code getConnectionStatus(_Out_ bool&) noexcept; // Статус подключения конвертора DONE
//	Main_Connection_Basic_Info_Types::Connection_Error_Code setNotifications(_Out_ std::vector<HANDLE>&) noexcept; // Установка уведомлений
//	Main_Connection_Basic_Info_Types::Connection_Error_Code closeNotifications(); // Закрыть уведомления DONE
//	Main_Connection_Basic_Info_Types::Connection_Error_Code readConverterNotifies(_Out_ std::vector<std::pair<UINT, LPARAM>>&) noexcept; // Чтение уведомлений конвертора DONE
//	Main_Connection_Basic_Info_Types::Connection_Error_Code addController(_ZG_FIND_CTR_INFO);
//	Main_Connection_Basic_Info_Types::Connection_Error_Code removeController(_ZG_FIND_CTR_INFO);
//	//ErrorCode setControllerKeysBase(const int, std::vector<type-error>); // Установка базы ключей
//	//ErrorCode getControllerKeyBase(const int, _Out_ std::vector<type-error>); // Получение базу ключей
//	Main_Connection_Basic_Info_Types::Connection_Error_Code readControllerNotifies(const int, _Out_ std::vector<std::pair<UINT, LPARAM>>&) noexcept; // Чтение уведомления контроллера DONE
//	Main_Connection_Basic_Info_Types::Connection_Error_Code readControllerEvent(const int, _Out_ std::vector<_ZG_CTR_EVENT>&); // Чтение событий контроллера
//	//ErrorCode readControllerEvents(const int, _Out_ std::vector<_ZG_EVENT>&) // Чтение всех событий
//	Main_Connection_Basic_Info_Types::Connection_Error_Code setControllerTime(const int); // Установка времени контроллера DONE
//	//AvailableConnection storeData();
//	//AvailableConnection restoreData();
//	///////////////
//
//	/////////////// Утилиты
//	const HANDLE& getControllerHandle(const int);
//	///////////////
//
//#ifdef _DEBUG 
//	static bool StaticTest();
//#endif
//
//	/////////////// 
//	std::unique_ptr<Available_Connection> _data; // Принимает структуру хранения информации
//	std::shared_ptr<HANDLE> _e_newInfo = nullptr; // Событие перезаписи данных **оставить
//	std::shared_ptr<HANDLE> _e_destroyed = nullptr; // Событие уничтожения объекта **оставить
//	///////////////
//
//	Main_Connection_Basic_Info_Types::Connection_Error_Code errorStatus;
//
//private:
//	
//	std::vector<std::pair<UINT, LPARAM>> _converterMessageList; // Прочитанные уведомления конвертора
//	std::vector<std::pair<UINT, LPARAM>> _controllerMessageList; // Прочитанные уведомление контроллера
//	std::vector<HANDLE> _hControllersList; // Список открытых контроллеров
//	HANDLE _hConvector = NULL; // Конвертер
//	_ZG_CVT_OPEN_PARAMS temp_Params; // Параметры открытия конвертора
//	_ZG_CVT_NOTIFY_SETTINGS commonConverterSettings; // Общие настройки уведомлений от конвертора
//	_ZG_CTR_NOTIFY_SETTINGS commonControllerSettings; // Общие найстройки уведомлений от контоллеров
//
//	/////////////// Временная информация о текущем контроллере
//	int temp_writeIndex = 0, temp_readIndex = 0, currentControllerNumber = 0, temp_controllerReadMax = 0;
//	HANDLE temp_hController = NULL;
//	_ZG_CTR_INFO temp_controllersDetailInfo;
//	std::pair<int, int> temp_controlerIndexWriteRead;
//	std::vector<_ZG_CTR_EVENT> temp_controllerEvents;
//	///////////////
//
//	/////////////// Приватные сценарии // TODO обработка исключений для итераций вызовов и вызов новых исключений
//	bool tryOpenConverter(); // Попытка открытия конвертора DONE / итерация обработана
//	void tryCloseConverter(); // Попытка закрытия конвертора DONE
//	void scanControllers(); // Сканирование контроллеров DONE / итерация (возможно)
//	void openControllers(); // Подключение контроллерров DONE / итерация
//	void openController(_ZG_FIND_CTR_INFO&); // Подключение контроллера 1
//	void deactivateController(_ZG_FIND_CTR_INFO&); // отключение контроллера
//	void closeControllers(); // Закртыие контрллеров DONE
//	void updateConverterInfo(bool); // Обновление информации о конверторе DONE
//	void updateControllerInfo(Action, int = 0); // Обновление информации о контроллере DONE
//	void trySetNotifications(_Out_ std::vector<HANDLE>&); // Установка уведомлений / итерация DONE
//	void tryCloseNotifications(); // Закрыть все уведомления DONE
//	void readConverterNotify(_Out_ std::vector<std::pair<UINT, LPARAM>>&); // Считать уведомление контроллера
//	void readControllerNotify(const int, _Out_ std::vector<std::pair<UINT, LPARAM>>&); // Считать уведомление конвертора
//	void setControllerCurrentTime(const int); // Установка времени
//	///////////////
//
//	/////////////// Низкоуровневые функции-команды
//	void cvt_SetNotification(_ZG_CVT_NOTIFY_SETTINGS = {}); // Установка уведомления для конвертора DONE
//	void ctr_SetNotification(_ZG_CTR_NOTIFY_SETTINGS = {}); // Установка уведомления для контроллера DONE
//	HRESULT cvt_GetNextMessage(); // TODO cvt_GetNextMessage DONE	
//	HRESULT ctr_GetNextMessage(); // TODO ctr_GetNextMessage DONE
//	void ReadControllerEvents(const int, _Out_ std::vector<_ZG_CTR_EVENT>&); // Чтение событий, DONE
//	/////////////// Низкоуровневые функции-команды
//
//	/////////////// Низкоуровневые функции
//	void openConverter(); // DONE
//	void closeConverter(); // DONE
//	ZP_CONNECTION_STATUS getStatus(); // DONE
//	void openController(const int); // DONE
//	void readControllerIdxs(); // DONE
//	int readEvents(int&, const int, const int = 0); // Читай до 5 событий за рас
//	void updateControllerReadIndex(const int); // DONE
//	void setTime(_ZG_CTR_CLOCK&);
//	void closeController(const int);  // DONE
//	///////////////
//
//};
//
