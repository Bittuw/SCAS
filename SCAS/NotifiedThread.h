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
//	std::weak_ptr<Connection> _localConnection; // Weak_ptr �� Connection
//	std::shared_ptr<Connection> temp_localConnection;
//
//	std::shared_ptr<HANDLE> _e_localExitThread; // ��������� ����� ������
//	std::shared_ptr<HANDLE> _e_newInfo; // ������� ���������� ������
//	std::shared_ptr<HANDLE> _e_destroyed; // ������� �����������
//
//	//std::unique_ptr<HANDLE> _e_getConverterNotify; // ��������� ����� ������� ����������
//	std::vector<HANDLE> _e_NotifiesList; // ������ ������� �������������
//	std::vector<std::pair<UINT, LPARAM>> _converterMessagesList;
//	std::vector<std::pair<UINT, LPARAM>> _controllerMessagesList;
//	std::vector<_ZG_CTR_EVENT> _controllerEventList;
//	
//	/////////////// ��������� ��������
//	bool createNotifies();
//	void switchDevice(const int);
//	///////////////
//
//	//void parceConverterNotify();
//	void parseConverterNotify();
//	void parseControllerNotify(const int&);
//	void parseCotrollerEvents(const int&);
//	/////////////// �������
//	void refreshWaitingArray();
//	///////////////
//};

#endif
