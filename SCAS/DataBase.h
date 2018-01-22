#pragma once

#include "DataStructs.h"

class DataBase
{
public:
	
	template <typename...T>
	DataBase(T...options) : session(mysqlx::SessionSettings(options...)) , database(session.getDefaultSchema()){
		downloadTables();
	};
	~DataBase();

	void disconnect();
	void downloadTables();

private:
	mysqlx::Session session;
	mysqlx::Schema database;

	Converters_data_list _converters_list;
	Controllers_data_list _controllers_list;
	Groups_data_list _groups_list;
	Employees_data_list _employees_list;
	GroupsInControllers_data_list groupsInControllers_list;

	/*template <typename ...Targs>
	decltype(auto) getEnumRow(const mysqlx::Row& row, const std::string&) {

	}*/

	//decltype(auto) getEnumRow(mysqlx::Row&, const std::string&);
};

class ConnectionLayer {
public:

private:

};