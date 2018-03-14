#include "stdafx.h"
#include "Graph_Builder.h"
#include "Util.h"

///
/// ќдновременное построение и св€зывание
/// т.е. построение(св€зывание) слева, справа и св€зывание
///

Graph_Builder::Graph_Builder()
{
	
}


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

void Graph_Builder::add_to_notify_set(Graph_Types::Graph_Converters_Set_Ref& converters_set) {
	_converters_set->insert(converters_set->begin(), converters_set->end());
	converters_set.reset(nullptr);
}

void Graph_Builder::add_Users(const Mysql_Types::Mysql_Employees_Data_List& mysql_employees_data_list) {
	auto copy_users = mysql_employees_data_list;
	copy_users = filter_by(copy_users, _users_list);
	std::for_each(copy_users.begin(), copy_users.end(), [this](auto& user) { add_User(user); });
}

void Graph_Builder::add_User(Mysql_Types::Mysql_Employee_Data_Type& user) {
	auto new_element = Graph_Types::transform(user, _users_list);
	Graph_Types::User_In_Group_Pair_uRef parent_pair; 
	try {
		parent_pair = Graph_Types::Building::bind_element(_groups_list, new_element); // bind
		add_to_notify_set(Graph_Types::Search<Graph_Types::Graph_Converter_sRef, Graph_Types::Less<Graph_Types::Graph_Converter_sRef>>::find_single(new_element)); // Ќайти converter TODO уведомить в commit
	}
	catch (const std::exception& error){
		Log(MessageTypes::WARNING) << LoggerFormat::format("Add user '(id:%, name:%, surname:%)' prevented!", user._id, user._name, user._surname);
		cancel(parent_pair, new_element);
	}
}

void Graph_Builder::delete_Users(const Mysql_Types::Mysql_Employees_Data_List& mysql_employees_data_list) {
	auto copy_users = mysql_employees_data_list;
	copy_users = filter_by(copy_users, _users_list);
	std::for_each(copy_users.begin(), copy_users.end(), [this](auto& user) { delete_User(user); });
}

void Graph_Builder::delete_User(Mysql_Types::Mysql_Employee_Data_Type& user) {
	try {
		auto old_element = Graph_Types::find_wrapper(user, _users_list);
		add_to_notify_set(Graph_Types::Search<Graph_Types::Graph_Converter_sRef, Graph_Types::Less<Graph_Types::Graph_Converter_sRef>>::find_single(*old_element));
		Graph_Types::Building::unbind_element(_users_list, old_element);
	}
	catch (const std::exception& error) {

	}
}

void Graph_Builder::update_Users(const Mysql_Types::Mysql_Employees_Data_List& mysql_employees_data_list) {
	try {

	}
	catch (std::exception& error) {
		Log(MessageTypes::WARNING) << "Update users prevented!";
	}
}

void Graph_Builder::add_Groups(const Mysql_Types::Mysql_Groups_Data_List& mysql_groups_data_list, const Mysql_Types::Mysql_Groups_In_Controllers_Data_List& mysql_groups_in_controllers_data_list) {
	auto copy_groups = mysql_groups_data_list;
	auto copy_ginc = mysql_groups_in_controllers_data_list;
	copy_groups = filter_by(copy_groups, _groups_list);
	std::for_each(copy_groups.begin(), copy_groups.end(), [this, &copy_ginc](auto& group) { add_Group(group, copy_ginc); });
}


void Graph_Builder::add_Group(Mysql_Types::Mysql_Group_Data_Type& group, const Mysql_Types::Mysql_Groups_In_Controllers_Data_List& copy_ginc) {
	auto new_element = Graph_Types::transform(group, _groups_list);
	auto bind_by = Graph_Types::find_links(new_element, copy_ginc);
	Graph_Types::Groups_In_Controllers_Pairs_uRef  parents_list_pair; 

	try {
		parents_list_pair = Graph_Types::Building::bind_element(_controllers_list, new_element, bind_by); // bind
		add_to_notify_set(Graph_Types::Search<Graph_Types::Graph_Converter_sRef, Graph_Types::Less<Graph_Types::Graph_Converter_sRef>>::find_single(new_element)); // Ќайти converter TODO уведомить в commit
	}
	catch (const std::exception& error) {
		Log(MessageTypes::WARNING) << LoggerFormat::format("Add group '(id:%, name:%)' prevented!", group._id, group._name);
		cancel(parents_list_pair, new_element);
		// cancel
	}
}


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