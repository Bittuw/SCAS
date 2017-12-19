#pragma once
class Connection;

class SpecialList { 
public:
	SpecialList(); // TODO создать евенты _e_pushing и _e_poping
	~SpecialList();

	/////////////// Общие функции
	std::shared_ptr<std::mutex> getMutex();
	std::vector<std::shared_ptr<Connection>> getCopyList();
	void setNewList(std::unique_ptr<std::vector<std::shared_ptr<Connection>>>);
	//auto findConnectedConverters();
	/////////////// 

	/////////////// Оборачиваемые функции
	//void push(std::shared_ptr<Connection>); // Положить
	//std::shared_ptr<Connection> pop(); // Достать (с удалением)
	void push_back(std::shared_ptr<Connection>);
	auto erase(const int);
	std::shared_ptr<Connection> at(const int);
	int size();
	void clear();
	/////////////// 

#ifdef _DEBUG
	static void StaticTest() { // TODO нужен тест
		
	}; 
#endif // _DEBUG
	
	std::shared_ptr<HANDLE> _e_pushing; // Событие добавления соединения
	std::shared_ptr<HANDLE> _e_poping; // TODO переменовать в erase
	std::shared_ptr<HANDLE> _e_clearing; // Событие чистки списка
	std::shared_ptr<HANDLE> _e_newlist; // Событие перезаписи листа
	std::shared_ptr<HANDLE> _e_at; // Событие обрашения к элементу листа

	unsigned untreatedConnections = 0;

private:
	std::unique_ptr<std::vector<std::shared_ptr<Connection>>> _wrappedList; // Оборачиваемый список
	std::shared_ptr<std::mutex> _m_access; // Мьютекс доступа к списку
	//auto findByOnline();
};

