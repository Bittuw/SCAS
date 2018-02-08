#pragma once

#include "DataStructs.h"
#include "Main_Connection_Info.h"
//
//struct Available_Connection;
//
//enum Action {
//	ADD = 0, // �������� ����������
//	CLOSE = 1, // ������� ���������� (+ ������� �����, func->erase)
//	CLEAR = 2, // ������� ������� 
//	CHANGE = 3, // ��������� ,
//	REBASE = 4, // ������������ ��� �������� ����������
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
//class Connection // TODO ���������� ������������ ErrorCode
//{
//public:
//	Connection(std::unique_ptr<Available_Connection>&);
//	~Connection();
//
//	/////////////// �������� TODO ���� exception �� ����� ������ ������ � ������ ��������������� ������
//	void setNewConnactionInfo(std::unique_ptr<Available_Connection>);
//	//int addController(_ZG_FIND_CTR_INFO); // TODO ������� �������
//	//void removeController(const int);
//	Main_Connection_Basic_Info_Types::Connection_Error_Code initialConnections() noexcept; // ������� ���������� � ��������/�������� ������������ DONE
//	Main_Connection_Basic_Info_Types::Connection_Error_Code closeConnections() noexcept; // ������� ��� ����������� DONE
//	Main_Connection_Basic_Info_Types::Connection_Error_Code reconnect() noexcept; // ����������� ���������� DONE
//	Main_Connection_Basic_Info_Types::Connection_Error_Code getConnectionStatus(_Out_ bool&) noexcept; // ������ ����������� ���������� DONE
//	Main_Connection_Basic_Info_Types::Connection_Error_Code setNotifications(_Out_ std::vector<HANDLE>&) noexcept; // ��������� �����������
//	Main_Connection_Basic_Info_Types::Connection_Error_Code closeNotifications(); // ������� ����������� DONE
//	Main_Connection_Basic_Info_Types::Connection_Error_Code readConverterNotifies(_Out_ std::vector<std::pair<UINT, LPARAM>>&) noexcept; // ������ ����������� ���������� DONE
//	Main_Connection_Basic_Info_Types::Connection_Error_Code addController(_ZG_FIND_CTR_INFO);
//	Main_Connection_Basic_Info_Types::Connection_Error_Code removeController(_ZG_FIND_CTR_INFO);
//	//ErrorCode setControllerKeysBase(const int, std::vector<type-error>); // ��������� ���� ������
//	//ErrorCode getControllerKeyBase(const int, _Out_ std::vector<type-error>); // ��������� ���� ������
//	Main_Connection_Basic_Info_Types::Connection_Error_Code readControllerNotifies(const int, _Out_ std::vector<std::pair<UINT, LPARAM>>&) noexcept; // ������ ����������� ����������� DONE
//	Main_Connection_Basic_Info_Types::Connection_Error_Code readControllerEvent(const int, _Out_ std::vector<_ZG_CTR_EVENT>&); // ������ ������� �����������
//	//ErrorCode readControllerEvents(const int, _Out_ std::vector<_ZG_EVENT>&) // ������ ���� �������
//	Main_Connection_Basic_Info_Types::Connection_Error_Code setControllerTime(const int); // ��������� ������� ����������� DONE
//	//AvailableConnection storeData();
//	//AvailableConnection restoreData();
//	///////////////
//
//	/////////////// �������
//	const HANDLE& getControllerHandle(const int);
//	///////////////
//
//#ifdef _DEBUG 
//	static bool StaticTest();
//#endif
//
//	/////////////// 
//	std::unique_ptr<Available_Connection> _data; // ��������� ��������� �������� ����������
//	std::shared_ptr<HANDLE> _e_newInfo = nullptr; // ������� ���������� ������ **��������
//	std::shared_ptr<HANDLE> _e_destroyed = nullptr; // ������� ����������� ������� **��������
//	///////////////
//
//	Main_Connection_Basic_Info_Types::Connection_Error_Code errorStatus;
//
//private:
//	
//	std::vector<std::pair<UINT, LPARAM>> _converterMessageList; // ����������� ����������� ����������
//	std::vector<std::pair<UINT, LPARAM>> _controllerMessageList; // ����������� ����������� �����������
//	std::vector<HANDLE> _hControllersList; // ������ �������� ������������
//	HANDLE _hConvector = NULL; // ���������
//	_ZG_CVT_OPEN_PARAMS temp_Params; // ��������� �������� ����������
//	_ZG_CVT_NOTIFY_SETTINGS commonConverterSettings; // ����� ��������� ����������� �� ����������
//	_ZG_CTR_NOTIFY_SETTINGS commonControllerSettings; // ����� ���������� ����������� �� �����������
//
//	/////////////// ��������� ���������� � ������� �����������
//	int temp_writeIndex = 0, temp_readIndex = 0, currentControllerNumber = 0, temp_controllerReadMax = 0;
//	HANDLE temp_hController = NULL;
//	_ZG_CTR_INFO temp_controllersDetailInfo;
//	std::pair<int, int> temp_controlerIndexWriteRead;
//	std::vector<_ZG_CTR_EVENT> temp_controllerEvents;
//	///////////////
//
//	/////////////// ��������� �������� // TODO ��������� ���������� ��� �������� ������� � ����� ����� ����������
//	bool tryOpenConverter(); // ������� �������� ���������� DONE / �������� ����������
//	void tryCloseConverter(); // ������� �������� ���������� DONE
//	void scanControllers(); // ������������ ������������ DONE / �������� (��������)
//	void openControllers(); // ����������� ������������� DONE / ��������
//	void openController(_ZG_FIND_CTR_INFO&); // ����������� ����������� 1
//	void deactivateController(_ZG_FIND_CTR_INFO&); // ���������� �����������
//	void closeControllers(); // �������� ����������� DONE
//	void updateConverterInfo(bool); // ���������� ���������� � ���������� DONE
//	void updateControllerInfo(Action, int = 0); // ���������� ���������� � ����������� DONE
//	void trySetNotifications(_Out_ std::vector<HANDLE>&); // ��������� ����������� / �������� DONE
//	void tryCloseNotifications(); // ������� ��� ����������� DONE
//	void readConverterNotify(_Out_ std::vector<std::pair<UINT, LPARAM>>&); // ������� ����������� �����������
//	void readControllerNotify(const int, _Out_ std::vector<std::pair<UINT, LPARAM>>&); // ������� ����������� ����������
//	void setControllerCurrentTime(const int); // ��������� �������
//	///////////////
//
//	/////////////// �������������� �������-�������
//	void cvt_SetNotification(_ZG_CVT_NOTIFY_SETTINGS = {}); // ��������� ����������� ��� ���������� DONE
//	void ctr_SetNotification(_ZG_CTR_NOTIFY_SETTINGS = {}); // ��������� ����������� ��� ����������� DONE
//	HRESULT cvt_GetNextMessage(); // TODO cvt_GetNextMessage DONE	
//	HRESULT ctr_GetNextMessage(); // TODO ctr_GetNextMessage DONE
//	void ReadControllerEvents(const int, _Out_ std::vector<_ZG_CTR_EVENT>&); // ������ �������, DONE
//	/////////////// �������������� �������-�������
//
//	/////////////// �������������� �������
//	void openConverter(); // DONE
//	void closeConverter(); // DONE
//	ZP_CONNECTION_STATUS getStatus(); // DONE
//	void openController(const int); // DONE
//	void readControllerIdxs(); // DONE
//	int readEvents(int&, const int, const int = 0); // ����� �� 5 ������� �� ���
//	void updateControllerReadIndex(const int); // DONE
//	void setTime(_ZG_CTR_CLOCK&);
//	void closeController(const int);  // DONE
//	///////////////
//
//};
//
