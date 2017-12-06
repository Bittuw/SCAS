#pragma once
class Connection;

class SpecialList { 
public:
	SpecialList() :
		_m_access(new std::mutex),
		_e_newlist(std::make_shared<HANDLE>(CreateEvent(NULL, TRUE, FALSE, NULL))),
		_e_clearing(std::make_shared<HANDLE>(CreateEvent(NULL, TRUE, FALSE, NULL))),
		_e_at(std::make_shared<HANDLE>(CreateEvent(NULL, TRUE, FALSE, NULL)))
	{}; // TODO создать евенты _e_pushing и _e_poping

	~SpecialList() {};

	std::shared_ptr<std::mutex> getMutex() { return _m_access; };

	std::vector<std::shared_ptr<Connection>> getCopyList() { 
		auto temp = *_wrappedList;
		return temp; 
	};

	void setNewList(std::unique_ptr<std::vector<std::shared_ptr<Connection>>> wrappedList) {
		_m_access->lock();
		_wrappedList = std::move(wrappedList);
		_m_access->unlock();
		SetEvent(*_e_newlist);
	};

	void clear() {
		_m_access->lock();
		_wrappedList->clear();
		_m_access->unlock();
		SetEvent(*_e_clearing);
	};

	std::shared_ptr<Connection> at(const int position) {
		_m_access->lock();
		auto temp = _wrappedList->at(position);
		_m_access->unlock();
		SetEvent(*_e_at);
		return temp;
	};

	int size() {
		_m_access->lock();
		auto temp = _wrappedList->size();
		_m_access->unlock();
		return temp;
	}

#ifdef _DEBUG
	static void StaticTest() {
		/*SpecialList<Connection> temp;
		temp.setList(std::unique_ptr<std::list<std::shared_ptr<Connection>>>(new std::list<std::shared_ptr<T>>));*/
	}; 
#endif // _DEBUG
	
	std::shared_ptr<HANDLE> _e_pushing;
	std::shared_ptr<HANDLE> _e_poping;
	std::shared_ptr<HANDLE> _e_clearing; // Событие чистки списка
	std::shared_ptr<HANDLE> _e_newlist; // Событие перезаписи листа
	std::shared_ptr<HANDLE> _e_at; // Событие обрашения к элементу листа

private:
	std::unique_ptr<std::vector<std::shared_ptr<Connection>>> _wrappedList; // Оборачиваемый список
	std::shared_ptr<std::mutex> _m_access; // Мьютекс доступа к списку

};

