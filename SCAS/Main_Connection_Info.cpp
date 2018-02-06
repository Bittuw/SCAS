#include "stdafx.h"
#include "Main_Connection_Info.h"

Main_Connection_Basic_Info_Types::Main_Connection_basic_Info_List_uRef Main_Connection_Basic_Info_Types::FromMysqlToMain(const Mysql_Basic_Info_Types::Mysql_Basic_Info_List_Ref& mysql_basic_info_list_ref) {
	auto main_connection_basic_info_list_uref = std::make_unique<Main_Connection_Basic_Info_List>();

	std::transform(
		mysql_basic_info_list_ref->cbegin(),
		mysql_basic_info_list_ref->cend(),
		std::back_inserter(*main_connection_basic_info_list_uref),
		[](const Mysql_Basic_Info& mysql_basic_info) -> decltype(auto)
		{
			return Main_Connection_Basic_Info_Types(mysql_basic_info);
		}
	);

	return std::move(main_connection_basic_info_list_uref);
}