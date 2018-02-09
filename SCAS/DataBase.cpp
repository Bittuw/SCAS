#include "stdafx.h"
#include "DataBase.h"


DataBase::~DataBase()
{
	_session.close();
	Log(MessageTypes::DEBUG) << "Close DataBase connection!";

}

void DataBase::downloadTables() { // TODO just do it like template

	for (size_t i = 0; i < _countof(Mysql_Types::TablesNames); i++) {
		auto table = _database.getTable(Mysql_Types::TablesNames[i], false);
		
		switch (i)
		{ 
		case 0:
			for (auto row : table.select("*").execute()) {
				_converters_list->emplace_back(row, 0);
			}
			break;
		case 1:
			for (auto row : table.select("*").execute()) {
				_controllers_list->emplace_back(row, 0);
			}
			break;
		case 2:
			for (auto row : table.select("*").execute()) {
				_groups_list->emplace_back(row, 0);
			}
			break;
		case 3:
			for (auto row : table.select("*").execute()) {
				_employees_list->emplace_back(row, 0);
			}
			break;
		case 4:
			for (auto row : table.select("*").execute()) {
				_groups_In_Controllers_list->emplace_back(row, 0);
			}
			break;
		default:
			throw  std::logic_error("Unknown database name");
			break;
		}
	}
}

std::shared_ptr<mysqlx::Table> DataBase::get_Table(std::string&& table_name) {
	return std::make_shared<mysqlx::Table>(_database.getTable(std::move(table_name)));
}

std::shared_ptr<mysqlx::Table> DataBase::get_table(const std::string& table_name)
{
	return std::make_shared<mysqlx::Table>(_database.getTable(table_name));
}

Mysql_Basic_Info_Types::Mysql_Basic_Info_List_Ref DataBaseLayer::make_Mysql_Basic_Info_List() {
	for (auto& _converter_data : *database._converters_list) {
		_basic_info_list_ref->emplace_back(_converter_data, *database._controllers_list);
	}
	return _basic_info_list_ref;
}

Mysql_Basic_Info_Types::Mysql_Users_Basic_Info_List_ref DataBaseLayer::make_Mysql_Users_basic_Info_List() {
	for (auto& _controller_data : *database._controllers_list) {
		_users_basic_info_list_ref->emplace_back(_controller_data, *database._groups_In_Controllers_list, *database._groups_list, *database._employees_list);
	}
	return _users_basic_info_list_ref;
}

std::string* Mysql_Types::Mysql_Converter_Data_Type::_table_name = const_cast<std::string*>(Mysql_Types::TablesNames);
std::string* Mysql_Types::Mysql_Controller_Data_Type::_table_name = const_cast<std::string*>(Mysql_Types::TablesNames + 1);
std::string* Mysql_Types::Mysql_Group_Data_Type::_table_name = const_cast<std::string*>(Mysql_Types::TablesNames + 2);
std::string* Mysql_Types::Mysql_Employee_Data_Type::_table_name = const_cast<std::string*>(Mysql_Types::TablesNames + 3);
std::string* Mysql_Types::Mysql_Group_In_Controller_Data_Type::_table_name = const_cast<std::string*>(Mysql_Types::TablesNames + 4);
