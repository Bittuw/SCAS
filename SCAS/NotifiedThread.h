#pragma once

#ifndef NOTIFIED_THREAD 
#define NOTIFIED_THREAD

//
//class NotifiedThread
//{
//public:
//	~NotifiedThread();
//	///////////////
//	void startListining();
//	///////////////
//
//	static void runListening(std::shared_ptr<Connection>);
//
//private:
//	NotifiedThread(std::shared_ptr<Connection>);
//
//	std::vector<HANDLE> _waitingConstArray;
//	std::vector<HANDLE> _waitingVariableArray;
//	std::unique_ptr<std::vector<HANDLE>> _waitingArray;
//
//	std::weak_ptr<Connection> _localConnection; // Weak_ptr на Connection
//	std::shared_ptr<Connection> temp_localConnection;
//
//	std::shared_ptr<HANDLE> _e_localExitThread; // Локальный евент выхода
//	std::shared_ptr<HANDLE> _e_newInfo; // Событие перезаписи данных
//	std::shared_ptr<HANDLE> _e_destroyed; // Событие уничтожения
//
//	//std::unique_ptr<HANDLE> _e_getConverterNotify; // Локальный евент события конвертора
//	std::vector<HANDLE> _e_NotifiesList; // Массив евентов контроллерова
//	std::vector<std::pair<UINT, LPARAM>> _converterMessagesList;
//	std::vector<std::pair<UINT, LPARAM>> _controllerMessagesList;
//	std::vector<_ZG_CTR_EVENT> _controllerEventList;
//	
//	/////////////// Приватные сценарии
//	bool createNotifies();
//	void switchDevice(const int);
//	///////////////
//
//	//void parceConverterNotify();
//	void parseConverterNotify();
//	void parseControllerNotify(const int&);
//	void parseCotrollerEvents(const int&);
//	/////////////// Утилиты
//	void refreshWaitingArray();
//	///////////////
//};

#endif
