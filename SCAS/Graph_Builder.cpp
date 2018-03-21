#include "stdafx.h"
#include "Graph_Builder.h"
#include "Util.h"

///
/// Одновременное построение и связывание
/// т.е. построение(связывание) слева, справа и связывание
///

Graph_Builder::Graph_Builder()
{
	_converters_set = std::make_unique<Graph_Types::Graph_Converters_Set_Ref::element_type>();
}


Graph_Builder::~Graph_Builder()
{
	_converters_set.reset();
}

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
}


void Graph_Builder::binding(const Mysql_Types::Mysql_Groups_In_Controllers_Data_List& mysql_groups_in_controllers_data_list)
{
	Graph_Types::Building::stiching(_controllers_list,mysql_groups_in_controllers_data_list, _groups_list);
}

void Graph_Builder::add_to_notify_set(Graph_Types::Graph_Converters_Set_Ref& converters_set) {
	if (converters_set != nullptr) {
		_converters_set->insert(converters_set->begin(), converters_set->end());
		converters_set.reset();
	}
}

/// ADD USER DONE
void Graph_Builder::add_Users(const Mysql_Types::Mysql_Employees_Data_List& mysql_employees_data_list) {
	/// DONE
	auto copy_users = mysql_employees_data_list;
	copy_users = filter_by
		<
		Graph_Types::Equal_NSTEQ
			<
			Mysql_Types::Mysql_Employees_Data_List::value_type,
			Graph_Types::Graph_User_sRef
			>
		>
		(copy_users, _users_list);
	std::for_each(copy_users.begin(), copy_users.end(), [this](auto& user) { add_User(user); });
}

void Graph_Builder::add_User(Mysql_Types::Mysql_Employee_Data_Type& user) {
	/// DONE
	Graph_Types::Graph_Users_sRefs::const_iterator new_element = Graph_Types::transform(user, _users_list);
	Graph_Types::Graph_Converters_Set_Ref converter_set = nullptr;
	Graph_Types::User_In_Group_Pair_uRef parent_pair = nullptr; 

	try {
		parent_pair = Graph_Types::Building::bind_element(_groups_list, *new_element); // bind
		converter_set = Graph_Types::Search<Graph_Types::Graph_Converter_sRef, Graph_Types::Less<Graph_Types::Graph_Converter_sRef>>::find_single(*new_element); // Найти converter TODO уведомить в commit
	}
	catch (const std::exception& error){
		Log(MessageTypes::WARNING) << LoggerFormat::format("Add user '(id:%, name:%, surname:%)' prevented!", user._id, user._name, user._surname);
		cancel_add(_users_list, parent_pair, new_element, converter_set);
	}
	add_to_notify_set(converter_set);
}
/// ADD USER

/// DELETE USER DONE
void Graph_Builder::delete_Users(const Mysql_Types::Mysql_Employees_Data_List& mysql_employees_data_list) {
	/// DONE
	auto copy_users = mysql_employees_data_list;
	copy_users = filter_by<
	Graph_Types::Equal_NSTNEQ 
		<
			Mysql_Types::Mysql_Employees_Data_List::value_type,
			Graph_Types::Graph_User_sRef
		>
	>
	(copy_users, _users_list);
	std::for_each(copy_users.begin(), copy_users.end(), [this](auto& user) { delete_User(user); });
}

void Graph_Builder::delete_User(Mysql_Types::Mysql_Employee_Data_Type& user) {
	/// DONE
	Graph_Types::Graph_Users_sRefs::const_iterator old_element_iterator = _users_list.cend();
	Graph_Types::Graph_Users_sRefs::value_type old_element = nullptr;
	Graph_Types::Graph_Converters_Set_Ref converter_set = nullptr;

	try {
		if ((old_element_iterator = Graph_Types::find_wrapper(user, _users_list)) == _users_list.cend()) 
			throw Not_Found_Exception(LoggerFormat::format(
				"User (id:'%', name:'%', surname:'%') not found to delete!",
				user._id, user._name, user._surname)); // Нашли обертку
		converter_set = Graph_Types::Search<Graph_Types::Graph_Converter_sRef, Graph_Types::Less<Graph_Types::Graph_Converter_sRef>>::find_single(*old_element_iterator); // Нашли конверторы
		old_element = Graph_Types::Building::unbind_element(_users_list, old_element_iterator); // Отвязали от родительского
		_users_list.erase(old_element_iterator); // Удаление
	}
	catch (const std::exception& error) {
		Log(MessageTypes::WARNING) << 
			LoggerFormat::format(
				"Add user (id:'%', name:'%', surname:'%') prevented!",
				user._id, user._name, user._surname);
		cancel_delete(_groups_list, _users_list, old_element, old_element_iterator, converter_set);
	}
	add_to_notify_set(converter_set);
}
/// DELETE USER

///  UPDATE USER NEED
void Graph_Builder::update_Users(const Mysql_Types::Mysql_Employees_Data_List& mysql_employees_data_list) {
	try {

	}
	catch (std::exception& error) {
		Log(MessageTypes::WARNING) << "Update users prevented!";
	}
}

void Graph_Builder::update_User(Mysql_Types::Mysql_Employee_Data_Type&) {

}
///  UPDATE USER

/// ADD GROUP DONE
void Graph_Builder::add_Groups(const Mysql_Types::Mysql_Groups_Data_List& mysql_groups_data_list, const Mysql_Types::Mysql_Groups_In_Controllers_Data_List& mysql_groups_in_controllers_data_list) {
	/// DONE
	auto copy_groups = mysql_groups_data_list;
	auto copy_ginc = mysql_groups_in_controllers_data_list;
	copy_groups = filter_by
		<
			Graph_Types::Equal_NSTEQ
			<
				Mysql_Types::Mysql_Groups_Data_List::value_type,
				Graph_Types::Graph_Group_sRef
			>
		>
		(copy_groups, _groups_list);
	std::for_each(copy_groups.begin(), copy_groups.end(), [this, &copy_ginc](auto& group) { add_Group(group, copy_ginc); });
}

void Graph_Builder::add_Group(Mysql_Types::Mysql_Group_Data_Type& group, const Mysql_Types::Mysql_Groups_In_Controllers_Data_List& copy_ginc) {
	Graph_Types::Groups_In_Controllers_Pairs_uRef  parents_list_pair = nullptr;
	Graph_Types::Graph_Converters_Set_Ref converter_set = nullptr;

	Graph_Types::Graph_Groups_sRefs::const_iterator new_element = Graph_Types::transform(group, _groups_list);
	auto bind_by = Graph_Types::find_links(*new_element, copy_ginc);

	try {
		parents_list_pair = Graph_Types::Building::bind_element(_controllers_list, *new_element, bind_by); // bind
		converter_set = Graph_Types::Search<Graph_Types::Graph_Converter_sRef, Graph_Types::Less<Graph_Types::Graph_Converter_sRef>>::find_single(*new_element); // Найти converter TODO уведомить в commit
	}
	catch (const std::exception& error) {
		Log(MessageTypes::WARNING) << LoggerFormat::format("Add group '(id:%, name:%)' prevented!", group._id, group._name);
		cancel_add(_groups_list, parents_list_pair, new_element, converter_set);
	}
	add_to_notify_set(converter_set);
}
/// ADD GROUP


/// DELETE GROUP
void Graph_Builder::delete_Groups(const Mysql_Types::Mysql_Groups_Data_List& mysql_groups_data_list) {
	auto copy_groups = mysql_groups_data_list;
	copy_groups = filter_by
		<
			Graph_Types::Equal_NSTNEQ
			<
				Mysql_Types::Mysql_Groups_Data_List::value_type,
				Graph_Types::Graph_Group_sRef
			>
		>
		(copy_groups, _groups_list);
	std::for_each(copy_groups.begin(), copy_groups.end(), [this](auto& group) { delete_Group(group); });
}

void Graph_Builder::delete_Group(Mysql_Types::Mysql_Group_Data_Type& group) {
	Graph_Types::Graph_Groups_sRefs::const_iterator old_element_iterator = _groups_list.cend();
	Graph_Types::Graph_Group_sRef::element_type::_Child_Type old_element_childs;
	Graph_Types::Group_Controllers_uRef old_element_data = nullptr;
	Graph_Types::Graph_Converters_Set_Ref converter_set = nullptr;

	try {
		if ((old_element_iterator = Graph_Types::find_wrapper(group, _groups_list)) == _groups_list.cend())
			throw Not_Found_Exception(LoggerFormat::format(
				"Group (id:'%', name:'%') not found to delete!",
				group._id, group._name)); // Нашли обертку
		old_element_childs = (*old_element_iterator)->_child; // Копировали детей
		converter_set = Graph_Types::Search<Graph_Types::Graph_Converter_sRef, Graph_Types::Less<Graph_Types::Graph_Converter_sRef>>::find_single(*old_element_iterator); // Нашли конверторы
		old_element_data = Graph_Types::Building::unbind_element(_groups_list, old_element_iterator); // Отвязали от родительского
		_groups_list.erase(old_element_iterator); // Удаление
		force_delete(old_element_childs, _users_list);
	}
	catch (const std::exception& error) {
		Log(MessageTypes::WARNING) <<
			LoggerFormat::format(
				"Add group (id:'%', name:'%') prevented!",
				group._id, group._name);
		//cancel_delete(_groups_list, _users_list, old_element, old_element_iterator, converter_set);
	}
	add_to_notify_set(converter_set);
}
/// DELETE GROUP
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