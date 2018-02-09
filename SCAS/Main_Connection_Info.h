#pragma once

#ifndef MAIN_CONNECION_INFO
#define MAIN_CONNECION_INFO

#include <mutex>
#include <string>
#include "ZGuard.h"
#include "Utils.h"

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
	X(std::wstring, _second_ip_port)\
	X(Basic_Controllers_Data_Ref_List, _basic_controllers_data_ref_list)

#define Main_Basic_Controller_Data_Type_Fields \
	X(unsigned int, _nSn)\
	X(std::wstring, _type_name)\
	X(std::wstring, _name)\
	X(unsigned int, _max_groups)\
	X(unsigned int, _max_keys)\
	X(unsigned int, _max_events)\
	X(unsigned int, _max_r_event_at_time)\
	X(unsigned int, _max_w_event_at_time)\
	X(Basic_Groups_Data_Ref_list, _basic_groups_data_ref_list)


#define Main_User_Basic_Data_Type_Fields \
	X(std::wstring, _name)\
	X(std::wstring, _surname)\
	X(std::wstring, _patronymic)\
	X(unsigned int, _card_number)

#define Main_Group_Basic_Data_Type_Fields\
	X(std::wstring, _name)\
	X(unsigned int, _time_zone)\


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

	static std::wstring unnamed = L"Unname";
	static unsigned int rw_events_at_time = 7;

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

	
	//������� �������� ������ ������������
	struct User_Data_Type {
#define X(type, name) type name;
		Main_User_Basic_Data_Type_Fields
#undef X
			User_Data_Type() = delete;
		User_Data_Type(const Mysql_Employee_Data_Type& mysql_employee_data_type)
			:
			_name(mysql_employee_data_type._name.cbegin(), mysql_employee_data_type._name.cend()),
			_surname(mysql_employee_data_type._surname.cbegin(), mysql_employee_data_type._surname.cend()),
			_patronymic(mysql_employee_data_type._patronymic.cbegin(), mysql_employee_data_type._patronymic.cend()),
			_card_number(mysql_employee_data_type._card_number)
		{}

		User_Data_Type(User_Data_Type&& other) noexcept
			:
			_name(std::move(other._name)),
			_surname(std::move(other._surname)),
			_patronymic(std::move(other._patronymic)),
			_card_number(std::move(other._card_number))
		{}
		User_Data_Type(const User_Data_Type& other) = default;
		User_Data_Type& operator=(User_Data_Type&& other) = default;
		User_Data_Type& operator=(const User_Data_Type& other) = default;

		~User_Data_Type() = default;
	};
	using User_Data_Ref = std::shared_ptr<User_Data_Type>;
	struct Basic_User_Data_Type {
		User_Data_Ref _user_data_type;

		Basic_User_Data_Type() = delete;
		Basic_User_Data_Type(const Mysql_Employee_Data_Type& mysql_employee_data_type) 
			:
			_user_data_type(std::make_shared<User_Data_Type>(mysql_employee_data_type))
		{}
		
		Basic_User_Data_Type(Basic_User_Data_Type&& other) noexcept 
			:
			_user_data_type(std::move(other._user_data_type))
		{}
		Basic_User_Data_Type(const Basic_User_Data_Type& other) = default;
		Basic_User_Data_Type& operator=(Basic_User_Data_Type&& other) = default;
		Basic_User_Data_Type& operator=(const Basic_User_Data_Type& other) = default;

		~Basic_User_Data_Type() = default;
	};
	using Basic_User_Data_Ref = std::shared_ptr<Basic_User_Data_Type>;
	using Basic_Users_Data_Ref_List = std::vector<Basic_User_Data_Ref>;
	//��������� �������� ������ ������
	struct Group_Data_Type {
#define X(type, name) type name;
		Main_Group_Basic_Data_Type_Fields
#undef X
		Group_Data_Type() = delete;
		Group_Data_Type(const Mysql_Group_Data_Type& mysql_group_data_type) 
			:
			_name(mysql_group_data_type._name.cbegin(), mysql_group_data_type._name.cend()),
			_time_zone(mysql_group_data_type._time_zone)
		{}

		Group_Data_Type(Group_Data_Type&& other) noexcept 
			:
			_name(std::move(other._name)),
			_time_zone(std::move(other._time_zone))
		{}

		Group_Data_Type(const Group_Data_Type& other) = default;
		Group_Data_Type& operator=(Group_Data_Type&&) = default;
		Group_Data_Type& operator=(const Group_Data_Type&) = default;

		~Group_Data_Type() = default;
	};
	using Group_Data_Ref = std::shared_ptr<Group_Data_Type>;
	struct Basic_Group_Data_Type {
		Group_Data_Ref group_data_type;
		Basic_Users_Data_Ref_List _basic_users_data_ref_list;

		Basic_Group_Data_Type() = delete;
		Basic_Group_Data_Type(const Mysql_Group_Data_Type& mysql_group_data_type, const Mysql_Employees_Data_List& mysql_employees_data_list)
			:
			group_data_type(std::make_shared<Group_Data_Type>(mysql_group_data_type))
		{
			Mysql_Employees_Data_List::const_iterator result;
			Mysql_Employees_Data_List::const_iterator start_from = mysql_employees_data_list.cbegin();
			while (
				(result = std::find_if(
					start_from, 
					mysql_employees_data_list.cend(), 
					[this, &mysql_group_data_type](const Mysql_Employee_Data_Type& mysql_employee_data_type) 
					{ return mysql_group_data_type._id == mysql_employee_data_type._id_groups; }
				)) != mysql_employees_data_list.cend()) 
			{
				_basic_users_data_ref_list.emplace_back(new Basic_User_Data_Type(*result));
				start_from = result++;
			}
		}

		Basic_Group_Data_Type(Basic_Group_Data_Type&& other) noexcept
			:
			group_data_type(std::move(other.group_data_type)),
			_basic_users_data_ref_list(std::move(other._basic_users_data_ref_list))
		{}
		Basic_Group_Data_Type(const Basic_Group_Data_Type& other) = default;
		Basic_Group_Data_Type& operator=(Basic_Group_Data_Type&&) = default;
		Basic_Group_Data_Type& operator=(const Basic_Group_Data_Type&) = default;

		~Basic_Group_Data_Type() = default;
	};
	using Basic_Group_Data_Ref = std::shared_ptr<Basic_Group_Data_Type>;
	using Basic_Groups_Data_Ref_list = std::vector<Basic_Group_Data_Ref>;
	// ���������, ������� �������� �� ������� ����� Mysql ��� Zguard ������ ������ ��� ����������
	struct Basic_Controller_Data_Type {
#define X(type, name) type name;
		Main_Basic_Controller_Data_Type_Fields
#undef X
		Basic_Controller_Data_Type() = delete;
		Basic_Controller_Data_Type(
			const Mysql_Controller_Data_Type& mysql_controller_data, 
			const Mysql_Groups_In_Controllers_Data_List& mysql_groups_in_controllers, 
			const Mysql_Groups_Data_List& mysql_groups_data_list,
			const Mysql_Employees_Data_List& mysql_employees_data_list
		)
			:
			_nSn(mysql_controller_data._nSn),
			_type_name(mysql_controller_data._type_name.cbegin(), mysql_controller_data._type_name.cend()),
			_name(mysql_controller_data._name.cbegin(), mysql_controller_data._name.cend()),
			_max_groups(mysql_controller_data._max_groups),
			_max_keys(mysql_controller_data._max_keys),
			_max_events(mysql_controller_data._max_events),
			_max_r_event_at_time(mysql_controller_data._max_r_event_at_time),
			_max_w_event_at_time(mysql_controller_data._max_w_event_at_time),
			_basic_groups_data_ref_list()
		{
			Mysql_Groups_In_Controllers_Data_List temp;
			Mysql_Groups_In_Controllers_Data_List::const_iterator result_a;
			Mysql_Groups_In_Controllers_Data_List::const_iterator start_from_a = mysql_groups_in_controllers.cbegin();

			while (
				(result_a = std::find_if(
					start_from_a, 
					mysql_groups_in_controllers.cend(), 
					[&mysql_controller_data, &mysql_groups_in_controllers](const Mysql_Group_In_Controller_Data_Type& mysql_group_in_controller_data_type) -> decltype(auto) 
					{ return mysql_group_in_controller_data_type._id_controllers == mysql_controller_data._id; }
					)
				) != mysql_groups_in_controllers.cend()) 
			{
				temp.push_back(*result_a);
				start_from_a = result_a++;
			}

			for (auto& group_in_controller : temp) 
			{
				Mysql_Groups_Data_List::const_iterator result_b;
				Mysql_Groups_Data_List::const_iterator start_from_b = mysql_groups_data_list.cbegin();

				while ((result_b = std::find_if(start_from_b, mysql_groups_data_list.cend(), [&group_in_controller](const Mysql_Group_Data_Type& mysql_group_data_type) -> decltype(auto) { return mysql_group_data_type._id == group_in_controller._id_groups; })) != mysql_groups_data_list.cend()) {
					_basic_groups_data_ref_list.emplace_back(new Basic_Group_Data_Type(*result_b, mysql_employees_data_list));
					start_from_b = result_b++;
				}
			}

		}
		Basic_Controller_Data_Type(const Zguard_Controller_Data_Type& zguard_controller_data)
			:
			_nSn(zguard_controller_data.nSn),
			_type_name(CtrTypeStrs[zguard_controller_data.nType]),
			_name(unnamed),
			_max_groups(ZG_MAX_TIMEZONES),
			_max_keys(zguard_controller_data.nMaxKeys),
			_max_events(zguard_controller_data.nMaxEvents),
			_max_r_event_at_time(rw_events_at_time),
			_max_w_event_at_time(rw_events_at_time)
		{}

		Basic_Controller_Data_Type(Basic_Controller_Data_Type&& other) noexcept
			:
			_nSn(std::move(other._nSn)),
			_type_name(std::move(other._type_name)),
			_name(std::move(other._name)),
			_max_groups(other._max_groups),
			_max_keys(other._max_keys),
			_max_events(other._max_events),
			_max_r_event_at_time(other._max_r_event_at_time),
			_max_w_event_at_time(std::move(other._max_w_event_at_time)),
			_basic_groups_data_ref_list(std::move(other._basic_groups_data_ref_list))
		{
			other._nSn = 0;
			/*other._type_name.clear();
			other._name.clear();*/
			other._max_groups = 0;
			other._max_keys = 0;
			other._max_events = 0;
			other._max_r_event_at_time = 0;
			other._max_w_event_at_time = 0;
		}
		Basic_Controller_Data_Type(const Basic_Controller_Data_Type& other) = default;
		Basic_Controller_Data_Type& operator=(Basic_Controller_Data_Type&& other) = default;
		Basic_Controller_Data_Type& operator=(const Basic_Controller_Data_Type& other) = default;

		~Basic_Controller_Data_Type() = default;
	};
	using Basic_Controller_Data_Ref = std::shared_ptr<Basic_Controller_Data_Type>;
	using Basic_Controllers_Data_Ref_List = std::vector<Basic_Controller_Data_Ref>;
	// ���������, ������� �������� �� ������� ����� Mysql ��� Zguard ������ ������ ��� ���������
	struct Basic_Converter_Data_Type {
#define X(type, name) type name;
		Main_Basic_Converter_Data_Type_Fields
#undef X
			Basic_Converter_Data_Type() = delete;
		Basic_Converter_Data_Type(
			const Mysql_Converter_Data_Type& mysql_converter_data,
			const Mysql_Controllers_Data_List& mysql_controllers_data_list,
			const Mysql_Groups_In_Controllers_Data_List& mysql_groups_in_controllers,
			const Mysql_Groups_Data_List& mysql_groups_data_list,
			const Mysql_Employees_Data_List& mysql_employees_data_list)
			:
			_nSn(mysql_converter_data._nSn),
			_type_name(mysql_converter_data._type_name.cbegin(), mysql_converter_data._type_name.cend()),
			_first_ip_port(mysql_converter_data._first_ip_port.cbegin(), mysql_converter_data._first_ip_port.cend()),
			_second_ip_port(mysql_converter_data._second_ip_port.cbegin(), mysql_converter_data._second_ip_port.cend()),
			_basic_controllers_data_ref_list()
		{
			Mysql_Controllers_Data_List::const_iterator result;
			Mysql_Controllers_Data_List::const_iterator start_from = mysql_controllers_data_list.cbegin();

			while ((result = std::find_if(start_from, mysql_controllers_data_list.cend(), [&mysql_converter_data](const Mysql_Controller_Data_Type& mysql_controller_data_type) -> decltype(auto) { return mysql_controller_data_type._id_converter == mysql_converter_data._id; })) != mysql_controllers_data_list.cend()) {
				_basic_controllers_data_ref_list.emplace_back(new Basic_Controller_Data_Type(*result, mysql_groups_in_controllers, mysql_groups_data_list, mysql_employees_data_list));
				start_from = result++;
			}
		}
		Basic_Converter_Data_Type(const Zguard_Converter_Data_Type& zguard_converter_data, const Zguard_Converter_Ports_Data_List& zguard_ports_data_list)
			:
			_nSn(zguard_converter_data.nSn),
			_type_name(CvtTypeStrs[zguard_converter_data.nType]),
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
		}
		Basic_Converter_Data_Type(const Basic_Converter_Data_Type& other) = default;
		Basic_Converter_Data_Type& operator=(Basic_Converter_Data_Type&& other) = default;
		Basic_Converter_Data_Type& operator=(const Basic_Converter_Data_Type& other) = default;

		~Basic_Converter_Data_Type() = default;
	};
	using Basic_Converter_Data_Ref = std::shared_ptr<Basic_Converter_Data_Type>;
	using Basic_Converters_Data_Ref_List = std::vector<Basic_Converter_Data_Ref>;

	// ���������, ������� ������������/����������� � runtime
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


	// ���������, ������� ��������������� � ������� Connection (��������� ���� �� ������� Mysql_Basic_Info, ����  Zguard_basic_Info)
	struct Main_Connection_Basic_Info_Types : Runtime_Info {

		Basic_Converter_Data_Ref _converter_main_info;

		Main_Connection_Basic_Info_Types(const Basic_Converter_Data_Ref& basic_converter_data_type)
			: 
			Runtime_Info(),
			_converter_main_info(basic_converter_data_type)
		{
		}
		//Main_Connection_Basic_Info_Types(const Zguard_Basic_Info& zguard_basic_info) 
		//	: 
		//	Runtime_Info(),
		//	_converter_main_info(zguard_basic_info._zguard_conveter_data, zguard_basic_info._zguard_converter_ports_data)
		//{
		//	std::transform(
		//		zguard_basic_info._zguard_controllers_data_list.cbegin(),
		//		zguard_basic_info._zguard_controllers_data_list.cend(),
		//		std::back_inserter(_controllers_main_info_list),
		//		[](const Zguard_Controller_Data_Type& zguard_controller_data) -> decltype(auto) {
		//			return Basic_Controller_Data_Type(zguard_controller_data);
		//		}
		//	);
		//}

		~Main_Connection_Basic_Info_Types() = default;
	};

	using Main_Connection_Basic_Info_Ref = std::shared_ptr<Main_Connection_Basic_Info_Types>;
	using Main_Connection_Basic_Info_List = std::vector<Main_Connection_Basic_Info_Types>;
	using Main_Connection_Basic_Info_List_uRef = std::unique_ptr<Main_Connection_Basic_Info_List>;

	template <typename From, typename To>
	struct Transorms {
		static decltype(auto) FromTo(From& upoint) {

			auto return_type = std::make_unique<To::element_type>();

			std::transform(
				upoint->cbegin(),
				upoint->cend(),
				std::back_inserter(*return_type),
				[](const From::element_type::value_type& transformed) -> decltype(auto)
					{
						return To::element_type::value_type(transformed);
					}
				);
			upoint.reset(nullptr);
			return return_type;
		}
	};
}
#endif
