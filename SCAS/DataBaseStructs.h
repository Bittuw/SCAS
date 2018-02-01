#pragma once

#ifndef DATA_BASE_STRUCTS
#define DATA_BASE_STRUCTS

namespace Common_Database_Types {

////////// Next new veiw of data_type

#define Mysql_Generic_Type_Fields \
	/*Done*/X(unsigned int, _id)

#define Mysql_Converter_Data_Type_Field \
	/*Done*/X(unsigned int, _nSn) \
	/*Done*/X(std::string, _type_name) \
	/*Done*/X(unsigned int, _version) \
	/*Done*/X(std::string, _first_ip_port) \
	/*Done*/X(std::string, _second_ip_port)

#define Mysql_Controller_Data_Type_Fields \
	/*Done*/X(unsigned int, _nSn) \
	/*Done*/X(std::string, _type_name) \
	/*Done*/X(unsigned int, _type_code) \
	/*Done*/X(std::string, _name) \
	/*Done*/X(unsigned int, _max_groups) \
	/*Done*/X(unsigned int, _max_keys) \
	/*Done*/X(unsigned int, _max_events) \
	/*Done*/X(unsigned int,	_max_r_event_at_time) \
	/*Done*/X(unsigned int, _max_w_event_at_time) \
	/*Done*/X(unsigned int, _id_converter)

#define Mysql_Group_Data_Type_Fields \
	/*Done*/X(std::string, _name) \
	/*Done*/X(unsigned int, _time_zone)

#define Mysql_Employee_Data_Type_Fields \
	/*Done*/X(std::string, _name) \
	/*Done*/X(std::string, _surname) \
	/*Done*/X(std::string, _patronymic) \
	/*Done*/X(unsigned int, _card_number) \
	/*Done*/X(unsigned int, _id_groups)

#define Mysql_Group_In_Controller_Data_Type_Fields \
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
		Mysql_Converter_Data_Type_Field
#undef X
	};

	struct Mysql_POD_Controller_Data_Type {
#define X(type, name) type name;
		Mysql_Generic_Type_Fields
		Mysql_Controller_Data_Type_Fields
#undef X
	};

	struct Mysql_POD_Group_Data_Type {
#define X(type, name) type name;
		Mysql_Generic_Type_Fields
		Mysql_Group_Data_Type_Fields
#undef X
	};

	struct Mysql_POD_Employee_Data_Type {
#define X(type, name) type name;
		Mysql_Generic_Type_Fields
		Mysql_Employee_Data_Type_Fields
#undef X
	};

	struct Mysql_POD_Group_In_Controller_Data_Type {
#define X(type, name) type name;
		Mysql_Generic_Type_Fields
		Mysql_Group_In_Controller_Data_Type_Fields
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
		Mysql_Generic_Type(int id)
			: _id(id)
		{}
		Mysql_Generic_Type(const Mysql_Generic_Type& other) = default;
		Mysql_Generic_Type(mysqlx::Value id) : _id(static_cast<int>(id)){};
		Mysql_Generic_Type(Mysql_Generic_Type&& other)
			:
			_id(other._id)
		{
			other._id = 0;
		}
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
		Mysql_Converter_Data_Type(const Mysql_Converter_Data_Type& other) = default;
		Mysql_Converter_Data_Type(mysqlx::Row& row,	int&& count)
			: 
			Mysql_Generic_Type(row.get(count++)),
			_nSn(static_cast<int>(row.get(count++))),
			_type_name(static_cast<mysqlx::string>(row.get(count++))),
			_version(static_cast<unsigned int>(row.get(count++))),
			_first_ip_port(static_cast<mysqlx::string>(row.get(count++))),
			_second_ip_port(static_cast<mysqlx::string>(row.get(count++)))
		{}
		Mysql_Converter_Data_Type(Mysql_Converter_Data_Type&& other) 
			: 
			Mysql_Generic_Type(std::move(other)),
			_nSn(other._nSn),
			_type_name(other._type_name),
			_version(other._version),
			_first_ip_port(other._first_ip_port),
			_second_ip_port(other._second_ip_port)
		{
			other._nSn = 0;
			other._type_name.clear();
			other._version = 0;
			other._first_ip_port.clear();
			other._second_ip_port.clear();
		}
		Mysql_Converter_Data_Type& operator=(const Mysql_Converter_Data_Type& other) = default;
		Mysql_Converter_Data_Type& operator=(Mysql_Converter_Data_Type&& other) = default;

		explicit operator POD_type()
		{
			POD_type ret = {
				this->_id,
				this->_nSn,
				this->_type_name,
				this->_version,
				this->_first_ip_port,
				this->_second_ip_port
			};
			return ret;
		}

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
		Mysql_Controller_Data_Type(const Mysql_Controller_Data_Type& other) = default;
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
		Mysql_Controller_Data_Type(Mysql_Controller_Data_Type&& other) 
			:
			Mysql_Generic_Type(std::move(other)),
			_nSn(other._nSn),
			_type_name(other._type_name),
			_type_code(other._type_code),
			_name(other._name),
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
		Mysql_Controller_Data_Type& operator=(const Mysql_Controller_Data_Type& other) = default;
		Mysql_Controller_Data_Type& operator=(Mysql_Controller_Data_Type&& other) = default;

		explicit operator POD_type()
		{
			POD_type ret = {
				this->_id,
				this->_nSn,
				this->_type_name,
				this->_type_code,
				this->_name,
				this->_max_groups,
				this->_max_keys,
				this->_max_events,
				this->_max_r_event_at_time,
				this->_max_w_event_at_time,
				this->_id_converter
			};
			return ret;
		}

		static std::string* _table_name;
	};

	struct Mysql_Group_Data_Type : public Mysql_Generic_Type { // TODO move
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
		Mysql_Group_Data_Type(const Mysql_Group_Data_Type& other) = default;
		Mysql_Group_Data_Type(mysqlx::Row& row, int&& count)
			: Mysql_Generic_Type(row.get(count++)),
			_name(static_cast<mysqlx::string>(row.get(count++))),
			_time_zone(static_cast<int>(row.get(count++)))
		{}
		Mysql_Group_Data_Type(Mysql_Group_Data_Type&& other) 
			:
			Mysql_Generic_Type(std::move(other)),
			_name(other._name),
			_time_zone(other._time_zone)
		{
			other._name.clear();
			other._time_zone = 0;
		}
		Mysql_Group_Data_Type& operator=(const Mysql_Group_Data_Type& other) = default;
		Mysql_Group_Data_Type& operator=(Mysql_Group_Data_Type&& other) = default;

		explicit operator POD_type()
		{
			Mysql_POD_Group_Data_Type ret = {
				this->_id,
				this->_name,
				this->_time_zone
			};
			return ret;
		}

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
			Mysql_Generic_Type(std::move(pod._id)),
			_name(std::move(pod._name)),
			_surname(std::move(pod._surname)),
			_patronymic(std::move(pod._patronymic)),
			_card_number(std::move(pod._card_number))
		{}
		Mysql_Employee_Data_Type(const Mysql_Employee_Data_Type& other) = default;
		Mysql_Employee_Data_Type(mysqlx::Row& row, int&& count)
			: Mysql_Generic_Type(row.get(count++)),
			_name(static_cast<mysqlx::string>(row.get(count++))),
			_surname(static_cast<mysqlx::string>(row.get(count++))),
			_patronymic(static_cast<mysqlx::string>(row.get(count++))),
			_card_number(static_cast<int>(row.get(count++)))
		{}
		Mysql_Employee_Data_Type(Mysql_Employee_Data_Type&& other)
			:
			Mysql_Generic_Type(std::move(other)),
			_name(other._name),
			_surname(other._surname),
			_patronymic(other._patronymic),
			_card_number(other._card_number)
		{
			other._name.clear();
			other._surname.clear();
			other._patronymic.clear();
			other._card_number = 0;
		}
		Mysql_Employee_Data_Type& operator=(const Mysql_Employee_Data_Type& other) = default;
		Mysql_Employee_Data_Type& operator=(Mysql_Employee_Data_Type&& other) = default;

		explicit operator POD_type()
		{
			Mysql_POD_Employee_Data_Type ret = {
				this->_id,
				this->_name,
				this->_surname,
				this->_patronymic,
				this->_card_number,
			};
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
		Mysql_Group_In_Controller_Data_Type(const Mysql_Group_In_Controller_Data_Type& other) = default;
		Mysql_Group_In_Controller_Data_Type(mysqlx::Row& row, int&& count)
			: Mysql_Generic_Type(row.get(count++)),
			_id_groups(static_cast<int>(row.get(count++))),
			_id_controllers(static_cast<int>(row.get(count++))),
			_id_converter(static_cast<int>(row.get(count++))),
			_position_in_controller(static_cast<int>(row.get(count++)))
		{}
		Mysql_Group_In_Controller_Data_Type(Mysql_Group_In_Controller_Data_Type&& other) 
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


	//Lists of types
	using Converters_Data_List = std::vector<Mysql_Converter_Data_Type>;
	using Controllers_Data_List = std::vector<Mysql_Controller_Data_Type>;
	using Groups_Data_List = std::vector<Mysql_Group_Data_Type>;
	using Employees_Data_List = std::vector<Mysql_Employee_Data_Type>;
	using Groups_In_Controllers_Data_List = std::vector<Mysql_Group_In_Controller_Data_Type>;
}


namespace Common_DataBaseLayer_Types {

	struct Basic_Info {

	public:
		Common_Database_Types::Mysql_Converter_Data_Type _mysql_converter_data;
		Common_Database_Types::Controllers_Data_List _mysql_controllers_data_list;

		Basic_Info(const Common_Database_Types::Mysql_Converter_Data_Type& mysql_converter_data, const Common_Database_Types::Controllers_Data_List& mysql_controllers_data_list)
		:	
			_mysql_converter_data(mysql_converter_data),
			_mysql_controllers_data_list()
		{
			Common_Database_Types::Controllers_Data_List::const_iterator result;
			Common_Database_Types::Controllers_Data_List::const_iterator start_from = mysql_controllers_data_list.cbegin();
			while (
				(
					result = std::find_if
					(
						start_from,
						mysql_controllers_data_list.cend(),
						[this](const Common_Database_Types::Mysql_Controller_Data_Type& _constroller)
						{ return _constroller._id_converter == _mysql_converter_data._id; }
					)
				) != mysql_controllers_data_list.end()
			)
			{
				_mysql_controllers_data_list.push_back(*result);
				start_from = result + 1;
			}
		}
		Basic_Info(Basic_Info&& other) 
		: 
			_mysql_converter_data(std::move(other._mysql_converter_data)),
			_mysql_controllers_data_list(std::move(other._mysql_controllers_data_list))
		{
			other._mysql_converter_data;
		}

		Basic_Info& operator=(Basic_Info&& other) = default;
		Basic_Info& operator=(const Basic_Info& other) = default;
	};

	// Basic usage
	using Basic_Info_Ref = std::shared_ptr<Basic_Info>;
	using Basic_Info_List = std::vector<Basic_Info>;
	using Basic_Info_List_Ref = std::shared_ptr<Basic_Info_List>;
	using Basic_Info_Ref_List = std::vector<Basic_Info_Ref>;
	using Basic_Info_Ref_List_Ref = std::shared_ptr<Basic_Info_Ref_List>;
}
#endif