#include "stdafx.h"
#include "SearchDevice.h"
#include "Connection.h"
#include "DataStructs.h" 
#include "Utils.h"

SearchDevice::SearchDevice(_ZG_CVT_OPEN_PARAMS searchParams) :
	_search_Params(searchParams)

{
	ZeroMemory(&_search_Params, sizeof(_search_Params));
}


SearchDevice::~SearchDevice(){}


//SearchDevice_RetrurnData<AV_list> SearchDevice::scanNetwork() { // TODO and commit
//
//	
//	//HRESULT hrSearch;
//	//INT_PTR nPortCount;
//	//
//	//if (ZG_SearchDevices(&_handle_Search, &((_ZP_SEARCH_PARAMS &)_search_Params)))
//	//	throw SearchError(std::string("Error in search")); // TODO log trace
//
//	//while ((hrSearch = ZG_FindNextDevice(*_hSearch, &*(_connectionData->converterInfo), _connectionData->converterPorts->data(), _connectionData->converterPorts->size(), &nPortCount)) == S_OK) {
//	//	//_connectionData->portType = ZP_PORT_IP;
//	//	//_currentConnection = std::unique_ptr<Connection>(new Connection(std::move(_connectionData)));
//	//	//try {
//	//	//	_currentConnection->initialConnections();
//	//	//	_localConverterList.push_back(std::move(_currentConnection));
//	//	//}
//	//	//catch (const ConnectionError& error) {
//	//	//	// TODO log trace and to log base
//	//	//	std::cout << error.what();
//	//	//	throw SearchError(std::string("Error in search"));
//	//	//}
//	//	////_localAvaliableConnectionsSet.insert(std::move(_connectionData));
//	//	//_connectionData = std::unique_ptr<AvailableConnection>(new AvailableConnection);
//	//}
//
//	//auto list = _localConverterList;
//	//auto pointer = std::make_unique<std::vector<std::shared_ptr<Connection>>>(list);
//	//_converterInfoListTest->setNewList(std::move(pointer));
//}


#ifdef _DEBUG 
bool SearchDevice::StaticTest() {
	/*(new SearchDevice(*(new _ZG_CVT_OPEN_PARAMS)))->scanNetwork();
	_converterInfoListTest->clear();*/
	return true;
}
#endif

void SearchDevice::custome_seach_converter() {

}

void SearchDevice::custome_search_controllers(HANDLE& converter) {

}