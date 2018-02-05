// Search_Device.cpp: определяет экспортированные функции для приложения DLL.
//


#include "stdafx.h"
#include "Search_Device.h"
#include "Logger.h"
#include "ZPort.h"
#include "Exceptions.h"

std::unique_ptr<Basic_Search_Device> Basic_Search_Device::create_searcher_object(const Seach_Device::Seach_Type& search_Type, _ZP_SEARCH_PARAMS search_params) {
	switch (search_Type)
	{
	case Seach_Device::Seach_Type::Search_Client_Device:
		return std::make_unique<Search_Client_Device>(search_params, ZP_PORT_IPS);
	case Seach_Device::Seach_Type::Search_Server_Device:
		return std::make_unique<Search_Server_Device>(search_params, ZP_PORT_IP);
	default:
		throw std::logic_error("!!!");
	}
}

Seach_Device::Zguard_Basic_Info_List_Ref Basic_Search_Device::execute() {
	Seach_Device::Zguard_Basic_Info_List_uRef zguard_info_list_ref = std::make_unique<Seach_Device::Zguard_Basic_Info_List>();
	search_converters(zguard_info_list_ref);
	search_controllers(zguard_info_list_ref);
	return std::move(zguard_info_list_ref);
}

void Search_Server_Device::search_converters(Seach_Device::Zguard_Basic_Info_List_uRef& zguard_basic_info_list_ref) {
	HANDLE handle_search;
	HRESULT result_search;

	if (ZG_SearchDevices(&handle_search, &(static_cast<_ZP_SEARCH_PARAMS &>(_search_params)))) {
		Log(MessageTypes::ERR) << "Error in search method with server type of converter!";
		throw SearchError(std::string("Error in search"));
	}

	INT_PTR ports_count = 2;
	Seach_Device::Zguard_Converter_Data_Type converter_info;
	Seach_Device::Zguard_Converter_Ports_Data_List converter_ports;

	while ((result_search = ZG_FindNextDevice(&handle_search, &converter_info, converter_ports.data(), converter_ports.size(), &ports_count)) == S_OK) {
		zguard_basic_info_list_ref->emplace_back(converter_info, converter_ports);
	}

	if (result_search != ZP_S_NOTFOUND) {
		Log(MessageTypes::ERR) << LoggerFormat::format("Search ended with error: %, see ZGuard errors table!", result_search);
		throw std::runtime_error("Error!");
	}

	ZG_CloseHandle(&handle_search);
}

void Search_Server_Device::search_controllers(Seach_Device::Zguard_Basic_Info_List_uRef& zguard_basic_info_list_ref) {
	for (Seach_Device::Zguard_Basic_Info& converter_data : *zguard_basic_info_list_ref) {

		Seach_Device::Zguard_Open_Params open_params;
		_ZG_CVT_INFO converter_detail_info;
		HANDLE handle_converter;

		if (!open_converter(converter_data, handle_converter, converter_detail_info, open_params)) {
			Log(MessageTypes::WARNING) << LoggerFormat::format("Converter with nSn % is not available!", std::to_string(converter_data._zguard_conveter_data.nSn));
			converter_data._zguard_converter_available = false;
			continue;
		}

		INT MaxCount = 0;
		HRESULT result_controller;
		Seach_Device::Zguard_Controller_Data_Type controller_data;

		if (ZG_Cvt_SearchControllers(handle_converter, NULL, NULL) != S_OK) {
			Log(MessageTypes::ERR) << LoggerFormat::format("Error while search controllers in converter with nSn %", std::to_string(converter_data._zguard_conveter_data.nSn));
			throw SearchError(std::string("Error while search controllers"));
		}

		while ((result_controller = ZG_Cvt_FindNextController(handle_converter, &static_cast<_ZG_FIND_CTR_INFO&>(controller_data)) == S_OK)) {
			converter_data._zguard_controllers_data_list.push_back(controller_data);
		}

		if (result_controller != ZP_S_NOTFOUND) {
			Log(MessageTypes::ERR) << LoggerFormat::format("Error while search controllers in converter with nSn %, error code: %", std::to_string(converter_data._zguard_conveter_data.nSn), std::to_string(result_controller));
			throw SearchError(std::string("Error while search controllers"));
		}
	}
}

bool Search_Server_Device::open_converter(Seach_Device::Zguard_Basic_Info &converter_info, HANDLE& handle_converter, _ZG_CVT_INFO& converter_detail_info, Seach_Device::Zguard_Open_Params& open_params) {
	ZeroMemory(&open_params, sizeof(open_params));
	open_params.nType = _port_type;
	for (size_t i = 0; i < converter_info._zguard_converter_ports_data.size(); i++) {
		open_params.pszName = converter_info._zguard_converter_ports_data.at(i).szName;
		try {
			if (ZG_Cvt_Open(&handle_converter, &open_params, &converter_detail_info) != S_OK) {
				Log(MessageTypes::WARNING) << LoggerFormat::format("Error while open converter: %", std::to_string(converter_info._zguard_conveter_data.nSn));
				throw OpenFailed(std::string("ZG_Cvt_Open"), std::string("Converter: " + std::to_string(converter_info._zguard_conveter_data.nSn)));
			}
			return true;
		}
		catch (const std::exception& error) {
			if (typeid(error) == typeid(OpenFailed) && i < converter_info._zguard_converter_ports_data.size() - 1)
				continue;
			else {
				Log(MessageTypes::ERR) << error.what();
			}
		}
	}
	return false;
}