#include "stdafx.h"
#include "SearchDevice.h"
#include "Connection.h"
#include "DataStructs.h"

SearchDevice::SearchDevice(_ZG_CVT_OPEN_PARAMS searchParams) :
	_searchParams(searchParams) 
{
	ZeroMemory(&_searchParams, sizeof(_searchParams));
	_connectionData = std::unique_ptr<AvailableConnection>(new AvailableConnection);
}


SearchDevice::~SearchDevice(){}


void SearchDevice::scanNetwork() {

	_hSearch = std::make_unique<HANDLE>(new HANDLE);
	_localConverterList.clear();
	HRESULT hrSearch;
	INT_PTR nPortCount;
	
	if (!CheckZGError(ZG_SearchDevices(&*_hSearch, &((_ZP_SEARCH_PARAMS &)_searchParams), FALSE, TRUE), _T("ZG_SearchDevices")))
		throw SearchError(std::string("Error in search")); // TODO log trace

	while ((hrSearch = ZG_FindNextDevice(*_hSearch, &*(_connectionData->converterInfo), _connectionData->converterPorts->data(), _connectionData->converterPorts->size(), &nPortCount)) == S_OK) {
		//_connectionData->portType = ZP_PORT_IP;
		//_currentConnection = std::unique_ptr<Connection>(new Connection(std::move(_connectionData)));
		//try {
		//	_currentConnection->initialConnections();
		//	_localConverterList.push_back(std::move(_currentConnection));
		//}
		//catch (const ConnectionError& error) {
		//	// TODO log trace and to log base
		//	std::cout << error.what();
		//	throw SearchError(std::string("Error in search"));
		//}
		////_localAvaliableConnectionsSet.insert(std::move(_connectionData));
		//_connectionData = std::unique_ptr<AvailableConnection>(new AvailableConnection);
	}

	auto list = _localConverterList;
	auto pointer = std::make_unique<std::vector<std::shared_ptr<Connection>>>(list);
	_converterInfoListTest->setNewList(std::move(pointer));
}


#ifdef _DEBUG 
bool SearchDevice::StaticTest() {
	/*(new SearchDevice(*(new _ZG_CVT_OPEN_PARAMS)))->scanNetwork();
	_converterInfoListTest->clear();*/
	return true;
}
#endif
