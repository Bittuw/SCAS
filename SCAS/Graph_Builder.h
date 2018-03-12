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
			list.begin(),
			list.end(),
			[](const T::value_type& a, const T::value_type& b) 
			{
				Log(MessageTypes::WARNING) << LoggerFormat::format("Delete dublicate from table: '%'", *a._table_name);
				return (a._id) == (b._id);
			}
		);
		list.erase(first, list.cend());
		return list;
	}

	template <typename T, typename R> 
	static T& filter_by(T& list, const R& list_by) {
		filter(list);
		std::for_each(list_by.cbegin(), list_by.cend(),
			[&list](const R::value_type& element) 
			{
				auto result = std::find_if(list.cbegin(), list.cend(),
					[&element](const T::value_type& new_element)
					{
						return (new_element._id == element->_data->_pk.pk);
					}
				);
				if(result != list.cend()) list.erase(result);
			}
		);
		return list;
	}

	void add_Users(
		const Mysql_Types::Mysql_Employees_Data_List& mysql_employees_data_list
	);
	void delete_Users(
		const Mysql_Types::Mysql_Employees_Data_List& mysql_employees_data_list
	);
	void update_Users(
		const Mysql_Types::Mysql_Employees_Data_List& mysql_employees_data_list
	);
	void add_Groups(
		const Mysql_Types::Mysql_Groups_Data_List& mysql_groups_data_list,
		const Mysql_Types::Mysql_Groups_In_Controllers_Data_List& mysql_groups_in_cintrollers_data_list
	);
	/*void add_Group_In_Controller(
		const Mysql_Types::Mysql_Groups_In_Controllers_Data_List& mysql_groups_in_controllers_data_list
	);*/
	/*Graph_Types::Graph_Groups_sRefs delete_Group(
		const Mysql_Types::Mysql_Groups_Data_List& mysql_groups_data_list
	);*/

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

	inline void add_to_notify_set(Graph_Types::Graph_Converters_Set_Ref&);
	inline void add_User(Mysql_Types::Mysql_Employee_Data_Type&);
	inline void add_Group(Mysql_Types::Mysql_Group_Data_Type&, const Mysql_Types::Mysql_Groups_In_Controllers_Data_List&);
	//inline static void add_Group(Mysql_Types::Mysql_Group_Data_Type&);
	//void commit()

	// С уничтожение объекта
	template <typename Parent_Pair_First, typename Parent_Pair_Second, typename Target_Element>
	inline void cancel(std::pair<Parent_Pair_First, Parent_Pair_Second>& parent_element, Target_Element& child_element) {
		if (parent_element.first.cend() != parent_element.second)
			parent_element.first.erase(parent_element.second);
		if (child_element != nullptr)
			child_element.reset();
	}
	template <typename Pair_First, typename Pair_Second, typename Target_Element>
	inline void cancel(std::vector<std::pair<Pair_First, Pair_Second>, std::allocator<std::pair<Pair_First, Pair_Second>>>& parents_list_pair, Target_Element& child_element) {
		std::for_each(parents_list_pair.begin(), parents_list_pair.end(), 
			[](auto& parent_pair) 
			{
				if (parent_pair.first.cend() != parent_pair.second)
					parent_pair.first.erase(parent_pair.second);
			}
		);
		if (child_element != nullptr)
			child_element.reset();
	}

	Graph_Types::Converters_sRefs _converters_info_list; // Информация о конверторе Left
	Graph_Types::Controllers_sRefs _controllers_info_list; // Информация о контроллере left
	Graph_Types::Users_sRefs _users_info_list; // Информация о пользователе right
	Graph_Types::Groups_sRefs _groups_info_list; // Информация о группе right
	//Graph_Types::Groups_In_Controllers_sRefs _groups_in_controllers_list; // Информация о связи группа <-> контроллер binding возможно удалить

	Graph_Types::Graph_Converters_sRefs _converters_list; // Элемент графа (конверторы) left
	Graph_Types::Graph_Controlles_sRefs _controllers_list; // Элемент графа (контроллеры) left 
	Graph_Types::Graph_Users_sRefs _users_list; // Элемент графа (пользователи) right
	Graph_Types::Graph_Groups_sRefs _groups_list; // Элемент графа (группы) right

	Graph_Types::Graph_Converters_Set_Ref _converters_set; // Уведомляемые конверторы

	//Graph_Types::Graph_Users_sRefs _temp_users_list; // Пользователи для добавления
	//Graph_Types::Graph_Groups_sRefs commit_groups_list; // Группы для добавления
	//Graph_Types::Groups_In_Controllers_sRefs commit_groups_in_controllers_list; // Связи группа-контроллер для добавления

};
#endif
