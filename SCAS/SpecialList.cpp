#include "stdafx.h"
#include "Connection.h"
#include "DataStructs.h"
#include "SpecialList.h"

SpecialList::SpecialList() :
	_wrappedList(std::make_unique<std::vector<std::shared_ptr<Connection>>>()),
	_m_access(new std::mutex),
	_e_pushing(std::make_shared<HANDLE>(CreateEvent(NULL, TRUE, FALSE, NULL))),
	_e_poping(std::make_shared<HANDLE>(CreateEvent(NULL, TRUE, FALSE, NULL))),
	_e_newlist(std::make_shared<HANDLE>(CreateEvent(NULL, TRUE, FALSE, NULL))),
	_e_clearing(std::make_shared<HANDLE>(CreateEvent(NULL, TRUE, FALSE, NULL))),
	_e_at(std::make_shared<HANDLE>(CreateEvent(NULL, TRUE, FALSE, NULL)))
{};

SpecialList::~SpecialList() {}

std::shared_ptr<std::mutex> SpecialList::getMutex() {
	return _m_access;
}

std::vector<std::shared_ptr<Connection>> SpecialList::getCopyList() {
	auto temp = *_wrappedList;
	return temp;
}

void SpecialList::setNewList(std::unique_ptr<std::vector<std::shared_ptr<Connection>>> wrappedList) {
	_m_access->lock();
	_wrappedList = std::move(wrappedList);
	untreatedConnections = _wrappedList->size();
	_m_access->unlock();
	SetEvent(*_e_newlist);
};

//auto SpecialList::findConnectedConverters() {
//	std::vector<std::shared_ptr<Connection>> resultList;
//	std::vector<std::shared_ptr<Connection>>::iterator result;
//
//	while ((result = findByOnline()) != _wrappedList->end()) {
//		resultList.push_back(*result);
//	}
//
//	return resultList;
//}

void SpecialList::clear() {
	_m_access->lock();
	_wrappedList->clear();
	untreatedConnections = 0;
	_m_access->unlock();
	SetEvent(*_e_clearing);
};

void SpecialList::push_back(std::shared_ptr<Connection> pointer) {
	_m_access->lock();
	_wrappedList->push_back(pointer);
	untreatedConnections++;
	_m_access->unlock();
	SetEvent(*_e_pushing);
};

std::shared_ptr<Connection> SpecialList::at(const int position) {
	_m_access->lock();
	auto temp = _wrappedList->at(position);
	_m_access->unlock();
	SetEvent(*_e_at);
	return temp;
};

int SpecialList::size() {
	_m_access->lock();
	auto temp = _wrappedList->size();
	_m_access->unlock();
	return temp;
}

//auto SpecialList::findByOnline() {
//	auto result = std::find_if(
//		_wrappedList->begin(), _wrappedList->end(), 
//		[](const std::shared_ptr<Connection>& item)->bool { return item->_data->converterStatus; });
//
//	return result;
//}