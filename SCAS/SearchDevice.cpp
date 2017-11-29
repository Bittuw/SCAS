#include "stdafx.h"
#include "SearchDevice.h"

SearchDevice::SearchDevice(std::unique_ptr<_ZP_SEARCH_PARAMS> searchParams) :
	_searchParams(std::move(searchParams)) {
	ZeroMemory(&*_searchParams, sizeof(*_searchParams));
}


SearchDevice::~SearchDevice(){}


void SearchDevice::scanNetwork() { 

	_hSearch = std::unique_ptr<HANDLE> (new HANDLE);
	HRESULT hrSearch;
	INT_PTR nPortCount;
	auto isEmpty = _convertorsInfoList->empty();

	if (!CheckZGError(ZG_SearchDevices(&*_hSearch, &((_ZP_SEARCH_PARAMS &)this->_searchParams), FALSE, TRUE), _T("ZG_SearchDevices"))) 
		throw SearchError(std::string("Error in search")); // TODO log trace

	while ((hrSearch = ZG_FindNextDevice(*_hSearch, &*(_connectionData->converterInfo), _connectionData->converterPorts, _countof(_connectionData->converterPorts), &nPortCount)) == S_OK) {
		_currentConnection = std::unique_ptr<Connection>(new Connection(std::move(_connectionData)));
		try {
			_currentConnection->openConnection();
			_currentConnection->scanControllers();
			//_currentConnection->get_controllersInfo();
			_localConverterList->push_back(std::move(_currentConnection));
		}
		catch (ConnectionError error) {
			// TODO log trace and to log base
			std::cout << error.what();
			throw SearchError(std::string("Error in search"));
		}
	}
}


#ifdef _DEBUG 
bool SearchDevice::StaticTest() {
	return true;
}
#endif


void SearchDevice::addInfoList(std::unique_ptr<std::vector<AvailableConnection>>* convertorsInfoList) {
	//*(_convertorsInfoList) = std::move(**convertorsInfoList);
}