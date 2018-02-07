#pragma once
class Connection;

class SpecialList { 
public:
	SpecialList(); // TODO ������� ������ _e_pushing � _e_poping
	~SpecialList();

	/////////////// ����� �������
	std::shared_ptr<std::mutex> getMutex();
	std::vector<std::shared_ptr<Connection>> getCopyList();
	void setNewList(std::unique_ptr<std::vector<std::shared_ptr<Connection>>>);
	//auto findConnectedConverters();
	/////////////// 

	/////////////// ������������� �������
	//void push(std::shared_ptr<Connection>); // ��������
	//std::shared_ptr<Connection> pop(); // ������� (� ���������)
	void push_back(std::shared_ptr<Connection>);
	auto erase(const int);
	std::shared_ptr<Connection> at(const int);
	int size();
	void clear();
	/////////////// 

#ifdef _DEBUG
	static void StaticTest() { // TODO ����� ����
		
	}; 
#endif // _DEBUG
	
	std::shared_ptr<HANDLE> _e_pushing; // ������� ���������� ����������
	std::shared_ptr<HANDLE> _e_poping; // TODO ������������ � erase
	std::shared_ptr<HANDLE> _e_clearing; // ������� ������ ������
	std::shared_ptr<HANDLE> _e_newlist; // ������� ���������� �����
	std::shared_ptr<HANDLE> _e_at; // ������� ��������� � �������� �����

	unsigned untreatedConnections = 0;

private:
	std::unique_ptr<std::vector<std::shared_ptr<Connection>>> _wrappedList; // ������������� ������
	std::shared_ptr<std::mutex> _m_access; // ������� ������� � ������
	//auto findByOnline();
};
