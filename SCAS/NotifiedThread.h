#pragma once
class NotifiedThread
{
public:
	NotifiedThread(std::shared_ptr<Connection>, std::shared_ptr<HANDLE>);
	~NotifiedThread();

	void startListining();
	bool createNotify();

private:
	std::vector<HANDLE> _waitingFirstArray;
	std::vector<HANDLE> _waitingSecondArray;

	std::weak_ptr<Connection> _localConnection; // Weak_ptr �� Connection
	std::weak_ptr<HANDLE> _hConverter; // HANDLE ����������
	std::weak_ptr<std::vector<std::unique_ptr<HANDLE>>> _hConctrollers; // ������� HANDLE ������������

	std::shared_ptr<HANDLE> _e_localExitThread; // ��������� ����� ������
	std::shared_ptr<HANDLE> _e_newInfo; // ������� ���������� ������
	std::shared_ptr<HANDLE> _e_destroyed; // ������� �����������

	std::unique_ptr<HANDLE> _e_getConverterNotify; // ��������� ����� ������� ����������
	std::vector<HANDLE> _e_getControllersNotifyList; // ������ ������� �������������

	void switchFirstEvent(DWORD&);
	void switchSecondEvent(DWORD&);
	void readNotify();

	void waitFirstEvent();
	void waitSecondEvent();
};

