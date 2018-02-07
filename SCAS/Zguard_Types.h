#pragma once

///
/// Represent zguard's data types
///

#ifndef ZGUARD_TYPES
#define ZGUARD_TYPES

#include <memory>
#include <vector>
#include "Zguard.h"

namespace Zguard_Basic_Info_Types {

	using Zguard_Converter_Data_Type = _ZG_ENUM_IPCVT_INFO;
	using Zguard_Converter_Ports_Data_List = std::vector<_ZP_PORT_INFO>;
	using Zguard_Controller_Data_Type = _ZG_FIND_CTR_INFO;
	using Zguard_Open_Params = _ZG_CVT_OPEN_PARAMS;

	using Zguard_Controller_Data_List = std::vector<Zguard_Controller_Data_Type>;
	using Zguard_Converter_Available = bool;
	using Zguard_Controllers_Available_list = std::vector<bool>;

	struct Zguard_Basic_Info {

		Zguard_Converter_Data_Type _zguard_conveter_data;
		Zguard_Converter_Ports_Data_List _zguard_converter_ports_data;
		Zguard_Controller_Data_List _zguard_controllers_data_list;
		Zguard_Converter_Available _zguard_converter_available;
		Zguard_Controllers_Available_list _zguard_controllers_available_list;

		Zguard_Basic_Info() {}
		Zguard_Basic_Info(const Zguard_Converter_Data_Type& zguard_converter_data, const Zguard_Converter_Ports_Data_List& zguard_converter_posrt_data)
			:
			_zguard_conveter_data(zguard_converter_data),
			_zguard_converter_ports_data(zguard_converter_posrt_data)
		{}

		Zguard_Basic_Info(Zguard_Basic_Info&& other)
			:
			_zguard_conveter_data(std::move(other._zguard_conveter_data)),
			_zguard_converter_ports_data(std::move(other._zguard_converter_ports_data)),
			_zguard_controllers_data_list(std::move(other._zguard_controllers_data_list)),
			_zguard_converter_available(std::move(other._zguard_converter_available)),
			_zguard_controllers_available_list(std::move(other._zguard_controllers_available_list))
		{
			other._zguard_conveter_data = {};
			other._zguard_converter_ports_data.clear();
			other._zguard_controllers_data_list.clear();
			other._zguard_converter_available = bool();
			other._zguard_controllers_available_list.clear();
		};
		Zguard_Basic_Info(const Zguard_Basic_Info& other) = default;
		Zguard_Basic_Info& operator=(Zguard_Basic_Info&& other) = default;
		Zguard_Basic_Info& operator=(const Zguard_Basic_Info& other) = default;

		~Zguard_Basic_Info() = default;
	};

	using Zguard_Basic_Info_List = std::vector<Zguard_Basic_Info>;
	using Zguard_Basic_Info_List_uRef = std::unique_ptr<Zguard_Basic_Info_List>;
	using Zguard_Basic_Info_List_Ref = std::shared_ptr<Zguard_Basic_Info_List>;
}
#endif