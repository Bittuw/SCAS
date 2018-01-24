#include "stdafx.h"
#include "DataBase.h"
#include <tuple>
#include "LoggerFormat.hpp"

DataBase::~DataBase()
{
	disconnect();
}

void DataBase::disconnect() {
	session.close();
	Log(TRACE) << "close DataBase connection!";
}

void DataBase::downloadTables() {

	for (size_t i = 0; i < _countof(TablesNames); i++) {
		auto table = database.getTable(TablesNames[i], false);

		switch (i)
		{
		case 0:
			_converters_select = table.select("*").execute();
			for (auto row : _converters_select) {
				_converters_list.push_back(Converters_data_type(row,0));
			}
			break;
		case 1:
			_controllers_select = table.select("*").execute();
			for (auto row : _controllers_select) {
				_controllers_list.push_back(Controllers_data_type(row, 0));
			}
			break;
		case 2:
			_groups_select = table.select("*").execute();
			for (auto row : _groups_select) {
				_groups_list.push_back(Groups_data_type(row, 0));
			}
			break;
		case 3:
			_employees_select = table.select("*").execute();
			for (auto row : _employees_select) {
				_employees_list.push_back(Employees_data_type(row, 0));
			}
			break;
		case 4:
			_groupsInControllers_select = table.select("*").execute();
			for (auto row : _groupsInControllers_select) {
				_groupsInControllers_list.push_back(GroupsInControllers_data_type(row, 0));
			}
			break;
		default:
			break;
		}
	}
}

mysqlx::Table& DataBase::getTable(std::string& tableName) {
	return database.getTable(tableName);
}

void DataBase::removeFrom(std::string& tableName) {
	try {
		auto table = database.getTable(tableName, false);
		table.remove().where(mysqlx::expr("id_converters = 1")).execute();
		table.insert();
	}
	catch (std::exception& error) {
		Log(TRACE) << error.what();
	}
}

void ConnectionLayer::loadData(std::vector<AvailableConnection>& data) {
	for(auto converter : data) {
		auto table = 
	}
}