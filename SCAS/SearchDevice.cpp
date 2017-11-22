#include "stdafx.h"
#include "SearchDevice.h"

SearchDevice::SearchDevice(_ZP_SEARCH_PARAMS* const searchParams) :
	_searchParams(searchParams){}


SearchDevice::~SearchDevice(){}

void SearchDevice::scanNetwork() { // TODO Возможна замена на ZG_SetNotification и ZG_GetNextMessage

	_hSearch = new HANDLE;
	HRESULT hrSearch;
	INT_PTR nPortCount;
	_ZP_PORT_INFO converterPort[2];
	Connection* tempConnection;

	_ZG_CVT_OPEN_PARAMS _searchParams;
	ZeroMemory(&_searchParams, sizeof(_searchParams));

	if (!CheckZGError(ZG_SearchDevices(_hSearch, &((_ZP_SEARCH_PARAMS &)this->_searchParams), FALSE, TRUE), _T("ZG_SearchDevices"))) 
		throw SearchError(std::string("Error in search")); // TODO log trace

	while ((hrSearch = ZG_FindNextDevice(_hSearch, &(_MainInfo->converterInfo), _MainInfo->converterPorts, _countof(_MainInfo->converterPorts), &nPortCount)) == S_OK) {
		tempConnection =
			new Connection(
				_MainInfo->converterInfo,
				*(new std::vector<_ZP_PORT_INFO>(std::begin(_MainInfo->converterPorts), std::end(_MainInfo->converterPorts))),
				_MainInfo->portType);
		try {
			tempConnection->openConnection();
			tempConnection->scanControllers();
			tempConnection->get_controllersInfo();
		}
		catch (ConnectionError error) {
			// TODO log trace and to log base
			std::cout << error.what();
			throw SearchError(std::string("Error in search"));
		}
	}

}