#include "stdafx.h"
#include "DataBase.h"


DataBase::~DataBase()
{
	disconnect();
}

void DataBase::disconnect() {
	session.close();
	Log(TRACE) << "close DataBase connection";
}

void DataBase::downloadTables() {

	auto table = database.getTable(TablesName[0], false);
	auto select = table.select("*").execute();

	for (auto row : select) {
		_converters_list.push_back(Converters_data_type(row, 0));
	}
}

//decltype(auto) DataBase::getEnumRow(mysqlx::Row& row, const std::string& name) {
//	int col = 0;
//	auto tup = std::make_tuple(3, "g");
//	auto t = static_cast<std::string>(row.get(0));
//	auto r = t.getType();
//	Groups_data_type temp = { row.get(col++) };
//	//return getEnumRow<>(row, name);
//}
