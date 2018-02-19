#pragma once

///
/// Represent mysql's data types
///

#ifndef DATA_BASE_STRUCTS
#define DATA_BASE_STRUCTS

#include <algorithm>
#include <mysql_devapi.h>
#include "Pods.h"

namespace Mysql_Types {

	// Commond Pods types
	using namespace Pods;

	// For Mysql converts
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

	// Mysql tables name !!!
	static const std::string TablesNames[] = {
		"converters",
		"controllers",
		"groups",
		"employees",
		"groups_in_controllers"
	};

	///
	/// Mysql types
	///

	// Generic type with move semantic 
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

	// Converter
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
		static std::string* _table_name;
	};

	// Controller
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

	//Group
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
		static std::string* _table_name;
	};

	// Employee
	struct Mysql_Employee_Data_Type : public Mysql_Generic_Type { 
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
			_card_number(pod._card_number),
			_id_groups(pod._id_groups)
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

	// Group in Controller
	struct Mysql_Group_In_Controller_Data_Type : public Mysql_Generic_Type { 
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
		static std::string* _table_name;
	};

	///
	///Lists of types
	///

	using Mysql_Converters_Data_List = std::vector<Mysql_Converter_Data_Type>;
	using Mysql_Controllers_Data_List = std::vector<Mysql_Controller_Data_Type>;
	using Mysql_Groups_Data_List = std::vector<Mysql_Group_Data_Type>;
	using Mysql_Employees_Data_List = std::vector<Mysql_Employee_Data_Type>;
	using Mysql_Groups_In_Controllers_Data_List = std::vector<Mysql_Group_In_Controller_Data_Type>;
}
#endif