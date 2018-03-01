#include "stdafx.h"
#include "Graph_Builder.h"
#include "Util.h"

///
/// ќдновременное построение и св€зывание
/// т.е. построение(св€зывание) слева, справа и св€зывание
///

Graph_Builder::Graph_Builder()
{}


Graph_Builder::~Graph_Builder()
{}

void Graph_Builder::make_Graph_From_Mysql(
	const Mysql_Types::Mysql_Converters_Data_List& mysql_converters_data_list,
	const Mysql_Types::Mysql_Controllers_Data_List& mysql_controllers_data_list,
	const Mysql_Types::Mysql_Groups_Data_List& mysql_groups_data_list,
	const Mysql_Types::Mysql_Employees_Data_List& mysql_employees_data_list,
	const Mysql_Types::Mysql_Groups_In_Controllers_Data_List& mysql_groups_in_controllers_data_list
) 
{
	auto copy_converters = mysql_converters_data_list;
	auto copy_controllers = mysql_controllers_data_list;
	auto copy_groups = mysql_groups_data_list;
	auto copy_users = mysql_employees_data_list;
	auto copy_groups_in_controllers = mysql_groups_in_controllers_data_list;

	right(filter(copy_groups), filter(copy_users));
	left(filter(copy_converters), filter(copy_controllers));
	binding(filter(copy_groups_in_controllers));
}

void Graph_Builder::right
(
	const Mysql_Types::Mysql_Groups_Data_List& mysql_groups_data_list,
	const Mysql_Types::Mysql_Employees_Data_List& mysql_employees_data_list
)
{
	Graph_Types::transform(mysql_groups_data_list, _groups_list);
	Graph_Types::transform(mysql_employees_data_list, _users_list);
	Graph_Types::Building::build(_groups_list, _users_list);
	/*for (auto& mysql_group_info : mysql_groups_data_list)
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
			_users_list.emplace_back(new Graph_Types::Graph_User(_users_info_list.back()));
			Graph_Types::bind_one_one(_groups_list.back(), _users_list.back());
		}
	}*/
}


void Graph_Builder::left
(
	const Mysql_Types::Mysql_Converters_Data_List& mysql_converters_data_list,
	const Mysql_Types::Mysql_Controllers_Data_List& mysql_controllers_data_list
) 
{
	Graph_Types::transform(mysql_converters_data_list, _converters_list);
	Graph_Types::transform(mysql_controllers_data_list, _controllers_list);
	Graph_Types::Building::build(_converters_list, _controllers_list);
	/*for (auto& mysql_converter_info : mysql_converters_data_list)
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
			_controllers_list.emplace_back(new Graph_Types::Graph_Controller(_controllers_info_list.back()));
			Graph_Types::bind_one_one(_converters_list.back(), _controllers_list.back());
		}
	}*/
}


void Graph_Builder::binding(const Mysql_Types::Mysql_Groups_In_Controllers_Data_List& mysql_groups_in_controllers_data_list)
{
	Graph_Types::Building::stiching(_controllers_list,mysql_groups_in_controllers_data_list, _groups_list);
}

void Graph_Builder::add_Users(const Mysql_Types::Mysql_Employees_Data_List& mysql_employees_data_list) {
	/*Graph_Types::transform(mysql_employees_data_list,);*/
}

//void Graph_Builder::bind_one_pair(const Graph_Types::Group_In_Controller_sRef& group_in_controller) {
//
//	auto controller = std::find_if(
//		_controllers_list.cbegin(),
//		_controllers_list.cend(),
//		[group_in_controller](const Graph_Types::Graph_Controller_sRef& controller)
//		{
//			return group_in_controller->_id_controllers == controller->_data->_id;
//		}
//	);
//	auto group = std::find_if(
//		_groups_list.cbegin(),
//		_groups_list.cend(),
//		[group_in_controller](const Graph_Types::Graph_Group_sRef& group)
//		{
//			return group_in_controller->_id_groups == group->_data->_id;
//		}
//	);
//
//	if (controller != _controllers_list.cend() && group != _groups_list.cend())
//	{
//		Graph_Types::bind_one_one();
//		(*controller)->_child.emplace_back(group_in_controller->_position_in_controller, *group);
//		(*group)->_parent.push_back(*controller);
//	}
//	else {
//		throw Programm_Exceptions("Not valid bond!");
//	}
//}


//void Graph_Builder::add_User(const Mysql_Types::Mysql_Employees_Data_List& mysql_employees_data_list) 
//{
//	//for (auto& user_info : mysql_employees_data_list) {
//
//	//	if (
//	//		std::find_if(
//	//			_users_info_list.cbegin(),
//	//			_users_info_list.cend(), 
//	//			[user_info](const Graph_Types::Graph_User_sRef& user)
//	//			{
//	//				return user_info._id == user->_data->_id;
//	//			}
//	//		) != _users_info_list.cend()) 
//	//	{
//	//		Log(MessageTypes::WARNING) << 
//	//			LoggerFormat::format(
//	//				"Find duplicate of user entry: id '%', name '%', surname '%'",
//	//				user_info._id,
//	//				user_info._name,
//	//				user_info._surname
//	//			);
//	//		continue;
//	//	}
//
//	//	auto result = std::find_if(
//	//		_groups_list.cbegin(),
//	//		_groups_list.cend(),
//	//		[user_info](const Graph_Types::Graph_Group_sRef& group)
//	//		{
//	//			return group->_data->_id == user_info._id;
//	//		}
//	//	);
//
//		//if (result != _groups_list.cend()) {
//		//	_users_info_list.emplace_back(new Graph_Types::User_Info(user_info));
//		//	commit_users_list.emplace_back(new Graph_Types::Graph_User(_users_info_list.back(), *result));
//		//}
//		//else { // TODO ќб€зательно
//		//	Log(MessageTypes::ERR) << LoggerFormat::format("Invalid user info: name/surname '% %'", user_info._name, user_info._surname);
//		//}
//	}
//
//
//
//void Graph_Builder::add_Group(const Mysql_Types::Mysql_Groups_Data_List& mysql_groups_data_list)
//{
//	/*for (auto& mysql_group_info : mysql_groups_data_list)
//	{
//
//		if (
//			std::find_if(
//				_groups_info_list.cbegin(),
//				_groups_info_list.cend(),
//				[mysql_group_info](const Graph_Types::Graph_Group_sRef& group)
//		{
//			return mysql_group_info._id == group->_data->_id;
//		}
//			) != _groups_info_list.cend())
//		{
//			Log(MessageTypes::WARNING) <<
//				LoggerFormat::format(
//					"Find duplicate of group entry: id '%', group_name '%'",
//					mysql_group_info._id,
//					mysql_group_info._name
//				);
//			continue;
//		}
//
//		_groups_info_list.emplace_back(new Graph_Types::Group_Info(mysql_group_info));
//		commit_groups_list.emplace_back(new Graph_Types::Graph_Group(_groups_info_list.back()));*/
//
//		//Mysql_Types::Mysql_Employees_Data_List::const_iterator result;
//		//auto start_from = mysql_employees_data_list.cbegin();
//		//
//		//while (
//		//		(result = std::find_if(
//		//				start_from, 
//		//				mysql_employees_data_list.cend(), 
//		//				[mysql_group_info](const Mysql_Types::Mysql_Employee_Data_Type& user)
//		//				{
//		//					return mysql_group_info._id == user._id_groups;
//		//				}
//		//			)
//		//		) != mysql_employees_data_list.cend()
//		//	)
//		//{
//		//	start_from = result + 1;
//		//	_users_info_list.emplace_back(new Graph_Types::User_Info(*result));
//		//	_users_list.emplace_back(new Graph_Types::Graph_User(_users_info_list.back(), _groups_list.back()));
//		//	_groups_list.back()->_users_list.push_back(_users_list.back());
//		//}
//	//}
//}
//
//
//void Graph_Builder::add_Group_In_Controller(const Mysql_Types::Mysql_Groups_In_Controllers_Data_List& mysql_groups_in_controllers_data_list) {
//	
//}
//
//
//Graph_Types::Graph_Users_sRefs Graph_Builder::delete_User(const Mysql_Types::Mysql_Employees_Data_List& mysql_employees_data_list) 
//{
//
//}
//
//
//Graph_Types::Graph_Groups_sRefs Graph_Builder::delete_Group(const Mysql_Types::Mysql_Groups_Data_List& mysql_groups_data_list)
//{
//
//}


//void Graph_Builder::commit_change() {
//	
//}
//
//
//void Graph_Builder::add_commit() {
//	if (!commit_groups_list.empty()) _groups_list.insert(_groups_list.cend(), commit_groups_list.cbegin(), commit_groups_list.cend());
//	if (!commit_users_list.empty()) _users_list.insert(_users_list.cend(), commit_users_list.cbegin(), commit_users_list.cend());
//	if (!commit_groups_in_controllers_list.empty()) {
//		for (auto& group_in_controller : commit_groups_in_controllers_list) 
//		{
//			bind_one_pair(group_in_controller);
//		}
//	}
//
//	find_affected_converters();
//
//	commit_groups_list.clear();
//	commit_users_list.clear();
//	commit_groups_in_controllers_list.clear();
//}