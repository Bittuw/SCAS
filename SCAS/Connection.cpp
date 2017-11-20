#include "stdafx.h"
#include "Connection.h"


Connection::Connection(const _ZG_ENUM_IPCVT_INFO convertorInfo, const std::vector<_ZP_PORT_INFO> convertorPorts, const ZP_PORT_TYPE portType) :
	_convertorInfo(convertorInfo),
	_convertorPorts(convertorPorts),
	_portType(portType){}

Connection::Connection(MainInfo* const mainInfo) :
	_convertorInfo(mainInfo->converterInfo),
	_convertorPorts(mainInfo->converterPorts),
	_portType(mainInfo->portType),
	_mainInfo(mainInfo){} 

Connection::~Connection()
{// TODO log trace
	if (_hConvector != nullptr || _hController != nullptr) {
		ZG_CloseHandle(*_hController);
		ZG_CloseHandle(*_hConvector);
	}
	delete this->_hConvector, this->_hController;
	_hConvector, _hController = nullptr;
}

bool Connection::openConnection() {
	for (int i = _convertorPorts.size(); i < 2; i++) {
		// TODO log trace
		_hConvector = new HANDLE;
		_ZG_CVT_OPEN_PARAMS openConvectorParams;
		ZeroMemory(&openConvectorParams, sizeof(openConvectorParams));

		openConvectorParams.pszName = _convertorPorts[i].szName;
		openConvectorParams.nType = _portType;
		
		if (!CheckZGError(ZG_Cvt_Open(_hConvector, &openConvectorParams, NULL), _T("ZG_Cvt_Open")))
			throw OpenFailed(std::string("Connection converter port: " + (WCHAR)this->_convertorPorts[i].szName), std::string("Convector")); // TODO возможно ошибкапреобразования из WCHAR to std::string
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

	if (!CheckZGError(ZG_Cvt_SearchControllers(_hConvector, MaxCount, NULL), _T("ZG_Cvt_SearchControllers")))
		throw InitializationSearchError(std::string("test message"));

	while ((hrController = ZG_Cvt_FindNextController(_hConvector, &(_ZG_FIND_CTR_INFO&)mControllerInfo)) == S_OK) {
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

