#pragma once

///
/// File for pods type. Save them in binary files 
/// and only types from mysql_devapi
///

#ifndef  PODS

#define PODS

#define Mysql_Generic_Type_Fields \
	/*Done*/X(unsigned int, _id)

#define POD_Converter_Data_Type_Field \
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

namespace Pods {
	struct Mysql_POD_Converter_Data_Type {
#define X(type, name) type name;
		Mysql_Generic_Type_Fields
			POD_Converter_Data_Type_Field
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
}

#undef Mysql_Generic_Type_Fields
#undef POD_Converter_Data_Type_Field
#undef Mysql_POD_Controller_Data_Type_Fields
#undef Mysql_POD_Group_Data_Type_Fields
#undef Mysql_POD_Employee_Data_Type_Fields
#undef Mysql_POD_Group_In_Controller_Data_Type_Fields

#endif // ! PODS
