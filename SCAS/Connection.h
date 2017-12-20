#pragma once

struct AvailableConnection;
enum ErrorCode;

enum Action {
	ADD = 1, // �������� ����������
	CLOSE = 2, // ������� ���������� (+ ������� �����, func->erase)
	CLEAR = 3, // ������� ������� 
	CHANGE = 4, // ��������� ,
	REBASE = 5 // ������������ ��� �������� ����������
};

class Connection // TODO �������� ���� ������� ����������
{
public:
	Connection(std::unique_ptr<AvailableConnection>);
	~Connection();

	/////////////// �������� TODO ���� exception �� ����� ������ ������ � ������ ��������������� ������
	void setNewConnactionInfo(std::unique_ptr<AvailableConnection>);
	//int addController(_ZG_FIND_CTR_INFO); // TODO ������� �������
	//void removeController(const int);
	ErrorCode initialConnections() noexcept; // ������� ���������� � ��������/�������� ������������ DONE
	ErrorCode closeConnections() noexcept; // ������� ��� ����������� DONE
	ErrorCode reconnect() noexcept; // ����������� ���������� DONE
	ErrorCode getConnectionStatus(_Out_ bool&) noexcept; // ������ ����������� ���������� DONE
	ErrorCode setNotifications(_Out_ std::vector<HANDLE>&) noexcept; // ��������� �����������
	ErrorCode closeNotifications(); // ������� ����������� DONE
	ErrorCode readConverterNotifies(_Out_ std::vector<std::pair<UINT, LPARAM>>&) noexcept; // ������ ����������� ���������� DONE
	ErrorCode readControllerNotifies(const int, _Out_ std::vector<std::pair<UINT, LPARAM>>&) noexcept; // ������ ����������� ����������� DONE
	ErrorCode readControllerEvent(const int, _Out_ std::vector<_ZG_CTR_EVENT>&); // ������ ������� �����������
	//ErrorCode addController(_ZG_FIND_CTR_INFO); // �������� ����������
	//ErrorCode removeController(); // ������� ���������� (���������)
	//ErrorCode reconnect();
	//AvailableConnection storeData();
	//AvailableConnection restoreData();
	///////////////

	/////////////// ������������� ������� ���������� SDK Guard

	///////////////

#ifdef _DEBUG 
	static bool StaticTest();
#endif

	/////////////// 
	std::unique_ptr<AvailableConnection> _data; // ��������� ��������� �������� ����������
	std::shared_ptr<HANDLE> _e_newInfo = nullptr; // ������� ���������� ������ **��������
	std::shared_ptr<HANDLE> _e_destroyed = nullptr; // ������� ����������� ������� **��������
	///////////////

	ErrorCode errorStatus;

private:
	
	std::vector<std::pair<UINT, LPARAM>> _converterMessageList; // ����������� ����������� ����������
	std::vector<std::pair<UINT, LPARAM>> _controllerMessageList; // ����������� ����������� �����������
	std::vector<HANDLE> _hControllersList; // ������ �������� ������������
	HANDLE _hConvector = NULL; // ���������
	_ZG_CVT_OPEN_PARAMS temp_Params; // ��������� �������� ����������
	_ZG_CVT_NOTIFY_SETTINGS commonConverterSettings; // ����� ��������� ����������� �� ����������
	_ZG_CTR_NOTIFY_SETTINGS commonControllerSettings; // ����� ���������� ����������� �� �����������

	/////////////// ��������� ���������� � ������� �����������
	int temp_writeIndex = 0, temp_readIndex = 0;
	HANDLE temp_hController = NULL;
	_ZG_CTR_INFO temp_controllersDetailInfo;
	std::pair<int, int> temp_controlerIndexWriteRead;
	std::vector<_ZG_CTR_EVENT> temp_controllerEvents;
	///////////////

	/////////////// ��������� �������� // TODO ��������� ���������� ��� �������� ������� � ����� ����� ����������
	bool tryOpenConverter(); // ������� �������� ���������� DONE / �������� ����������
	void tryCloseConverter(); // ������� �������� ���������� DONE
	void scanControllers(); // ������������ ������������ DONE / �������� (��������)
	void openControllers(); // ����������� ������������� DONE / ��������
	void closeControllers(); // �������� ����������� DONE
	void updateConverterInfo(bool); // ���������� ���������� � ���������� DONE
	void updateControllerInfo(Action, int = 0); // ���������� ���������� � ����������� DONE
	void trySetNotifications(_Out_ std::vector<HANDLE>&); // ��������� ����������� / �������� DONE
	void tryCloseNotifications(); // ������� ��� ����������� DONE
	void readConverterNotify(_Out_ std::vector<std::pair<UINT, LPARAM>>&); // ������� ����������� �����������
	void readControllerNotify(const int, _Out_ std::vector<std::pair<UINT, LPARAM>>&); // ������� ����������� ����������
	///////////////

	/////////////// �������������� �������-�������
	void cvt_SetNotification(_ZG_CVT_NOTIFY_SETTINGS = {}); // ��������� ����������� ��� ���������� DONE
	void ctr_SetNotification(const int, _ZG_CTR_NOTIFY_SETTINGS = {}); // ��������� ����������� ��� ����������� DONE
	HRESULT cvt_GetNextMessage(); // TODO cvt_GetNextMessage
	HRESULT ctr_GetNextMessage(const int); // TODO ctr_GetNextMessage
	void ReadControllerEvents(const int, _Out_ std::vector<_ZG_CTR_EVENT>&); // ������ �������
	/////////////// �������������� �������-�������

	/////////////// �������������� �������
	void openConverter(); // DONE
	void closeConverter(); // DONE
	ZP_CONNECTION_STATUS getStatus(); // DONE
	void openController(const int); // DONE
	void readControllerIdxs(int = -1); // DONE
	int ReadEvents(const int, const int); // ����� �� 5 ������� �� ���
	void closeController(const int);  // DONE
	///////////////

};

