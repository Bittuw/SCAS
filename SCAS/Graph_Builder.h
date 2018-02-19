#pragma once

#ifndef GRAPH_BULDER
#define GRAPH_BULDER

#include "Mysql_Types.h"
#include "Graph_Types.h"

class Graph_Builder final // TODO на основе данных Mysql или на основе данных Search_Device
{
public:
	Graph_Builder();
	~Graph_Builder();

	// From mysql (all tables)
	void make_Graph_From_Mysql(
		const Mysql_Types::Mysql_Converters_Data_List& mysql_converters_data_list,
		const Mysql_Types::Mysql_Controllers_Data_List& mysql_controllers_data_list,
		const Mysql_Types::Mysql_Groups_Data_List& mysql_groups_data_list,
		const Mysql_Types::Mysql_Employees_Data_List& mysql_employees_data_list,
		const Mysql_Types::Mysql_Groups_In_Controllers_Data_List& mysql_groups_in_controllers_data_list
	); 
	
private:

	/// Привести к одному виду
	/// Left construct
	/// Right construct

	template <typename From, typename To>
	void transform(const From& from, To& to) {
		std::transform(
			from.cbegin(),
			from.cend(),
			std::back_inserter(to),
			[](const From::value_type& element)
			{
				return std::make_shared<To::value_type>(element);
			}
		)
	}

	/*template <typename >
	void build_one_many() 
	{

	}*/

	void right(
		const Mysql_Types::Mysql_Groups_Data_List& mysql_groups_data_list,
		const Mysql_Types::Mysql_Employees_Data_List& mysql_employees_data_list
	); // Groups and users
	void left(
		const Mysql_Types::Mysql_Converters_Data_List& mysql_converters_data_list,
		const Mysql_Types::Mysql_Controllers_Data_List& mysql_controllers_data_list
	); // Converters and controllers (Mysql or Zguard)
	void binding(
		const Mysql_Types::Mysql_Groups_In_Controllers_Data_List& mysql_groups_in_controllers_data_list
	); // Bind right and left

	Graph_Types::Converters_sRefs _converters_info_list; // Информация о конверторе Left
	Graph_Types::Controllers_sRefs _controllers_info_list; // Информация о контроллере left
	Graph_Types::Users_sRefs _users_info_list; // Информация о пользователе right
	Graph_Types::Groups_sRefs _groups_info_list; // Информация о группе right
	Graph_Types::Groups_In_Controllers_sRefs _groups_in_controllers_list; // Информация о связи группа <-> контроллер binding

	Graph_Types::Graph_Converters_sRefs _converters_list; // Элемент графа left
	Graph_Types::Graph_Controlles_sRefs _controllers_list; // Элемент графа left 
	Graph_Types::Graph_Users_sRefs _users_list; // Элемент графа right
	Graph_Types::Graph_Groups_sRefs _groups_list; // Элемент графа right
};
#endif
