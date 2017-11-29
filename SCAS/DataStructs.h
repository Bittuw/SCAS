#pragma once
#include "Connection.h"
class Connection;

template <typename T>
class SpecialList {
public:
	SpecialList() : _wrappedList(new std::unique_ptr<std::list<std::shared_ptr<T>>>) {}; // TODO создать евенты
	~SpecialList() {};
	// TODO создать дублирующие функции
	_wrappedList getCopyList();
	&_wrappedList getPointerToList() { return &_wrappedList };
	void setNewList(std::unique_ptr<std::list<std::shared_ptr<T>>>);
	
	std::shared_ptr<HANDLE> e_pushing;
	std::shared_ptr<HANDLE> e_poping;
	std::shared_ptr<HANDLE> e_clearing;
	std::shared_ptr<HANDLE> e_newlist;
	std::shared_ptr<std::mutex> m_access;

private:
	std::unique_ptr<std::list<std::shared_ptr<T>>> _wrappedList;
};

struct AvailableConnection { // TODO возможная замена для MainInfo
	std::unique_ptr<_ZG_ENUM_IPCVT_INFO> converterInfo = nullptr; // Общая информация  о конверторе
	_ZP_PORT_INFO converterPorts[2]; // Список портов
	std::unique_ptr<std::vector<_ZG_FIND_CTR_INFO>> controllersInfo = nullptr; // Список конверторов
	std::unique_ptr<ZP_PORT_TYPE> portType = nullptr; // Тип подключения
	std::unique_ptr<std::mutex> connectionMutex; // Мьютетс доступа
	bool isJoinable = false;
	//_ZG_CVT_OPEN_PARAMS openConverterParams; // TODO параметры подключения (Возможность задать)

	AvailableConnection() :
		converterInfo(new _ZG_ENUM_IPCVT_INFO),
		controllersInfo(new std::vector<_ZG_FIND_CTR_INFO>),
		portType(new ZP_PORT_TYPE),
		connectionMutex(new std::mutex)
	{
		ZeroMemory(&*converterInfo, sizeof(*converterInfo));
		converterInfo->cbSize = sizeof(_ZG_ENUM_IPCVT_INFO);
	}

	~AvailableConnection() { // TODO delete connection
		converterInfo = nullptr;
		controllersInfo = nullptr;
		portType = nullptr;
	}
};

static const auto _convertorsInfoList = std::unique_ptr<std::list<std::shared_ptr<Connection>>>(new std::list<std::shared_ptr<Connection>>);
static const std::mutex listLocker;

template <typename T>
class BlockingList : public std::list<T> {
public:
	T find(T find) {
		for (std::list<T>::iterator it = this->begin(); it != this->end(); ++it)
			if (*it == find)
				return *it;
		return 0;
	}
};
