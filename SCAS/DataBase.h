#pragma once

#include "DataStructs.h"

class DataBase
{
public:
	
	template <typename...T>
	DataBase(T...options) : session(mysqlx::SessionSettings(options...)), database(session.getDefaultSchema()) 
	{ 
		downloadTables(); 
	};
	~DataBase();

	void disconnect();
	void downloadTables();
	void pushTables();

	void removeFrom(std::string&);

	Converters_data_list _converters_list;
	Controllers_data_list _controllers_list;
	Groups_data_list _groups_list;
	Employees_data_list _employees_list;
	GroupsInControllers_data_list _groupsInControllers_list;

private:
	mysqlx::Session session;
	mysqlx::Schema database;

	mysqlx::RowResult _converters_select;
	mysqlx::RowResult _controllers_select;
	mysqlx::RowResult _groups_select;
	mysqlx::RowResult _employees_select;
	mysqlx::RowResult _groupsInControllers_select;
};

class ConnectionLayer {
public:
	ConnectionLayer() : database("localhost", 33060, "sslroot", "elitaass18A", "test_skud"){}

	
	void deleteRow() {
		database.removeFrom(std::string("converters"));
	}

private:
	DataBase database;
};