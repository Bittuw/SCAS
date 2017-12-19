#pragma once

struct AvailableConnection;
enum ErrorCode;

enum Action {
	ADD = 1,
	CLOSE = 2,
	CLEAR = 3
};

class Connection // TODO �������� ���� ������� ����������
{
public:
	Connection(std::unique_ptr<AvailableConnection>);
	~Connection();

	/////////////// ��������
	void setNewConnactionInfo(std::unique_ptr<AvailableConnection>);
	//int addController(_ZG_FIND_CTR_INFO); // TODO ������� �������
	//void removeController(const int);
	ErrorCode initialConnections() noexcept; // ������� ���������� � ��������/�������� ������������ DONE
	ErrorCode closeConnections() noexcept; // ������� ��� ����������� DONE
	ErrorCode reconnect() noexcept; // 
	ErrorCode getConnectionStatus(_Out_ bool&) noexcept; // ������ ����������� ���������� DONE
	//ErrorCode addController(_ZG_FIND_CTR_INFO); // �������� ����������
	//ErrorCode removeController(); // ������� ���������� (���������)
	//ErrorCode reconnect();
	//AvailableConnection storeData();
	//AvailableConnection restoreData();
	///////////////

	/////////////// ������������� ������� ���������� SDK Guard
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
	std::unique_ptr<AvailableConnection> _data; // ��������� ��������� �������� ����������
	std::shared_ptr<HANDLE> _e_newInfo = nullptr; // ������� ���������� ������ **��������
	std::shared_ptr<HANDLE> _e_destroyed = nullptr; // ������� ����������� ������� **��������
	///////////////

	ErrorCode errorStatus;

private:
	
	std::vector<HANDLE> _hControllersList;
	HANDLE _hConvector = NULL;
	_ZG_CVT_OPEN_PARAMS temp_Params;

	/////////////// ��������� ���������� � ������� �����������
	int temp_writeIndex = 0, temp_readIndex = 0;
	HANDLE temp_hController = NULL;
	_ZG_CTR_INFO temp_controllersDetailInfo;
	std::pair<int, int> temp_controlersIndexWriteRead;
	///////////////

	/////////////// ��������� ��������
	bool tryOpenConverter(); // ������� �������� ���������� DONE
	void tryCloseConverter(); // ������� �������� ���������� DONE
	void scanControllers(); // ������������ ������������ DONE
	void openControllers(); // ����������� ������������� DONE
	void closeControllers(); // �������� ����������� DONE
	void updateConverterInfo(bool); // ���������� ���������� � ���������� DONE
	void updateControllerInfo(Action, int = 0); // ���������� ���������� � ����������� DONE
	///////////////

	/////////////// �������������� ������� �������
	HRESULT cvt_GetNextMessage(); // TODO cvt_GetNextMessage
	HRESULT ctr_GetNextMessage(const int); // TODO ctr_GetNextMessage
	/////////////// 

	/////////////// �������������� ������� �����������
	void openConverter(); // DONE
	void closeConverter(); // DONE
	ZP_CONNECTION_STATUS getStatus(); // DONE
	void openController(const int); // DONE
	void readControllerIdxs(const int); // DONE
	void closeController(const int);  // DONE
	///////////////
};

