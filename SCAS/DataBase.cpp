#include "stdafx.h"
#include "DataBase.h"
//
//template <typename ...options>
//DataBase::DataBase()
//{
//
//}


DataBase::~DataBase()
{
	disconnect();
}

void DataBase::disconnect() {
	session.close();
	Log(TRACE) << "close DataBase connection";
}