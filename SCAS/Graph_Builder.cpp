#include "stdafx.h"
#include "Graph_Builder.h"
#include "Util.h"

///
/// Одновременное построение и связывание
/// т.е. построение(связывание) слева, справа и связывание
///

Graph_Builder::Graph_Builder()
{}


Graph_Builder::~Graph_Builder()
{
}

void Graph_Builder::make_Graph_From_Mysql(
	const Mysql_Types::Mysql_Converters_Data_List& mysql_converters_data_list,
	const Mysql_Types::Mysql_Controllers_Data_List& mysql_controllers_data_list,
	const Mysql_Types::Mysql_Groups_Data_List& mysql_groups_data_list,
	const Mysql_Types::Mysql_Employees_Data_List& mysql_employees_data_list,
	const Mysql_Types::Mysql_Groups_In_Controllers_Data_List& mysql_groups_in_controllers_data_list
) 
{
	right(mysql_groups_data_list, mysql_employees_data_list);
	left(mysql_converters_data_list, mysql_controllers_data_list);
	binding(mysql_groups_in_controllers_data_list);
}

void Graph_Builder::right
(
	const Mysql_Types::Mysql_Groups_Data_List& mysql_groups_data_list,
	const Mysql_Types::Mysql_Employees_Data_List& mysql_employees_data_list
)
{
	for (auto& mysql_group_info : mysql_groups_data_list)
	{
		_groups_info_list.emplace_back(new Graph_Types::Group_Info(mysql_group_info));
		_groups_list.emplace_back(new Graph_Types::Graph_Group(_groups_info_list.back()));

		Mysql_Types::Mysql_Employees_Data_List::const_iterator result;
		auto start_from = mysql_employees_data_list.cbegin();

		while (
				(result = std::find_if(
						start_from,
						mysql_employees_data_list.cend(),
						[mysql_group_info](const Mysql_Types::Mysql_Employee_Data_Type& mysql_user_info)
						{
							return mysql_group_info._id == mysql_user_info._id_groups;
						}
					)
				) != mysql_employees_data_list.cend()
			)
		{
			start_from = result + 1;
			_users_info_list.emplace_back(new Graph_Types::User_Info(*result));
			_users_list.emplace_back(new Graph_Types::Graph_User(_users_info_list.back(), _groups_list.back()));
			_groups_list.back()->_users_list.push_back(_users_list.back());
		}
	}
}


void Graph_Builder::left
(
	const Mysql_Types::Mysql_Converters_Data_List& mysql_converters_data_list,
	const Mysql_Types::Mysql_Controllers_Data_List& mysql_controllers_data_list
) 
{
	for (auto& mysql_converter_info : mysql_converters_data_list)
	{
		_converters_info_list.emplace_back(new Graph_Types::Converter_Info(mysql_converter_info));
		_converters_list.emplace_back(new Graph_Types::Graph_Converter(_converters_info_list.back()));

		Mysql_Types::Mysql_Controllers_Data_List::const_iterator result;
		auto start_from = mysql_controllers_data_list.cbegin();


		while (
				(result = std::find_if(
						start_from, 
						mysql_controllers_data_list.cend(),
						[mysql_converter_info](const Mysql_Types::Mysql_Controller_Data_Type& mysql_controller_info)
						{
							return mysql_converter_info._id == mysql_controller_info._id_converter;
						}
					)
				) != mysql_controllers_data_list.cend()
			)
		{
			start_from = result + 1;
			_controllers_info_list.emplace_back(new Graph_Types::Controller_Info(*result));
			_controllers_list.emplace_back(new Graph_Types::Graph_Controller(_controllers_info_list.back(), _converters_list.back()));
			_converters_list.back()->_controllers_list.push_back(_controllers_list.back());
		}
	}
}


void Graph_Builder::binding
(
	const Mysql_Types::Mysql_Groups_In_Controllers_Data_List& mysql_groups_in_controllers_data_list
) 
{
	for (auto& group_in_controller_info : mysql_groups_in_controllers_data_list)
	{
		auto controller = std::find_if(
			_controllers_list.cbegin(), 
			_controllers_list.cend(), 
			[group_in_controller_info](const Graph_Types::Graph_Controller_sRef& controller)
			{
				return group_in_controller_info._id_controllers == controller->_controller_info_ref->_id;
			}
		);
		auto group = std::find_if(
			_groups_list.cbegin(), 
			_groups_list.cend(), 
			[group_in_controller_info](const Graph_Types::Graph_Group_sRef& group)
			{
				return group_in_controller_info._id_groups == group->_group_ref->_id;
			}
		);

		if (controller != _controllers_list.cend() && group != _groups_list.cend())
		{
			(*controller)->_groups_list.push_back(*group);
			(*group)->_controllers_list.push_back(*controller);
		}
		else {
			throw Programm_Exceptions("Not valid bond!");
		}
	}
}