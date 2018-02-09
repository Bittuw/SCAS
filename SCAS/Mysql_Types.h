#pragma once

///
/// Represent mysql's data types
///

#ifndef DATA_BASE_STRUCTS
#define DATA_BASE_STRUCTS

#include <algorithm>
#include <mysql_devapi.h>

namespace Mysql_Types {

////////// Next new veiw of data_type
	
	using std::string;

#define Mysql_Generic_Type_Fields \
	/*Done*/X(unsigned int, _id)

#define Mysql_Converter_Data_Type_Field \
	/*Done*/X(unsigned int, _nSn) \
	/*Done*/X(string, _type_name) \
	/*Done*/X(unsigned int, _version) \
	/*Done*/X(string, _first_ip_port) \
	/*Done*/X(string, _second_ip_port)

#define Mysql_Controller_Data_Type_Fields \
	/*Done*/X(unsigned int, _nSn) \
	/*Done*/X(string, _type_name) \
	/*Done*/X(unsigned int, _type_code) \
	/*Done*/X(string, _name) \
	/*Done*/X(unsigned int, _max_groups) \
	/*Done*/X(unsigned int, _max_keys) \
	/*Done*/X(unsigned int, _max_events) \
	/*Done*/X(unsigned int, _max_r_event_at_time) \
	/*Done*/X(unsigned int, _max_w_event_at_time) \
	/*Done*/X(unsigned int, _id_converter)

#define Mysql_Group_Data_Type_Fields \
	/*Done*/X(string, _name) \
	/*Done*/X(unsigned int, _time_zone)

#define Mysql_Employee_Data_Type_Fields \
	/*Done*/X(string, _name) \
	/*Done*/X(string, _surname) \
	/*Done*/X(string, _patronymic) \
	/*Done*/X(unsigned int, _card_number) \
	/*Done*/X(unsigned int, _id_groups)

#define Mysql_Group_In_Controller_Data_Type_Fields \
	/*Done*/X(unsigned int, _id_groups) \
	/*Done*/X(unsigned int, _id_controllers) \
	/*Done*/X(unsigned int, _id_converter) \
	/*Done*/X(unsigned int, _position_in_controller)

	//// POD defines

#define Mysql_POD_Converter_Data_Type_Field \
	/*Done*/X(unsigned int, _nSn) \
	/*Done*/X(char, _type_name[45])\
	/*Done*/X(unsigned int, _version) \
	/*Done*/X(char, _first_ip_port[45]) \
	/*Done*/X(char, _second_ip_port[45])

#define Mysql_POD_Controller_Data_Type_Fields \
	/*Done*/X(unsigned int, _nSn) \
	/*Done*/X(char, _type_name[45]) \
	/*Done*/X(unsigned int, _type_code) \
	/*Done*/X(char, _name[45]) \
	/*Done*/X(unsigned int, _max_groups) \
	/*Done*/X(unsigned int, _max_keys) \
	/*Done*/X(unsigned int, _max_events) \
	/*Done*/X(unsigned int, _max_r_event_at_time) \
	/*Done*/X(unsigned int, _max_w_event_at_time) \
	/*Done*/X(unsigned int, _id_converter)

#define Mysql_POD_Group_Data_Type_Fields \
	/*Done*/X(char, _name[45]) \
	/*Done*/X(unsigned int, _time_zone)

#define Mysql_POD_Employee_Data_Type_Fields \
	/*Done*/X(char, _name[45]) \
	/*Done*/X(char, _surname[45]) \
	/*Done*/X(char, _patronymic[45]) \
	/*Done*/X(unsigned int, _card_number) \
	/*Done*/X(unsigned int, _id_groups)

#define Mysql_POD_Group_In_Controller_Data_Type_Fields \
	/*Done*/X(unsigned int, _id_groups) \
	/*Done*/X(unsigned int, _id_controllers) \
	/*Done*/X(unsigned int, _id_converter) \
	/*Done*/X(unsigned int, _position_in_controller)

	// Next POD's types

	static const std::string TablesNames[] = {
		"converters",
		"controllers",
		"groups",
		"employees",
		"groups_in_controllers"
	};

	struct Mysql_POD_Converter_Data_Type {
#define X(type, name) type name;
		Mysql_Generic_Type_Fields
		Mysql_POD_Converter_Data_Type_Field
#undef X
	};

	struct Mysql_POD_Controller_Data_Type {
#define X(type, name) type name;
		Mysql_Generic_Type_Fields
		Mysql_POD_Controller_Data_Type_Fields
#undef X
	};

	struct Mysql_POD_Group_Data_Type {

#define X(type, name) type name;
		Mysql_Generic_Type_Fields
		Mysql_POD_Group_Data_Type_Fields
#undef X
	};

	struct Mysql_POD_Employee_Data_Type {

#define X(type, name) type name;
		Mysql_Generic_Type_Fields
		Mysql_POD_Employee_Data_Type_Fields
#undef X

	};

	struct Mysql_POD_Group_In_Controller_Data_Type {

#define X(type, name) type name;
		Mysql_Generic_Type_Fields
		Mysql_POD_Group_In_Controller_Data_Type_Fields
#undef X

	};

	///
	/// Next mysql wrappers type
	///

	struct Mysql_Generic_Type {
#define X(type, name) type name;
		Mysql_Generic_Type_Fields
#undef X
		Mysql_Generic_Type() {};
		Mysql_Generic_Type(mysqlx::Value id) : _id(static_cast<int>(id)){};

		Mysql_Generic_Type(Mysql_Generic_Type&& other)
			:
			_id(other._id)
		{
			other._id = 0;
		}
		Mysql_Generic_Type(const Mysql_Generic_Type& other) = default;
		Mysql_Generic_Type& operator=(const Mysql_Generic_Type& other) = default;
		Mysql_Generic_Type& operator=(Mysql_Generic_Type&& other) = default;
		virtual ~Mysql_Generic_Type() = default;
	};

	struct Mysql_Converter_Data_Type : public Mysql_Generic_Type {
		using POD_type = Mysql_POD_Converter_Data_Type;

#define X(type, name) type name;
		Mysql_Converter_Data_Type_Field
#undef X
		Mysql_Converter_Data_Type() {}
		Mysql_Converter_Data_Type(POD_type pod)
			:
			Mysql_Generic_Type(pod._id),
			_nSn(pod._nSn),
			_type_name(pod._type_name),
			_version(pod._version),
			_first_ip_port(pod._first_ip_port),
			_second_ip_port(pod._second_ip_port)

		{}
		Mysql_Converter_Data_Type(mysqlx::Row& row,	int&& count)
			: 
			Mysql_Generic_Type(row.get(count++)),
			_nSn(static_cast<int>(row.get(count++))),
			_type_name(static_cast<mysqlx::string>(row.get(count++))),
			_version(static_cast<unsigned int>(row.get(count++))),
			_first_ip_port(static_cast<mysqlx::string>(row.get(count++))),
			_second_ip_port(static_cast<mysqlx::string>(row.get(count++)))
		{}

		Mysql_Converter_Data_Type(Mysql_Converter_Data_Type&& other) noexcept 
			: 
			Mysql_Generic_Type(std::move(other)),
			_nSn(other._nSn),
			_type_name(std::move(other._type_name)),
			_version(other._version),
			_first_ip_port(std::move(other._first_ip_port)),
			_second_ip_port(std::move(other._second_ip_port))
		{
			other._nSn = 0;
			other._type_name.clear();
			other._version = 0;
			other._first_ip_port.clear();
			other._second_ip_port.clear();
		}
		Mysql_Converter_Data_Type(const Mysql_Converter_Data_Type& other) = default;
		Mysql_Converter_Data_Type& operator=(const Mysql_Converter_Data_Type& other) = default;
		Mysql_Converter_Data_Type& operator=(Mysql_Converter_Data_Type&& other) = default;

		explicit operator POD_type()
		{
			POD_type ret;
			ret._id = this->_id;
			ret._nSn = this->_nSn;
			strncpy_s(ret._type_name, this->_type_name.c_str(), sizeof(ret._type_name));
			ret._version = this->_version;
			strncpy_s(ret._first_ip_port, this->_first_ip_port.c_str(), sizeof(ret._first_ip_port));
			strncpy_s(ret._second_ip_port, this->_second_ip_port.c_str(), sizeof(ret._second_ip_port));
			return ret;
		}
		/*friend std::ofstream& operator<<(std::ofstream& stream, Mysql_Converter_Data_Type& object);
		friend std::ifstream& operator>>(std::ifstream& stream, Mysql_Converter_Data_Type& object);*/

		static std::string* _table_name;
	};

	struct Mysql_Controller_Data_Type : public Mysql_Generic_Type {
		using POD_type = Mysql_POD_Controller_Data_Type;

#define X(type, name) type name;
		Mysql_Controller_Data_Type_Fields
#undef X
		Mysql_Controller_Data_Type() {};
		Mysql_Controller_Data_Type(POD_type pod)
			:
			Mysql_Generic_Type(pod._id),
			_nSn(pod._nSn),
			_type_name(pod._type_name),
			_type_code(pod._type_code),
			_name(pod._name),
			_max_groups(pod._max_groups),
			_max_keys(pod._max_keys),
			_max_events(pod._max_events),
			_max_r_event_at_time(pod._max_r_event_at_time),
			_max_w_event_at_time(pod._max_w_event_at_time),
			_id_converter(pod._id_converter)
		{}
		Mysql_Controller_Data_Type(mysqlx::Row& row, int&& count)
			: Mysql_Generic_Type(row.get(count++)),
			_nSn(static_cast<int>(row.get(count++))),
			_type_name(static_cast<mysqlx::string>(row.get(count++))),
			_type_code(static_cast<int>(row.get(count++))),
			_name(static_cast<mysqlx::string>(row.get(count++))),
			_max_groups(static_cast<int>(row.get(count++))),
			_max_keys(static_cast<int>(row.get(count++))),
			_max_events(static_cast<int>(row.get(count++))),
			_max_r_event_at_time(static_cast<int>(row.get(count++))),
			_max_w_event_at_time(static_cast<int>(row.get(count++))),
			_id_converter(static_cast<int>(row.get(count++)))
		{}

		Mysql_Controller_Data_Type(Mysql_Controller_Data_Type&& other) noexcept  
			:
			Mysql_Generic_Type(std::move(other)),
			_nSn(other._nSn),
			_type_name(std::move(other._type_name)),
			_type_code(other._type_code),
			_name(std::move(other._name)),
			_max_groups(other._max_groups),
			_max_keys(other._max_keys),
			_max_events(other._max_events),
			_max_r_event_at_time(other._max_r_event_at_time),
			_max_w_event_at_time(other._max_w_event_at_time),
			_id_converter(other._id_converter)
		{
			other._nSn = 0;
			other._type_name.clear();
			other._type_code = 0;
			other._name.clear();
			other._max_groups = 0;
			other._max_keys = 0;
			other._max_events = 0;
			other._max_r_event_at_time = 0;
			other._max_w_event_at_time = 0;
			other._id_converter = 0;
		}
		Mysql_Controller_Data_Type(const Mysql_Controller_Data_Type& other) = default;
		Mysql_Controller_Data_Type& operator=(const Mysql_Controller_Data_Type& other) = default;
		Mysql_Controller_Data_Type& operator=(Mysql_Controller_Data_Type&& other) = default;

		explicit operator POD_type()
		{
			POD_type ret;
			ret._id = this->_id;
			ret._nSn = this->_nSn;
			strcpy_s(ret._type_name, this->_type_name.c_str());
			ret._type_code = this->_type_code;
			strcpy_s(ret._name, this->_name.c_str());
			ret._max_groups = this->_max_groups;
			ret._max_keys = this->_max_keys;
			ret._max_events = this->_max_events;
			ret._max_r_event_at_time = this->_max_r_event_at_time;
			ret._max_w_event_at_time = this->_max_w_event_at_time;
			ret._id_converter = this->_id_converter;
			return ret;
		}
		static std::string* _table_name;
	};

	struct Mysql_Group_Data_Type : public Mysql_Generic_Type {
		using POD_type = Mysql_POD_Group_Data_Type;

#define X(type, name) type name;
		Mysql_Group_Data_Type_Fields
#undef X
		Mysql_Group_Data_Type() {};
		Mysql_Group_Data_Type(const POD_type& pod)
			:
			Mysql_Generic_Type(pod._id),
			_name(pod._name),
			_time_zone(pod._time_zone)
		{}
		Mysql_Group_Data_Type(mysqlx::Row& row, int&& count)
			: Mysql_Generic_Type(row.get(count++)),
			_name(static_cast<mysqlx::string>(row.get(count++))),
			_time_zone(static_cast<int>(row.get(count++)))
		{}

		Mysql_Group_Data_Type(Mysql_Group_Data_Type&& other) noexcept 
			:
			Mysql_Generic_Type(std::move(other)),
			_name(std::move(other._name)),
			_time_zone(other._time_zone)
		{
			other._name.clear();
			other._time_zone = 0;
		}
		Mysql_Group_Data_Type(const Mysql_Group_Data_Type& other) = default;
		Mysql_Group_Data_Type& operator=(const Mysql_Group_Data_Type& other) = default;
		Mysql_Group_Data_Type& operator=(Mysql_Group_Data_Type&& other) = default;

		explicit operator POD_type()
		{
			Mysql_POD_Group_Data_Type ret;
			ret._id = this->_id;
			strncpy_s(ret._name, this->_name.c_str(), sizeof(ret._name));
			ret._time_zone = this->_time_zone;
			return ret;
		}
		/*friend std::ofstream& operator<<(std::ofstream& stream, Mysql_Group_Data_Type& object);
		friend std::ifstream& operator>>(std::ifstream& stream, Mysql_Group_Data_Type& object);*/
		static std::string* _table_name;
	};

	struct Mysql_Employee_Data_Type : public Mysql_Generic_Type { // TODO move
		using POD_type = Mysql_POD_Employee_Data_Type;

#define X(type, name) type name;
		Mysql_Employee_Data_Type_Fields
#undef X
		Mysql_Employee_Data_Type() {};
		Mysql_Employee_Data_Type(const POD_type& pod)
			:
			Mysql_Generic_Type(pod._id),
			_name(pod._name),
			_surname(pod._surname),
			_patronymic(pod._patronymic),
			_card_number(pod._card_number)
		{}
		Mysql_Employee_Data_Type(mysqlx::Row& row, int&& count)
			: Mysql_Generic_Type(row.get(count++)),
			_name(static_cast<mysqlx::string>(row.get(count++))),
			_surname(static_cast<mysqlx::string>(row.get(count++))),
			_patronymic(static_cast<mysqlx::string>(row.get(count++))),
			_card_number(static_cast<int>(row.get(count++))),
			_id_groups(static_cast<int>(row.get(count++)))
		{}

		Mysql_Employee_Data_Type(Mysql_Employee_Data_Type&& other) noexcept
			:
			Mysql_Generic_Type(std::move(other)),
			_name(std::move(other._name)),
			_surname(std::move(other._surname)),
			_patronymic(std::move(other._patronymic)),
			_card_number(other._card_number),
			_id_groups(other._id_groups)
		{
			other._name.clear();
			other._surname.clear();
			other._patronymic.clear();
			other._card_number = 0;
			other._id_groups = 0;
		}
		Mysql_Employee_Data_Type(const Mysql_Employee_Data_Type& other) = default;
		Mysql_Employee_Data_Type& operator=(const Mysql_Employee_Data_Type& other) = default;
		Mysql_Employee_Data_Type& operator=(Mysql_Employee_Data_Type&& other) = default;

		explicit operator POD_type()
		{
			Mysql_POD_Employee_Data_Type ret;
			ret._id = this->_id;
			strncpy_s(ret._name, this->_name.c_str(), sizeof(ret._name));
			strncpy_s(ret._surname, this->_surname.c_str(), sizeof(ret._surname));
			strncpy_s(ret._patronymic, this->_patronymic.c_str(), sizeof(ret._patronymic));
			ret._card_number = this->_card_number;
			ret._id_groups = this->_id_groups;
			return ret;
		}
		static std::string* _table_name;
	};

	struct Mysql_Group_In_Controller_Data_Type : public Mysql_Generic_Type { // TODO move
		using POD_type = Mysql_POD_Group_In_Controller_Data_Type;

#define X(type, name) type name;
		Mysql_Group_In_Controller_Data_Type_Fields
#undef X
		Mysql_Group_In_Controller_Data_Type() {};
		Mysql_Group_In_Controller_Data_Type(const POD_type& pod)
			:
			Mysql_Generic_Type(std::move(pod._id)),
			_id_groups(std::move(pod._id_groups)),
			_id_controllers(std::move(pod._id_controllers)),
			_id_converter(std::move(pod._id_converter)),
			_position_in_controller(std::move(pod._position_in_controller))
		{}
		Mysql_Group_In_Controller_Data_Type(mysqlx::Row& row, int&& count)
			: Mysql_Generic_Type(row.get(count++)),
			_id_groups(static_cast<int>(row.get(count++))),
			_id_controllers(static_cast<int>(row.get(count++))),
			_id_converter(static_cast<int>(row.get(count++))),
			_position_in_controller(static_cast<int>(row.get(count++)))
		{}

		Mysql_Group_In_Controller_Data_Type(Mysql_Group_In_Controller_Data_Type&& other) noexcept
			:
			Mysql_Generic_Type(std::move(other)),
			_id_groups(other._id_groups),
			_id_controllers(other._id_controllers),
			_id_converter(other._id_converter),
			_position_in_controller(other._position_in_controller)
		{
			other._id_groups = 0;
			other._id_controllers = 0;
			other._id_converter = 0;
			other._position_in_controller = 0;
		}
		Mysql_Group_In_Controller_Data_Type(const Mysql_Group_In_Controller_Data_Type& other) = default;
		Mysql_Group_In_Controller_Data_Type& operator=(const Mysql_Group_In_Controller_Data_Type& other) = default;
		Mysql_Group_In_Controller_Data_Type& operator=(Mysql_Group_In_Controller_Data_Type&& other) = default;

		explicit operator POD_type()
		{
			Mysql_POD_Group_In_Controller_Data_Type ret = {
				this->_id,
				this->_id_groups,
				this->_id_controllers,
				this->_id_converter,
				this->_position_in_controller
			};
			return ret;
		}
		/*friend std::ofstream& operator<<(std::ofstream& stream, Mysql_Group_In_Controller_Data_Type& object);
		friend std::ifstream& operator>>(std::ifstream& stream, Mysql_Group_In_Controller_Data_Type& object);*/
		static std::string* _table_name;
	};


	//Lists of types
	using Mysql_Converters_Data_List = std::vector<Mysql_Converter_Data_Type>;
	using Mysql_Controllers_Data_List = std::vector<Mysql_Controller_Data_Type>;
	using Mysql_Groups_Data_List = std::vector<Mysql_Group_Data_Type>;
	using Mysql_Employees_Data_List = std::vector<Mysql_Employee_Data_Type>;
	using Mysql_Groups_In_Controllers_Data_List = std::vector<Mysql_Group_In_Controller_Data_Type>;

	//For Mysql_Users_Basic_Info
	using Mysql_Groups_In_Controllers_Data_Ref = std::shared_ptr<Mysql_Group_In_Controller_Data_Type>;
	using Mysql_Groups_In_Controllers_Data_Ref_List = std::vector<Mysql_Groups_In_Controllers_Data_Ref>;
	using Mysql_Controller_Data_Ref = std::shared_ptr<Mysql_Controller_Data_Type>;
	using Mysql_Groups_Data_List_Ref = std::shared_ptr<Mysql_Groups_Data_List>;
	using Mysql_Employees_Data_List_Ref = std::shared_ptr<Mysql_Employees_Data_List>;
}



namespace Mysql_Basic_Info_Types {
	
	using namespace Mysql_Types;

	struct Mysql_Basic_Info { 

	public:
		Mysql_Converter_Data_Type _mysql_converter_data;
		Mysql_Controllers_Data_List _mysql_controllers_data_list;

		Mysql_Basic_Info(const Mysql_Converter_Data_Type& mysql_converter_data, const Mysql_Controllers_Data_List& mysql_controllers_data_list)
		:	
			_mysql_converter_data(mysql_converter_data),
			_mysql_controllers_data_list()
		{
			Mysql_Types::Mysql_Controllers_Data_List::const_iterator result;
			Mysql_Types::Mysql_Controllers_Data_List::const_iterator start_from = mysql_controllers_data_list.cbegin();
			while (
				(
					result = std::find_if
					(
						start_from,
						mysql_controllers_data_list.cend(),
						[this](const Mysql_Types::Mysql_Controller_Data_Type& _constroller)
						{ return _constroller._id_converter == _mysql_converter_data._id; }
					)
				) != mysql_controllers_data_list.cend()
			)
			{
				_mysql_controllers_data_list.push_back(*result);
				start_from = result + 1;
			}
		}

		Mysql_Basic_Info(Mysql_Basic_Info&& other) 
		: 
			_mysql_converter_data(std::move(other._mysql_converter_data)),
			_mysql_controllers_data_list(std::move(other._mysql_controllers_data_list))
		{
			/*other._mysql_controllers_data_list.clear();
			other._mysql_controllers_data_list.shrink_to_fit();*/
		}
		Mysql_Basic_Info(const Mysql_Basic_Info& other) = default;
		Mysql_Basic_Info& operator=(Mysql_Basic_Info&& other) = default;
		Mysql_Basic_Info& operator=(const Mysql_Basic_Info& other) = default;

		~Mysql_Basic_Info() = default;
	};

	// Basic usage
	using Mysql_Basic_Info_Ref = std::shared_ptr<Mysql_Basic_Info>;
	using Mysql_Basic_Info_List = std::vector<Mysql_Basic_Info>;
	using Mysql_Basic_Info_List_Ref = std::shared_ptr<Mysql_Basic_Info_List>;
	using Mysql_Basic_Info_Ref_List = std::vector<Mysql_Basic_Info_Ref>;
	using Mysql_Basic_Info_Ref_List_Ref = std::shared_ptr<Mysql_Basic_Info_Ref_List>;

	struct Mysql_Users_Basic_Info { 
	public:
		Mysql_Controller_Data_Ref _mysql_controller_data_ref;
		Mysql_Groups_Data_List_Ref _mysqll_groups_data_list_ref;
		Mysql_Employees_Data_List_Ref _mysql_employees_data_list_ref;

		Mysql_Users_Basic_Info(const Mysql_Controller_Data_Type& mysql_controller_data, const Mysql_Groups_In_Controllers_Data_List& mysql_groups_in_controllers_data_list, const Mysql_Groups_Data_List& mysql_groups_data_list, const Mysql_Employees_Data_List& mysql_employees_data_list)
			:
			_mysql_controller_data_ref(std::make_shared<Mysql_Controller_Data_Type>(mysql_controller_data)),
			_mysqll_groups_data_list_ref(std::make_shared<Mysql_Groups_Data_List>()),
			_mysql_employees_data_list_ref(std::make_shared<Mysql_Employees_Data_List>())
		{
			Mysql_Groups_In_Controllers_Data_List::const_iterator result_a;
			Mysql_Groups_In_Controllers_Data_List::const_iterator start_from_a = mysql_groups_in_controllers_data_list.cbegin();
			Mysql_Groups_In_Controllers_Data_List temp_mysql_groups_in_controllers_data_list;

			while
				(
					(result_a = std::find_if(
							start_from_a,
							mysql_groups_in_controllers_data_list.cend(),
							[this](const Mysql_Group_In_Controller_Data_Type& mysql_group_in_controller_data)->decltype(auto)
							{
								return _mysql_controller_data_ref->_id == mysql_group_in_controller_data._id_controllers;
							}
						)
					) != mysql_groups_in_controllers_data_list.cend()
				) 
			{
				temp_mysql_groups_in_controllers_data_list.push_back(*result_a);
				start_from_a = result_a + 1;
			}

			for (auto& mysql_groupd_in_controller_data: temp_mysql_groups_in_controllers_data_list) {

				Mysql_Groups_Data_List::const_iterator result_b;
				Mysql_Groups_Data_List::const_iterator start_from_b = mysql_groups_data_list.cbegin();

				while
					(
						(result_b = std::find_if(
							start_from_b, 
							mysql_groups_data_list.cend(), 
							[&mysql_groupd_in_controller_data](const Mysql_Group_Data_Type& mysql_group_data) -> decltype(auto) 
							{ 
								return mysql_group_data._id == mysql_groupd_in_controller_data._id_groups;
							}
							)
						) != mysql_groups_data_list.cend()
					)
				{
					_mysqll_groups_data_list_ref->push_back(*result_b);
					start_from_b = result_b + 1;
				}
			}

			for (auto& mysql_group_data : *_mysqll_groups_data_list_ref) 
			{
				Mysql_Employees_Data_List::const_iterator result_c;
				Mysql_Employees_Data_List::const_iterator start_from_c = mysql_employees_data_list.cbegin();

				while 
					(
						(result_c = std::find_if(
							start_from_c,
							mysql_employees_data_list.cend(),
							[&mysql_group_data](const Mysql_Employee_Data_Type& mysql_employee_data) -> decltype(auto) 
							{ 
								return mysql_employee_data._id_groups == mysql_group_data._id;
							}
							)
						) != mysql_employees_data_list.cend())
				{
					_mysql_employees_data_list_ref->push_back(*result_c);
					start_from_c = result_c + 1;
				}
			}
			
		}
		
		Mysql_Users_Basic_Info(Mysql_Users_Basic_Info&& other) 
			:
			_mysql_controller_data_ref(std::move(other._mysql_controller_data_ref)),
			_mysqll_groups_data_list_ref(std::move(other._mysqll_groups_data_list_ref)),
			_mysql_employees_data_list_ref(std::move(other._mysql_employees_data_list_ref))
		{

		}
		Mysql_Users_Basic_Info(const Mysql_Users_Basic_Info& other) = default;
		Mysql_Users_Basic_Info& operator=(Mysql_Users_Basic_Info&& other) = default;
		Mysql_Users_Basic_Info& operator=(const Mysql_Users_Basic_Info& other) = default;

		~Mysql_Users_Basic_Info() = default;
	};

	using Mysql_Users_Basic_Info_Ref = std::shared_ptr<Mysql_Users_Basic_Info>;
	using Mysql_Users_Basic_Info_List = std::vector<Mysql_Users_Basic_Info>;
	using Mysql_Users_Basic_Info_List_ref = std::shared_ptr<Mysql_Users_Basic_Info_List>;
}
#endif