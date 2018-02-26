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
	
	template <typename T>
	static T& filter(T& list) {
		auto first = std::unique(
			list.cbegin(),
			list.cend(),
			[](const T::value_type& a, const T::value_type& b) 
			{
				return a._id == b._id;
			}
		);

		list.erase(first, list.cend());
	}

	void add_User(
		const Mysql_Types::Mysql_Employees_Data_List& mysql_employees_data_list
	);

	void add_Group(
		const Mysql_Types::Mysql_Groups_Data_List& mysql_groups_data_list
	);
	void add_Group_In_Controller(
		const Mysql_Types::Mysql_Groups_In_Controllers_Data_List& mysql_groups_in_controllers_data_list
	);

	Graph_Types::Graph_Users_sRefs delete_User(
		const Mysql_Types::Mysql_Employees_Data_List& mysql_employees_data_list
	);
	Graph_Types::Graph_Groups_sRefs delete_Group(
		const Mysql_Types::Mysql_Groups_Data_List& mysql_groups_data_list
	);

	//void commit_change();

private:
		
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
	); // Bind right and left part of graph

	//void bind_one_pair(const Graph_Types::Group_In_Controller_sRef& group_in_controller);

	/*void delete_commit();
	void add_commit();
	void update_commit();

	template <typename L, typename...Largs>
	void find_affected_converters(const L& list, Largs...lists) {

	}*/

	Graph_Types::Converters_sRefs _converters_info_list; // »нформаци€ о конверторе Left
	Graph_Types::Controllers_sRefs _controllers_info_list; // »нформаци€ о контроллере left
	Graph_Types::Users_sRefs _users_info_list; // »нформаци€ о пользователе right
	Graph_Types::Groups_sRefs _groups_info_list; // »нформаци€ о группе right
	//Graph_Types::Groups_In_Controllers_sRefs _groups_in_controllers_list; // »нформаци€ о св€зи группа <-> контроллер binding возможно удалить

	Graph_Types::Graph_Converters_sRefs _converters_list; // Ёлемент графа (конверторы) left
	Graph_Types::Graph_Controlles_sRefs _controllers_list; // Ёлемент графа (контроллеры) left 
	Graph_Types::Graph_Users_sRefs _users_list; // Ёлемент графа (пользователи) right
	Graph_Types::Graph_Groups_sRefs _groups_list; // Ёлемент графа (группы) right

	Graph_Types::Graph_Users_sRefs commit_users_list; // ѕользователи дл€ добавлени€
	Graph_Types::Graph_Groups_sRefs commit_groups_list; // √руппы дл€ добавлени€
	//Graph_Types::Groups_In_Controllers_sRefs commit_groups_in_controllers_list; // —в€зи группа-контроллер дл€ добавлени€

};
#endif
