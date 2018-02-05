#include "stdafx.h"
#include "SearchDevice.h"



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

std::unique_ptr<Seach_Device::Basic_Search_Device> Seach_Device::Basic_Search_Device::create_searcher_object(const Seach_Device::Seach_Type& search_Type, _ZP_SEARCH_PARAMS search_params) {
	switch (search_Type)
	{
	case Seach_Type::Search_Client_Device:
		return std::make_unique<Search_Client_Device>(search_params);
	case Seach_Type::Search_Server_Device:
		return std::make_unique<Search_Server_Device>(search_params);
	default:
		throw std::logic_error("!!!");
	}
}

Seach_Device::Zguard_Basic_Info_List_Ref Seach_Device::Basic_Search_Device::execute() {
	Zguard_Basic_Info_List_Ref zguard_info_list_ref = std::make_unique<Zguard_Basic_Info_List>();
	search_converters(zguard_info_list_ref);
	search_controllers(zguard_info_list_ref);
	return std::move(zguard_info_list_ref);
}

void Seach_Device::Search_Server_Device::search_converters(const Zguard_Basic_Info_List_Ref& zguard_basic_info_list_ref) {
	HANDLE handle_search;
	HRESULT result_search;

	if (ZG_SearchDevices(&handle_search, &(static_cast<_ZP_SEARCH_PARAMS &>(_search_params)))) {
		Log(MessageTypes::ERR) << "Error in search method with server type of converter!";
		throw SearchError(std::string("Error in search")); // TODO log trace
	}

	INT_PTR ports_count = 2;
	_ZG_ENUM_IPCVT_INFO converter_info;
	std::vector<_ZP_PORT_INFO> converter_ports;
	while ((result_search = ZG_FindNextDevice(&handle_search, &converter_info, converter_ports.data(), converter_ports.size(), &ports_count)) == S_OK) {
		zguard_basic_info_list_ref->emplace_back(&converter_info, &converter_ports);
	}

	if (result_search != ZP_S_NOTFOUND) {
		Log(MessageTypes::ERR) << LoggerFormat::format("Search ended with error: %, see ZGuard errors table!", result_search);
		throw std::runtime_error("Error!");
	}
}

void Seach_Device::Search_Server_Device::search_controllers(const Zguard_Basic_Info_List_Ref& zguard_basic_info_list_ref) { // TODO сценарий
	for (auto converter_info : *zguard_basic_info_list_ref) {

		Zguard_Open_Params open_params;
		_ZG_CVT_INFO converter_detail_info;
		HANDLE handle_converter;

		ZeroMemory(&open_params, sizeof(open_params));
		open_params.nType = _port_type;
		for (size_t i = 0; i < converter_info._zguard_converter_ports_data.size(); i++) {
			open_params.pszName = converter_info._zguard_converter_ports_data.at(i).szName;
			try {
				if (ZG_Cvt_Open(&handle_converter, &open_params, &converter_detail_info) != S_OK) {
					Log(MessageTypes::ERR) << LoggerFormat::format("Error while open converter: %", std::to_string(converter_info._zguard_conveter_data.nSn));
					throw OpenFailed(std::string("ZG_Cvt_Open"), std::string("Converter: " + std::to_string(converter_info._zguard_conveter_data.nSn)));
				}
			}
			catch (const std::exception& error) {
				if (typeid(error) == typeid(OpenFailed) && i < converter_info._zguard_converter_ports_data.size() - 1)
					continue;
				else {
					Log(MessageTypes::ERR) << error.what();
				}
			}
		}
	}
}