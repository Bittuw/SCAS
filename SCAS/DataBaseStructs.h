#pragma once


#define Data_type_fields \
	X(unsigned int, _id)

#define Converters_data_type_fields \
	X(unsigned int, _nSn) \
	X(std::string, _type_name) \
	X(std::string, _version) \
	X(std::string, _first_ip_port) \
	X(std::string, _second_ip_port)

#define Controllers_data_type_fields \
	X(unsigned int, _nSn) \
	X(std::string, _type_name) \
	X(unsigned int, _type_code) \
	X(std::string, _name) \
	X(unsigned int, _max_groups) \
	X(unsigned int, _max_keys) \
	X(unsigned int, _max_events) \
	X(unsigned int,	_max_r_event_at_time) \
	X(unsigned int, _max_w_event_at_time) \
	X(unsigned int, _id_converter)

#define Groups_data_type_fields \
	X(std::string, _name) \
	X(unsigned int, _time_zone)

#define Employees_data_type_fields \
	X(std::string, _name) \
	X(std::string, _surname) \
	X(std::string, _patronymic) \
	X(unsigned int, _card_number) \
	X(unsigned int, _id_groups)

#define GroupsInControllers_data_type_fields \
	X(unsigned int, _id_groups) \
	X(unsigned int, _id_controllers) \
	X(unsigned int, _id_converter) \
	X(unsigned int, _position_in_controller)


struct Data_type {
#define X(type, name) type name;
	Data_type_fields
#undef X
	Data_type() {};
	Data_type(mysqlx::Value id) : _id(static_cast<int>(id)) {};
	virtual ~Data_type() {};
	virtual mysqlx::Table& writeToRow
	(
		mysqlx::Table&,
		int&&
	);
	//virtual std::vector<Data_type>getList();
};


struct  Converters_data_type : public Data_type {
#define X(type, name) type name;
	Converters_data_type_fields
#undef X

	Converters_data_type() {};
	Converters_data_type
	(
		mysqlx::Row& row,
		int&& count
	)	: Data_type(row.get(count++)),
		_nSn(static_cast<int>(row.get(count++))),
		_type_name(static_cast<mysqlx::string>(row.get(count++))),
		_version(static_cast<mysqlx::string>(row.get(count++))),
		_first_ip_port(static_cast<mysqlx::string>(row.get(count++))),
		_second_ip_port(static_cast<mysqlx::string>(row.get(count++)))
	{}

	mysqlx::Table& writeToRow(mysqlx::Table& table, int&& count) override {
		table.insert("nSn", "type_name", "version", "first_ip:port", "second_ip:port")
			.values(_nSn, _type_name, _version, _first_ip_port, _second_ip_port);
		return table;
	}
};

struct Controllers_data_type : public Data_type {
#define X(type, name) type name;
	Controllers_data_type_fields
#undef X

	Controllers_data_type() {};
	Controllers_data_type
	(
		mysqlx::Row& row,
		int&& count
	) : Data_type(row.get(count++)),
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


struct Groups_data_type : public Data_type {
#define X(type, name) type name;
	Groups_data_type_fields
#undef X
	Groups_data_type() {};
	Groups_data_type
	(
		mysqlx::Row& row,
		int&& count
	) : Data_type(row.get(count++)),
		_name(static_cast<mysqlx::string>(row.get(count++))),
		_time_zone(static_cast<int>(row.get(count++)))
	{}
};


struct Employees_data_type : public Data_type {
#define X(type, name) type name;
	Employees_data_type_fields
#undef X
	Employees_data_type() {};
	Employees_data_type
	(
		mysqlx::Row& row,
		int&& count
	) : Data_type(row.get(count++)),
		_name(static_cast<mysqlx::string>(row.get(count++))),
		_surname(static_cast<mysqlx::string>(row.get(count++))),
		_patronymic(static_cast<mysqlx::string>(row.get(count++))),
		_card_number(static_cast<int>(row.get(count++)))
	{}
};


struct GroupsInControllers_data_type : public Data_type {
#define X(type, name) type name;
	GroupsInControllers_data_type_fields
#undef X
	GroupsInControllers_data_type() {};
	GroupsInControllers_data_type
	(
		mysqlx::Row& row,
		int&& count
	) : Data_type(row.get(count++)),
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

using Converters_data_list = std::vector<Converters_data_type>;
using Controllers_data_list = std::vector<Controllers_data_type>;
using Groups_data_list = std::vector<Groups_data_type>;
using Employees_data_list = std::vector<Employees_data_type>;
using GroupsInControllers_data_list = std::vector<GroupsInControllers_data_type>;
//using Type_list = std::vector<std::shared_ptr<Data_type>>;
//using Types_list = std::vector<Data_type>;
