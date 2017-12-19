#pragma once

class NotifiedThread
{
public:
	NotifiedThread() {};
	~NotifiedThread();
	///////////////
	void startListining();
	bool createNotifies();
	void createNotify(PZG_FIND_CTR_INFO);
	//void closeNotifies();
	///////////////

	static void runListening(std::shared_ptr<Connection>, std::shared_ptr<HANDLE>);

private:
	NotifiedThread(std::shared_ptr<Connection>, std::shared_ptr<HANDLE>);

	std::vector<HANDLE> _waitingConstArray;
	std::vector<HANDLE> _waitingVariableArray;
	std::unique_ptr<std::vector<HANDLE>> _waitingArray;

	std::weak_ptr<Connection> _localConnection; // Weak_ptr �� Connection
	std::weak_ptr<HANDLE> _hConverter; // HANDLE ����������
	std::weak_ptr<std::vector<HANDLE>> _hConctrollers; // ������� HANDLE ������������

	std::shared_ptr<HANDLE> _e_localExitThread; // ��������� ����� ������
	std::shared_ptr<HANDLE> _e_newInfo; // ������� ���������� ������
	std::shared_ptr<HANDLE> _e_destroyed; // ������� �����������

	//std::unique_ptr<HANDLE> _e_getConverterNotify; // ��������� ����� ������� ����������
	std::vector<HANDLE> _e_NotifiesList; // ������ ������� �������������

	void readConvertorNotify();
	void readControllerNotify();

	void parceConverterNotify();
	void parceControllerNotify();

	///////////////
	void clearNotifyList();
	void getNewPointers(std::shared_ptr<Connection>&);
	void refreshWaitingArray();
	///////////////
};

