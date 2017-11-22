#include "stdafx.h"
#include "Connection.h"


Connection::Connection(const _ZG_ENUM_IPCVT_INFO convertorInfo, const std::vector<_ZP_PORT_INFO> convertorPorts, const ZP_PORT_TYPE portType) :
	_convertorInfo(convertorInfo),
	_convertorPorts(convertorPorts),
	_portType(portType){}

//Connection::Connection(MainInfo* const mainInfo) :
//	_convertorInfo(mainInfo->converterInfo),
//	_convertorPorts(mainInfo->converterPorts),
//	_portType(mainInfo->portType),
//	_mainInfo(mainInfo){} 

Connection::~Connection()
{// TODO log trace
	if (_hConvector != nullptr)
		ZG_CloseHandle(*_hConvector);

	if (_hController != nullptr)
		ZG_CloseHandle(*_hController);

	delete this->_hConvector, this->_hController;
	_hConvector, _hController = nullptr;
}

bool Connection::openConnection() {
	for (unsigned int i = 0; i < _convertorPorts.size(); i++) {
		// TODO log trace
		_hConvector = new HANDLE;
		_ZG_CVT_OPEN_PARAMS openConvectorParams;
		ZeroMemory(&openConvectorParams, sizeof(openConvectorParams));

		openConvectorParams.pszName = _convertorPorts[i].szName;
		openConvectorParams.nType = _portType;
		
		if (!CheckZGError(ZG_Cvt_Open(_hConvector, &openConvectorParams, NULL), _T("ZG_Cvt_Open")))
			throw OpenFailed(std::string("Connection converter port: " + *(WCHAR*)this->_convertorPorts[i].szName), std::string("Convector"));
		else {
			isOpenConvertor = true;
			return true;
		}
	}
	return false;
}

void Connection::scanControllers() {

	//TODO log trace
	INT MaxCount = 0;
	HRESULT hrController;
	_ZG_FIND_CTR_INFO mControllerInfo;
	_controllersInfo.clear();

	if (!CheckZGError(ZG_Cvt_SearchControllers(*_hConvector, MaxCount, NULL), _T("ZG_Cvt_SearchControllers")))
		throw InitializationSearchError(std::string("test message"));

	while ((hrController = ZG_Cvt_FindNextController(*_hConvector, &(_ZG_FIND_CTR_INFO&)mControllerInfo)) == S_OK) {
		// TODO log trace
		_controllersInfo.push_back(mControllerInfo);
	}

	if (hrController != ZP_S_NOTFOUND)
		throw SearchError(std::string("Error while search controllers"));
}

bool Connection::openController(const int controllerAddress) {
	// TODO log trace
	_hController = new HANDLE;
	_ZG_CTR_INFO rCtrInfo;
	ZeroMemory(&rCtrInfo, sizeof(rCtrInfo));

	if (!CheckZGError(ZG_Ctr_Open(_hController, _hConvector, controllerAddress, 0, &rCtrInfo, ZG_CTR_UNDEF), _T("ZG_Ctr_Open")))
		throw OpenFailed(std::string("Connection controller address: " + controllerAddress), std::string("Controller"));

	isOpenController = true;
	_addrOfOpenController = controllerAddress;
	return true;
}

void Connection::closeController() {
	ZG_CloseHandle(*_hController);
	isOpenController = false;
	_addrOfOpenController = 0;
	// TODO log trace
}

HANDLE* const Connection::get_hConvertor() {
	if (_hConvector == nullptr)
		throw std::runtime_error("Null pointer: maybe you forgot to open connection!");
	return _hConvector;
} 

HANDLE* const Connection::get_hController() {
	if (_hController == nullptr)
		throw std::runtime_error("Null pointer: maybe you forgot to open connection!");
	return _hController;
}

std::vector<_ZG_FIND_CTR_INFO>* const Connection::get_controllersInfo() {
	if (_controllersInfo.empty())
		throw std::runtime_error("Info vector is empty, scanControllers!");
	return &_controllersInfo;
}

#ifdef _DEBUG
bool Connection::TestConnection() {

	HANDLE *_hSearch = new HANDLE;
	HRESULT hrSearch;
	INT_PTR nPortCount;
	_ZP_PORT_INFO converterPorts[2];
	Connection* tempConnection;
	_ZG_ENUM_IPCVT_INFO converterInfo;
	ZP_PORT_TYPE portType = ZP_PORT_IP;
	_ZG_CVT_OPEN_PARAMS _searchParams;
	ZeroMemory(&_searchParams, sizeof(_searchParams));
	ZeroMemory(&converterInfo, sizeof(converterInfo));

	if (!CheckZGError(ZG_SearchDevices(_hSearch, &((_ZP_SEARCH_PARAMS &)_searchParams), FALSE, TRUE), _T("ZG_SearchDevices")))
		throw SearchError(std::string("Error in search")); // TODO log trace

	while ((hrSearch = ZG_FindNextDevice(*_hSearch, &(converterInfo), converterPorts, _countof(converterPorts), &nPortCount)) == S_OK) {
		tempConnection =
			new Connection(
				converterInfo,
				*(new std::vector<_ZP_PORT_INFO>(std::begin(converterPorts), std::end(converterPorts))),
				portType);
		try {
			tempConnection->openConnection();
			tempConnection->scanControllers();
			tempConnection->get_controllersInfo();
		}
		catch (std::exception error) {
			// TODO log trace and to log base
			std::cout << error.what() << "\n";
			//throw SearchError(std::string(error.what()));
		}
		_tprintf(TEXT("1 convertor found\n"));
	}
	ZG_CloseHandle(*_hSearch);
	delete tempConnection;
	return true;
}
#endif