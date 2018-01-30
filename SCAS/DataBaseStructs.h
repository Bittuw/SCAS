#pragma once

#ifndef DATA_BASE_STRUCTS
#define DATA_BASE_STRUCTS

namespace Common_Database_Types {

////////// Next new data types
//
//	// Common type for database types
//	template <typename T>
//	struct Common_Database_Type {
//		T _value;
//		using _type = T;
//		Common_Database_Type() {}
//		Common_Database_Type(const T& value) : _value(value) {}
//		virtual ~Common_Database_Type() {}
//	};
//
//	//Common
//	struct Id_Type : public Common_Database_Type<unsigned int> {
//		Id_Type(const _type& value) : Common_Database_Type(value) {}
//		Id_Type(_type&& value) : Common_Database_Type(std::forward<_type>(value)) {};
//	};
//	struct nSn_Type : public Common_Database_Type<unsigned int> {
//		nSn_Type(const _type& value) : Common_Database_Type(value) {}
//		nSn_Type(_type&& value) : Common_Database_Type(std::forward<_type>(value)) {}
//	};
//	struct Type_Name_Type : public Common_Database_Type<std::string> {
//		Type_Name_Type(const _type& value) : Common_Database_Type(value) {}
//		Type_Name_Type(_type&& value) : Common_Database_Type(std::forward<_type>(value)) {}
//	};
//	struct Name_Type : public Common_Database_Type<std::string> {
//		Name_Type(const _type& value) : Common_Database_Type(value) {}
//		Name_Type(_type&& value) : Common_Database_Type(std::forward<_type>(value)) {}
//	};
//	struct Id_Groups_Type : public Common_Database_Type<unsigned int> {
//		Id_Groups_Type(const _type& value) : Common_Database_Type(value) {}
//		Id_Groups_Type(_type&& value) : Common_Database_Type(std::forward<_type>(value)) {}
//	};
//	struct Id_Converter_Type : public Common_Database_Type<unsigned int> {
//		Id_Converter_Type(const _type& value) : Common_Database_Type(value) {}
//		Id_Converter_Type(_type&& value) : Common_Database_Type(std::forward<_type>(value)) {}
//	};
//	struct id_Controller_Type : public Common_Database_Type<unsigned int> {
//		id_Controller_Type(const _type& value) : Common_Database_Type(value) {}
//		id_Controller_Type(_type&& value) : Common_Database_Type(std::forward<_type>(value)) {}
//	};
//
//	//Converter
//	struct Version_Type : public Common_Database_Type<std::string> {
//		Version_Type(const _type& value) : Common_Database_Type(value) {}
//		Version_Type(_type&& value) : Common_Database_Type(std::forward<_type>(value)) {}
//	};
//	struct First_Ip_Port_Type : public Common_Database_Type<std::string> {
//		First_Ip_Port_Type(const _type& value) : Common_Database_Type(value) {}
//		First_Ip_Port_Type(_type&& value) : Common_Database_Type(std::forward<_type>(value)) {}
//	};
//	struct Second_Ip_Port_Type : public Common_Database_Type<std::string> {
//		Second_Ip_Port_Type(const _type& value) : Common_Database_Type(value) {}
//		Second_Ip_Port_Type(_type&& value) : Common_Database_Type(std::forward<_type>(value)) {}
//	};
//
//	//Controller
//	struct Type_Code_Type : public Common_Database_Type<unsigned int> {
//		Type_Code_Type(const _type& value) : Common_Database_Type(value) {}
//		Type_Code_Type(_type&& value) : Common_Database_Type(std::forward<_type>(value)) {}
//	};
//	struct Max_Groups_Type : public Common_Database_Type<unsigned int> {
//		Max_Groups_Type(const _type& value) : Common_Database_Type(value) {}
//		Max_Groups_Type(_type&& value) : Common_Database_Type(std::forward<_type>(value)) {}
//	};
//	struct Max_Keys_Type : public Common_Database_Type<unsigned int> {
//		Max_Keys_Type(const _type& value) : Common_Database_Type(value) {}
//		Max_Keys_Type(_type&& value) : Common_Database_Type(std::forward<_type>(value)) {}
//	};
//	struct Max_Events_Type : public Common_Database_Type<unsigned int> {
//		Max_Events_Type(const _type& value) : Common_Database_Type(value) {}
//		Max_Events_Type(_type&& value) : Common_Database_Type(std::forward<_type>(value)) {}
//	};
//	struct Max_R_In_Time_Type : public Common_Database_Type<unsigned int> {
//		Max_R_In_Time_Type(const _type& value) : Common_Database_Type(value) {}
//		Max_R_In_Time_Type(_type&& value) : Common_Database_Type(std::forward<_type>(value)) {}
//	};
//	struct Max_W_In_Time_Type : public Common_Database_Type<unsigned int> {
//		Max_W_In_Time_Type(const _type& value) : Common_Database_Type(value) {}
//		Max_W_In_Time_Type(_type&& value) : Common_Database_Type(std::forward<_type>(value)) {}
//	};
//
//	//Groups
//	struct Time_Zone_Type : public Common_Database_Type<unsigned int> {
//		Time_Zone_Type(const _type& value) : Common_Database_Type(value) {}
//		Time_Zone_Type(_type&& value) : Common_Database_Type(std::forward<_type>(value)) {}
//	};
//
//	//Employee
//	struct Surname_Type : public Common_Database_Type<std::string> {
//		Surname_Type(const _type& value) : Common_Database_Type(value) {}
//		Surname_Type(_type&& value) : Common_Database_Type(std::forward<_type>(value)) {}
//	};
//	struct Patronymic_Type : public Common_Database_Type<std::string> {
//		Patronymic_Type(const _type& value) : Common_Database_Type(value) {}
//		Patronymic_Type(_type&& value) : Common_Database_Type(std::forward<_type>(value)) {}
//	};
//	struct Card_Number_Type : public Common_Database_Type<unsigned int> {
//		Card_Number_Type(const _type& value) : Common_Database_Type(value) {}
//		Card_Number_Type(_type&& value) : Common_Database_Type(std::forward<_type>(value)) {}
//	};
//
//	//Groups in controller
//	struct Id_Controller_Type : public Common_Database_Type<unsigned int> {
//		Id_Controller_Type(const _type& value) : Common_Database_Type(value) {}
//		Id_Controller_Type(_type&& value) : Common_Database_Type(std::forward<_type>(value)) {}
//	};
//	struct Position_In_Controller_Type : public Common_Database_Type<unsigned int> {
//		Position_In_Controller_Type(const _type& value) : Common_Database_Type(value) {}
//		Position_In_Controller_Type(_type&& value) : Common_Database_Type(std::forward<_type>(value)) {}
//	};
//
//#define Common_Data_Type_Fields \
//	X(Id_Type, _id)
//
//#define Converters_Data_Types_Fields \
//	/*Done*/X(nSn_Type, _nSn) \
//	/*Done*/X(Type_Name_Type, _type_name) \
//	/*Done*/X(Version_Type, _version) \
//	/*Done*/X(First_Ip_Port_Type, _first_ip_port) \
//	/*Done*/X(Second_Ip_Port_Type, _second_ip_port)
//
//#define Controllers_Data_Types_Fields \
//	/*Done*/X(nSn_Type, _nSn) \
//	/*Done*/X(Type_Name_Type, _type_name) \
//	/*Done*/X(Type_Code_Type, _type_code) \
//	/*Done*/X(Name_Type, _name) \
//	/*Done*/X(Max_Groups_Type, _max_groups) \
//	/*Done*/X(Max_Keys_Type, _max_keys) \
//	/*Done*/X(Max_Events_Type, _max_events) \
//	/*Done*/X(Max_R_In_Time_Type,	_max_r_event_at_time) \
//	/*Done*/X(Max_W_In_Time_Type, _max_w_event_at_time) \
//	/*Done*/X(Id_Converter_Type, _id_converter)
//
//#define Groups_Data_Types_Fields \
//	/*Done*/X(Name_Type, _name) \
//	/*Done*/X(Time_Zone_Type, _time_zone)
//
//#define Employees_Data_Types_Field \
//	/*Done*/X(Name_Type, _name) \
//	/*Done*/X(Surname_Type, _surname) \
//	/*Done*/X(Patronymic_Type, _patronymic) \
//	/*Done*/X(Card_Number_Type, _card_number) \
//	/*Done*/X(Id_Groups_Type, _id_groups)
//
//#define Groups_In_Controllers_Data_Types_Fields \
//	/*Done*/X(Id_Groups_Type, _id_groups) \
//	/*Done*/X(id_Controller_Type, _id_controllers) \
//	/*Done*/X(Id_Converter_Type, _id_converter) \
//	/*Done*/X(Position_In_Controller_Type, _position_in_controller)
//
//	struct Common_Data {
//#define X(type, name) type name;
//		Common_Data_Type_Fields
//#undef X
//
//		Common_Data(const mysqlx::Value& id) : _id(static_cast<unsigned int>(id)){}
//		virtual ~Common_Data() {}
//	};
//
//	struct Converters_Data : Common_Data {
//#define X(type, name) type name;
//		Converters_Data_Types_Fields
//#undef X
//		Converters_Data
//		(
//			mysqlx::Row& row,
//			int&& count
//		) : Common_Data(row.get(count++)),
//		_nSn(static_cast<unsigned int>(row.get(count++))),
//		_type_name(static_cast<mysqlx::string>(row.get(count++))),
//		_version(static_cast<mysqlx::string>(row.get(count++))),
//		_first_ip_port(static_cast<mysqlx::string>(row.get(count++))),
//		_second_ip_port(static_cast<mysqlx::string>(row.get(count++)))
//	{}
//	};
//
//	struct Controllers_Data : Common_Data {
//#define X(type, name) type name;
//		Controllers_Data_Types_Fields
//#undef X
//		Controllers_Data
//		(
//			mysqlx::Row& row,
//			int&& count
//		) : Common_Data(row.get(count++)),
//		_nSn(static_cast<unsigned int>(row.get(count++))),
//		_type_name(static_cast<mysqlx::string>(row.get(count++))),
//		_type_code(static_cast<unsigned int>(row.get(count++))),
//		_name(static_cast<mysqlx::string>(row.get(count++))),
//		_max_groups(static_cast<unsigned int>(row.get(count++))),
//		_max_keys(static_cast<unsigned int>(row.get(count++))),
//		_max_events(static_cast<unsigned int>(row.get(count++))),
//		_max_r_event_at_time(static_cast<unsigned int>(row.get(count++))),
//		_max_w_event_at_time(static_cast<unsigned int>(row.get(count++))),
//		_id_converter(static_cast<unsigned int>(row.get(count++)))
//	{}
//	};
//
//	struct Groupd_Data : Common_Data {
//#define X(type, name) type name;
//		Groups_Data_Types_Fields
//#undef X
//		Groupd_Data
//		(
//			mysqlx::Row& row,
//			int&& count
//		) : Common_Data(row.get(count++)),
//		_name(static_cast<mysqlx::string>(row.get(count++))),
//		_time_zone(static_cast<unsigned int>(row.get(count++)))
//		{}
//	};
//
//	struct Employees_Data : Common_Data {
//#define X(type, name) type name;
//		Employees_Data_Types_Field
//#undef X
//		Employees_Data
//		(
//			mysqlx::Row& row,
//			int&& count
//		) : Common_Data(row.get(count++)),
//		_name(static_cast<mysqlx::string>(row.get(count++))),
//		_surname(static_cast<mysqlx::string>(row.get(count++))),
//		_patronymic(static_cast<mysqlx::string>(row.get(count++))),
//		_card_number(static_cast<unsigned int>(row.get(count++))),
//		_id_groups(static_cast<unsigned int>(row.get(count++)))
//		{}
//	};
//
//	struct Groups_In_Controllers_Data : Common_Data {
//#define X(type, name) type name;
//		Groups_In_Controllers_Data_Types_Fields
//#undef X
//		Groups_In_Controllers_Data
//		(
//			mysqlx::Row& row,
//			int&& count
//		) : Common_Data(row.get(count++)),
//		_id_groups(static_cast<int>(row.get(count++))),
//		_id_controllers(static_cast<int>(row.get(count++))),
//		_id_converter(static_cast<int>(row.get(count++))),
//		_position_in_controller(static_cast<int>(row.get(count++)))
//		{}
//	};
//
//	using Controllers_Data_List = std::vector<Controllers_Data>;
//
//	//struct Converter_Controllers_Data  {
//	//	Converters_Data _converter_data;
//	//	Controllers_Data_List _controllers_data_list;
//
//	//	//Converter_Controllers_Data() {}
//	//};
//
///////// Next old data

////////// Next old data types

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


	struct Mysql_Generic_Type {
#define X(type, name) type name;
		Mysql_Generic_Type_Fields
#undef X

		Mysql_Generic_Type() {};
		Mysql_Generic_Type(mysqlx::Value id) : _id(static_cast<int>(id)){};
		virtual ~Mysql_Generic_Type() {};
	};


	struct  Mysql_Converter_Data_Type : public Mysql_Generic_Type {
#define X(type, name) type name;
		Mysql_Converter_Data_Type_Field
#undef X

		Mysql_Converter_Data_Type() {};
		Mysql_Converter_Data_Type(mysqlx::Row& row,	int&& count)
			: Mysql_Generic_Type(row.get(count++)),
			_nSn(static_cast<int>(row.get(count++))),
			_type_name(static_cast<mysqlx::string>(row.get(count++))),
			_version(static_cast<unsigned int>(row.get(count++))),
			_first_ip_port(static_cast<mysqlx::string>(row.get(count++))),
			_second_ip_port(static_cast<mysqlx::string>(row.get(count++)))
		{}
	};

	struct Mysql_Controller_Data_Type : public Mysql_Generic_Type {
#define X(type, name) type name;
		Mysql_Controller_Data_Type_Fields
#undef X

		Mysql_Controller_Data_Type() {};
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
	};


	struct Mysql_Group_Data_Type : public Mysql_Generic_Type {
#define X(type, name) type name;
		Mysql_Group_Data_Type_Fields
#undef X
			Mysql_Group_Data_Type() {};
		Mysql_Group_Data_Type(mysqlx::Row& row, int&& count)
			: Mysql_Generic_Type(row.get(count++)),
			_name(static_cast<mysqlx::string>(row.get(count++))),
			_time_zone(static_cast<int>(row.get(count++)))
		{}
	};


	struct Mysql_Employee_Data_Type : public Mysql_Generic_Type {
#define X(type, name) type name;
		Mysql_Employee_Data_Type_Fields
#undef X
		Mysql_Employee_Data_Type() {};
		Mysql_Employee_Data_Type(mysqlx::Row& row, int&& count)
			: Mysql_Generic_Type(row.get(count++)),
			_name(static_cast<mysqlx::string>(row.get(count++))),
			_surname(static_cast<mysqlx::string>(row.get(count++))),
			_patronymic(static_cast<mysqlx::string>(row.get(count++))),
			_card_number(static_cast<int>(row.get(count++)))
		{}
	};


	struct Mysql_Group_In_Controller_Data_Type : public Mysql_Generic_Type {
#define X(type, name) type name;
		Mysql_Group_In_Controller_Data_Type_Fields
#undef X
		Mysql_Group_In_Controller_Data_Type() {};
		Mysql_Group_In_Controller_Data_Type(mysqlx::Row& row, int&& count)
			: Mysql_Generic_Type(row.get(count++)),
			_id_groups(static_cast<int>(row.get(count++))),
			_id_controllers(static_cast<int>(row.get(count++))),
			_id_converter(static_cast<int>(row.get(count++))),
			_position_in_controller(static_cast<int>(row.get(count++)))
		{}
	};

	static const std::string TablesNames[] = {
		"converters",
		"controllers",
		"groups",
		"employees",
		"groups_in_controllers"
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

		Basic_Info(Common_Database_Types::Mysql_Converter_Data_Type mysql_converter_data, const Common_Database_Types::Controllers_Data_List& mysql_controllers_data_list)
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
	};

	// Basic usage
	using Basic_Info_Ref = std::shared_ptr<Basic_Info>;
	using Basic_Info_List = std::vector<Basic_Info>;
	using Basic_Info_List_Ref = std::shared_ptr<Basic_Info_List>;
	using Basic_Info_Ref_List = std::vector<Basic_Info_Ref>;
	using Basic_Info_Ref_List_Ref = std::shared_ptr<Basic_Info_Ref_List>;
}
#endif