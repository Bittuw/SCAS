#pragma once

#include "DataStructs.h"

// Little Interface for MySQL Database
class DataBase 
{
public:
	template <typename...T>
	explicit DataBase(T...options) 
		: 
		_session(mysqlx::SessionSettings(options...)), 
		_database(_session.getDefaultSchema()), 
		_converters_list(std::make_shared<Common_Database_Types::Converters_Data_List>()),
		_controllers_list(std::make_shared<Common_Database_Types::Controllers_Data_List>()),
		_groups_list(std::make_shared<Common_Database_Types::Groups_Data_List>()),
		_employees_list(std::make_shared<Common_Database_Types::Employees_Data_List>()),
		_groupsInControllers_list(std::make_shared<Common_Database_Types::Groups_In_Controllers_Data_List>())
	{
		Log(MessageTypes::DEBUG) << LoggerFormat::format(
			"Open DataBase connection: \n\
			IP: % \n\
			PORT: % \n\
			USER: % \n\
			PASSWORD: % \n\
			DEFUALT SHEMA: %", options...);
		downloadTables();
	};
	~DataBase();

	void* operator new(size_t) = delete;
	void* operator new[](size_t) = delete;
	void operator delete(void*) = delete;
	void operator delete[](void*) = delete;

	DataBase(DataBase&) = delete;
	DataBase& operator =(const DataBase&) = delete;

	DataBase(DataBase&&) = delete;
	DataBase& operator=(DataBase&&) = delete;

	std::shared_ptr<mysqlx::Table> get_Table(std::string&&); // For execute
	std::shared_ptr<mysqlx::Table> get_table(const std::string&); // For execute 

	void downloadTables(); // Can do exception

	std::shared_ptr<Common_Database_Types::Converters_Data_List> _converters_list;
	std::shared_ptr<Common_Database_Types::Controllers_Data_List> _controllers_list;
	std::shared_ptr<Common_Database_Types::Groups_Data_List> _groups_list;
	std::shared_ptr<Common_Database_Types::Employees_Data_List> _employees_list;
	std::shared_ptr<Common_Database_Types::Groups_In_Controllers_Data_List> _groupsInControllers_list;

private:
	mysqlx::Session _session;
	mysqlx::Schema _database;
};

class DataBaseLayer {
public:

	DataBaseLayer() 
		: database("localhost", 33060, "sslroot", "elitaass18A", "test_skud") ,
		_basic_info_ref_list_ref(std::make_shared<Common_DataBaseLayer_Types::Basic_Info_Ref_List>())
	{
		/*auto copy_converters_list = *database._converters_list;
		auto copy_controllers_list = *database._controllers_list;
		auto copy_groups_list = *database._groups_list;
		auto copy_employees_list = *database._employees_list;
		auto copy_groupsInControllers_list = *database._groupsInControllers_list;*/
		make_Basic_Info_List();
	}

	Common_DataBaseLayer_Types::Basic_Info_Ref_List_Ref make_Basic_Info_List();


private:
	Common_DataBaseLayer_Types::Basic_Info_Ref_List_Ref _basic_info_ref_list_ref;
	//void CreateSerializationThread(Common_DataBaseLayer_Types::Basic_Info_Ref_List_Ref);

	//void make_copies();
	DataBase database;

};

//class DataBasePresenter {
//
//};
//
//class DataBaseThreading {
//
//};