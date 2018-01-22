#pragma once

class DataBase
{
public:
	
	template <typename...T>
	DataBase(T...options) : session(mysqlx::SessionSettings(options...)) , database(session.getDefaultSchema()){
		//database = session.getSchema("test");
		auto table = database.getTable("test_collection");
		auto select = table.select("*").where(mysqlx::expr("int > 1")).execute();
		auto list = select.fetchAll();
		for each (auto var in list)
		{
			std::cout << var.get(1) << std::endl;
		}
	};
	~DataBase();

	void disconnect();
	mysqlx::Table getTable(const mysqlx::string&);

private:
	mysqlx::Session session;
	mysqlx::Schema database;

};

class ConnectionLayer {
public:

private:

};