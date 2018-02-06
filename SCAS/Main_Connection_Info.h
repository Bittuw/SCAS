#pragma once

#ifndef MAIN_CONNECION_INFO
#define MAIN_CONNECION_INFO

#include <string>
#include "ZGuard.h"
#include <mutex>

#include "Mysql_Types.h"
#include "Zguard_Types.h"

namespace Main_Connection_Basic_Info_Types {

	using namespace Zguard_Basic_Info_Types;
	using namespace Mysql_Basic_Info_Types;

#define Connection_Error_Code_Types \
	X(UNDEFINE, 0) \
	X(SUCCESS, 1) \
	X(CONVERTER_OPEN_FAIL, 2) \
	X(CONVERTER_COMMAND_FAIL, 3) \
	X(CONTROLLER_OPEN_FAIL, 4) \
	X(CONTROLLER_COMMAND_FAIL , 5) \
	X(CONNECTION_FAIL, 6)

#define Main_Basic_Converter_Data_Type_Fields \
	X(unsigned int, _nSn)\
	X(std::wstring, _type_name)\
	X(std::wstring, _first_ip_port)\
	X(std::wstring, _second_ip_port)

#define Main_Basic_Controller_Data_Type_Fields \
	X(unsigned int, _nSn)\
	X(std::wstring, _type_name)\
	X(std::wstring, _name)\
	X(unsigned int, _max_groups)\
	X(unsigned int, _max_keys)\
	X(unsigned int, _max_events)\
	X(unsigned int, _max_r_event_at_time)\
	X(unsigned int, _max_w_event_at_time) 


	enum class Connection_Error_Code {
#define X(name, value) name = value,
		Connection_Error_Code_Types
#undef X
	};

	static std::string Connection_Error_Code_String[] = {
#define X(name, value) #name,
		Connection_Error_Code_Types
#undef X
	};

	using Converter_Handle = HANDLE;
	using Converter_Detail_Info = _ZG_CVT_INFO;
	using Converter_Detail_Info_Ref = std::shared_ptr<Converter_Detail_Info>;
	using Converter_Port_Info = _ZP_PORT_INFO;
	using Converter_Ports_Info_List = std::vector<Converter_Port_Info>;
	using Converter_Ports_Info_List_Ref = std::shared_ptr<Converter_Ports_Info_List>;
	using Converter_Connection_Status = bool;

	// Common controller's information types
	using Controller_Handle = HANDLE;
	using Controller_Info = _ZG_FIND_CTR_INFO;
	using Controllers_Info_List = std::vector<Controller_Info>;
	using Controllers_Info_List_Ref = std::shared_ptr<Controllers_Info_List>;
	using Controllers_Handles_List = std::vector<Controller_Handle>;
	using Controller_Detail_Info = _ZG_CTR_INFO;
	using Controllers_Detail_Info_List = std::vector<Controller_Detail_Info>;
	using Controllers_Detail_Info_List_Ref = std::shared_ptr<Controllers_Detail_Info_List>;
	using Controller_Connection_Status = bool;
	using Controllers_Connection_Status_List = std::vector<Controller_Connection_Status>;
	using Controllers_Connection_Status_List_ref = std::shared_ptr<Controllers_Connection_Status_List>;
	using Controller_Index_Read_Write = std::pair<int, int>;;
	using Controllers_Index_Read_Write_List = std::vector<Controller_Index_Read_Write>;
	using Controllers_Index_Read_Write_List_Ref = std::shared_ptr<Controllers_Index_Read_Write_List>;

	using Connection_Mutex_Ref = std::shared_ptr<std::mutex>;
	using Connection_Type = ZP_PORT_TYPE;

	//using Global_Connections_List_Ref = std::unique_ptr<SpecialList>;

	// Структура, которая используется/заполняется в runtime
	struct Runtime_Info {

		//Converter info
		Converter_Handle _converter_handle;
		Converter_Detail_Info _converter_detail_info;
		Converter_Connection_Status _converter_connection_info;

		//Controller info
		Controllers_Detail_Info_List _controllers_detail_info_list;
		Controllers_Connection_Status_List _controllers_connection_status_list;
		Controllers_Index_Read_Write_List _controllers_index_read_write_list;

		//Converter connection info
		Connection_Type _connection_type;

		//Mutex of access
		Connection_Mutex_Ref _mutex;

		Runtime_Info()
			:
			_converter_handle(),
			_converter_detail_info(),
			_converter_connection_info(),
			_controllers_detail_info_list(),
			_controllers_connection_status_list(),
			_controllers_index_read_write_list(),
			_connection_type(),
			_mutex(std::make_shared<std::mutex>())
		{}

		Runtime_Info(Runtime_Info&& other)
			:
			_converter_detail_info(std::move(other._converter_detail_info)),
			_converter_connection_info(std::move(other._converter_connection_info)),
			_controllers_detail_info_list(std::move(other._controllers_detail_info_list)),
			_controllers_connection_status_list(std::move(other._controllers_connection_status_list)),
			_controllers_index_read_write_list(std::move(other._controllers_index_read_write_list)),
			_connection_type(std::move(other._connection_type)),
			_mutex(std::move(other._mutex))
		{
			memset(&other._converter_detail_info, 0, sizeof(other._converter_detail_info));
			memset(&other._converter_connection_info, 0, sizeof(other._converter_connection_info));
			//other._controllers_detail_info_list;
			//other._controllers_connection_status_list;
			//other._controllers_index_read_write_list;
			other._connection_type = {};
		}
		Runtime_Info(const Runtime_Info& other) = default;
		Runtime_Info& operator=(Runtime_Info&& other) = default;
		Runtime_Info& operator=(const Runtime_Info& other) = default;
		virtual ~Runtime_Info() = default;
	};

	// Структура, которая получает из базовых типов Mysql или Zguard нужные данные про конвертер
	struct Basic_Converter_Data_Type {
#define X(type, name) type name;
		Main_Basic_Converter_Data_Type_Fields
#undef X
		Basic_Converter_Data_Type() = delete;
		Basic_Converter_Data_Type(const Mysql_Converter_Data_Type& mysql_converter_data)
			:
			_nSn(mysql_converter_data._nSn),
			_type_name(mysql_converter_data._type_name.cbegin(), mysql_converter_data._type_name.cend()),
			_first_ip_port(mysql_converter_data._first_ip_port.cbegin(), mysql_converter_data._first_ip_port.cend()),
			_second_ip_port(mysql_converter_data._second_ip_port.cbegin(), mysql_converter_data._second_ip_port.cend())
		{}
		Basic_Converter_Data_Type(const Zguard_Converter_Data_Type& zguard_converter_data, const Zguard_Converter_Ports_Data_List& zguard_ports_data_list)
			:
			_nSn(zguard_converter_data.nSn),
			/*_type_name(zguard_converter_data._type_name),*/
			_first_ip_port(zguard_ports_data_list.at(0).szName),
			_second_ip_port(zguard_ports_data_list.at(1).szName)
		{}

		Basic_Converter_Data_Type(Basic_Converter_Data_Type&& other) 
			:
			_nSn(other._nSn),
			_type_name(std::move(other._type_name)),
			_first_ip_port(std::move(other._first_ip_port)),
			_second_ip_port(std::move(other._second_ip_port))
		{
			other._nSn = 0;
			/*other._type_name.clear();
			other._first_ip_port.clear();
			other._second_ip_port.clear();*/
		}
		Basic_Converter_Data_Type(const Basic_Converter_Data_Type& other) = default;
		Basic_Converter_Data_Type& operator=(Basic_Converter_Data_Type&& other) = default;
		Basic_Converter_Data_Type& operator=(const Basic_Converter_Data_Type& other) = default;

		~Basic_Converter_Data_Type() = default;
	};

	// Структура, которая получает из базовых типов Mysql или Zguard нужные данные про контроллер
	struct  Basic_Controller_Data_Type {
#define X(type, name) type name;
		Main_Basic_Controller_Data_Type_Fields
#undef X
		Basic_Controller_Data_Type() = delete;
		Basic_Controller_Data_Type(const Mysql_Controller_Data_Type& mysql_controller_data) {}
		Basic_Controller_Data_Type(const Zguard_Controller_Data_Type& zguard_controller_data) {}

		Basic_Controller_Data_Type(Basic_Controller_Data_Type&& other)
			:
			_nSn(std::move(other._nSn)),
			_type_name(std::move(other._type_name)),
			 _name(std::move(other._name)),
			_max_groups(other._max_groups),
			_max_keys(other._max_keys),
			_max_events(other._max_events),
			_max_r_event_at_time(other._max_r_event_at_time),
			_max_w_event_at_time(std::move(other._max_w_event_at_time))
		{
			other._nSn = 0;
			/*other._type_name.clear();
			other._name.clear();*/
			other._max_groups = 0 ;
			other._max_keys = 0 ;
			other._max_events = 0;
			other._max_r_event_at_time = 0;
			other._max_w_event_at_time = 0;
		}
		Basic_Controller_Data_Type(const Basic_Controller_Data_Type& other) = default;
		Basic_Controller_Data_Type& operator=(Basic_Controller_Data_Type&& other) = default;
		Basic_Controller_Data_Type& operator=(const Basic_Controller_Data_Type& other) = default;

		~Basic_Controller_Data_Type() = default;
	};

	using Basic_Controllers_Data_List = std::vector<Basic_Controller_Data_Type>;

	// Структура, которая инкапсулируется в объекте Connection (Создается либо из объекта Mysql_Basic_Info, либо  Zguard_basic_Info)
	struct Main_Connection_Basic_Info_Types : Runtime_Info {

		Basic_Converter_Data_Type _converter_main_info;
		Basic_Controllers_Data_List _controllers_main_info_list;

		Main_Connection_Basic_Info_Types(const Mysql_Basic_Info& mysql_basic_info) 
			: 
			Runtime_Info(),
			_converter_main_info(mysql_basic_info._mysql_converter_data)
		{
			std::transform(
				mysql_basic_info._mysql_controllers_data_list.cbegin(),
				mysql_basic_info._mysql_controllers_data_list.cend(),
				std::back_inserter(_controllers_main_info_list),
				[](const Mysql_Controller_Data_Type& mysql_controller_data) -> decltype(auto) {
					return std::move(Basic_Controller_Data_Type(mysql_controller_data));
				}
			);
		}
		Main_Connection_Basic_Info_Types(const Zguard_Basic_Info& zguard_basic_info) 
			: 
			Runtime_Info(),
			_converter_main_info(zguard_basic_info._zguard_conveter_data, zguard_basic_info._zguard_converter_ports_data)
		{
			std::transform(
				zguard_basic_info._zguard_controllers_data_list.cbegin(),
				zguard_basic_info._zguard_controllers_data_list.cend(),
				std::back_inserter(_controllers_main_info_list),
				[](const Zguard_Controller_Data_Type& zguard_controller_data) -> decltype(auto) {
					return std::move(Zguard_Controller_Data_Type(zguard_controller_data));
				}
			);
		}

		~Main_Connection_Basic_Info_Types() = default;
	};

	using Connection_Info_Ref = std::shared_ptr<Main_Connection_Basic_Info_Types>;

}
#endif
