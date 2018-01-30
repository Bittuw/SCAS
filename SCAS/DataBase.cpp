#include "stdafx.h"
#include "DataBase.h"


DataBase::~DataBase()
{
	_session.close();
	Log(MessageTypes::DEBUG) << "Close DataBase connection!";

}

void DataBase::downloadTables() { // TODO just do it like template

	for (size_t i = 0; i < _countof(Common_Database_Types::TablesNames); i++) {
		auto table = _database.getTable(Common_Database_Types::TablesNames[i], false);
		
		switch (i)
		{ 
		case 0:
			for (auto row : table.select("*").execute()) {
				_converters_list->push_back(Common_Database_Types::Mysql_Converter_Data_Type(row, 0));
			}
			break;
		case 1:
			for (auto row : table.select("*").execute()) {
				_controllers_list->push_back(Common_Database_Types::Mysql_Controller_Data_Type(row, 0));
			}
			break;
		case 2:
			for (auto row : table.select("*").execute()) {
				_groups_list->push_back(Common_Database_Types::Mysql_Group_Data_Type(row, 0));
			}
			break;
		case 3:
			for (auto row : table.select("*").execute()) {
				_employees_list->push_back(Common_Database_Types::Mysql_Employee_Data_Type(row, 0));
			}
			break;
		case 4:
			for (auto row : table.select("*").execute()) {
				_groupsInControllers_list->push_back(Common_Database_Types::Mysql_Group_In_Controller_Data_Type(row, 0));
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

Common_DataBaseLayer_Types::Basic_Info_Ref_List_Ref DataBaseLayer::make_Basic_Info_List() {
	for (auto _converter_data : *database._converters_list) {
		/*Common_DataBaseLayer_Types::Basic_Info bas1(_converter_data);
		Common_DataBaseLayer_Types::Basic_Info bas2(*database._controllers_list);
		std::make_shared<Common_DataBaseLayer_Types::Basic_Info>(_converter_data, *database._controllers_list);*/
		_basic_info_ref_list_ref->emplace_back(std::make_shared<Common_DataBaseLayer_Types::Basic_Info>(_converter_data, *database._controllers_list));
	}

	return nullptr;
}