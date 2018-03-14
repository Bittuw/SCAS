#pragma once

///
/// Represent main data types
///

#ifndef MAIN_CONNECION_INFO
#define MAIN_CONNECION_INFO

#include <string>
#include <set>
#include "Util.h"
#include "Mysql_Types.h"

namespace Graph_Types {

	///
	/// Defines of data fields 
	///

#define PK(type, name)\
	struct pk_##name{\
		type pk;\
		using pk_type = type;\
	} _pk;\

#define FK(type, name)\
	struct fk_##name{\
		type fk;\
		using fk_type = type;\
	}_fk;\

#define FIELD(type, name)\
	struct field_##name{\
		type name;\
		using field_type = type;\
	} name;\
	
#define Converter_Info_Fields\
	PK(unsigned int, _id)\
	FIELD(unsigned int, _nSn)\
	FIELD(std::wstring, _type_name)\
	FIELD(std::wstring, _first_ip_port)\
	FIELD(std::wstring, _second_ip_port)\

#define Controller_Info_Fields\
	PK(unsigned int, _id)\
	FIELD(unsigned int, _nSn)\
	FIELD(std::wstring, _type_name)\
	FIELD(std::wstring, _name)\
	FIELD(unsigned int, _max_groups)\
	FIELD(unsigned int, _max_keys)\
	FIELD(unsigned int, _max_events)\
	FIELD(unsigned int, _max_r_event_at_time)\
	FIELD(unsigned int, _max_w_event_at_time)\
	FK(unsigned int, _id_converter)

#define User_Info_Fields\
	PK(unsigned int, _id)\
	FIELD(std::wstring, _name)\
	FIELD(std::wstring, _surname)\
	FIELD(std::wstring, _patronymic)\
	FIELD(unsigned int, _card_number)\
	FK(unsigned int, _id_groups)

#define Group_Info_Fields\
	PK(unsigned int, _id)\
	FIELD(std::wstring, _name)\
	FIELD(unsigned int, _time_zone)\

//#define Group_In_Controller_Fields\
//	PK(unsigned int, _id)\
//	FK(unsigned int, _id_groups) \
//	FK(unsigned int, _id_controllers) \
//	FK(unsigned int, _id_converter)\
//	FIELD(unsigned int, _position_in_controller)

	static std::wstring unnamed = L"Unnamed";
	static unsigned int base_rw_events_at_time = 0x07;

	///
	/// Structs 
	///

	struct Model_Info {
		Model_Info(Model_Info&&) = default;
		Model_Info& operator=(Model_Info&&) = default;
		virtual ~Model_Info() {};
	};

	struct Converter_Info {

		Converter_Info_Fields

		Converter_Info() = default;
		Converter_Info(const Mysql_Types::Mysql_Converter_Data_Type& mysql_converter)
			:
			_pk({ mysql_converter._id }),
			_nSn({ mysql_converter._nSn }),
			_type_name({ Utils::MultiToWide(mysql_converter._type_name.c_str(), mysql_converter._type_name.size()) }),
			_first_ip_port({ Utils::MultiToWide(mysql_converter._first_ip_port.c_str(), mysql_converter._first_ip_port.size()) }),
			_second_ip_port({ Utils::MultiToWide(mysql_converter._second_ip_port.c_str(), mysql_converter._second_ip_port.size()) })
		{}
	};

	struct Controller_Info {

		Controller_Info_Fields

		Controller_Info() = default;
		Controller_Info(const Mysql_Types::Mysql_Controller_Data_Type& mysql_controller) 
			:
			_pk({ mysql_controller._id }),
			_nSn({ mysql_controller._nSn }),
			_type_name({ Utils::MultiToWide(mysql_controller._type_name.c_str(), mysql_controller._type_name.size()) }),
			_name({ Utils::MultiToWide(mysql_controller._name.c_str(), mysql_controller._name.size()) }),
			_max_groups({ mysql_controller._max_groups }),
			_max_keys({ mysql_controller._max_keys }),
			_max_events({ mysql_controller._max_events }),
			_max_r_event_at_time({ mysql_controller._max_r_event_at_time }),
			_max_w_event_at_time({ mysql_controller._max_w_event_at_time }),
			_fk({ mysql_controller._id_converter })
		{}
	};

	struct User_Info {

		User_Info_Fields

		User_Info() = default;
		User_Info(const Mysql_Types::Mysql_Employee_Data_Type& mysql_employee) 
			:
			_pk({ mysql_employee._id }),
			_name({ Utils::MultiToWide(mysql_employee._name.c_str(), mysql_employee._name.size()) }),
			_surname({ Utils::MultiToWide(mysql_employee._surname.c_str(), mysql_employee._surname.size()) }),
			_patronymic({ Utils::MultiToWide(mysql_employee._patronymic.c_str(), mysql_employee._patronymic.size()) }),
			_card_number({ mysql_employee._card_number }),
			_fk({ mysql_employee._id_groups })
		{}
	};

	struct Group_Info {

		Group_Info_Fields

		Group_Info() = default;
		Group_Info(const Mysql_Types::Mysql_Group_Data_Type& mysql_group)
			:
			_pk({ mysql_group._id }),
			_name({ Utils::MultiToWide(mysql_group._name.c_str(), mysql_group._name.size()) }),
			_time_zone({ mysql_group._time_zone })
		{}
	};

	template <typename Element>
	struct Less;
	/*struct Group_In_Controller_Info {

		Group_In_Controller_Fields

		Group_In_Controller_Info() = default;
		Group_In_Controller_Info(const Mysql_Types::Mysql_Group_In_Controller_Data_Type& mysql_group_in_controller) 
			:
			_pk({ { mysql_group_in_controller._id } }),
			_fk({ mysql_group_in_controller._id_groups }),
			_fk({ mysql_group_in_controller._id_controllers }),
			_fk(mysql_group_in_controller._id_converter),
			_position_in_controller(mysql_group_in_controller._position_in_controller)
		{}
	};*/

	///
	/// References of main types
	///

	using Converter_sRef = std::shared_ptr<Converter_Info>;
	using Controller_sRef = std::shared_ptr<Controller_Info>;
	using User_sRef = std::shared_ptr<User_Info>;
	using Group_sRef = std::shared_ptr<Group_Info>;
	//using Group_In_Controller_sRef = std::shared_ptr<Group_In_Controller_Info>;

	using Converters_sRefs = std::vector<Converter_sRef>;
	using Controllers_sRefs = std::vector<Controller_sRef>;
	using Users_sRefs = std::vector<User_sRef>;
	using Groups_sRefs = std::vector<Group_sRef>;
	//using Groups_In_Controllers_sRefs = std::vector<Group_In_Controller_sRef>;

	///
	/// Main types
	///

	class Graph_Base;
	class Graph_Converter;
	class Graph_Controller;
	class Graph_User;
	class Graph_Group;

	///
	/// Declarations of main types's fields
	///

	using Graph_Base_sRef = std::shared_ptr<Graph_Base>;
	using Graph_Base_sRefs = std::vector<Graph_Base_sRef>;

	using Graph_Converter_sRef = std::shared_ptr<Graph_Converter>; // Указатель на конвертер
	using Graph_Controller_sRef = std::shared_ptr<Graph_Controller>; // Указатель на контроллер
	using Graph_User_sRef = std::shared_ptr<Graph_User>; // Указатель на пользователя
	using Graph_Group_sRef = std::shared_ptr<Graph_Group>; // Указатель на группу
	using Graph_Nullptr_sRef = std::shared_ptr<nullptr_t>;

	using Graph_Converters_sRefs = std::vector<Graph_Converter_sRef>; // Список указателей на конверторы
	using Graph_Controlles_sRefs = std::vector<Graph_Controller_sRef>; // Список указателей на контроллеры
	using Graph_Users_sRefs = std::vector<Graph_User_sRef>; // Список указателей на пользователей
	using Graph_Groups_sRefs = std::vector<Graph_Group_sRef>; // Список указателй на группы

	using Graph_Group_Pair = std::pair<unsigned int, Graph_Group_sRef>; // Пара "позиция:группа"
	using Graph_Group_Pair_sRef = std::shared_ptr<Graph_Group_Pair>;
	using Graph_Groups_Pairs_sRefs = std::vector<Graph_Group_Pair_sRef>; // Список пар "позиция:группа"

	using Graph_Converters_Set_Ref = std::unique_ptr<std::set<Graph_Converter_sRef, Less<Graph_Converter_sRef>>>; // Уникально множество конверторов

	//////

	template<typename... Ts> struct typelist {
		template<typename T> using prepend = typelist<T, Ts...>;
	};

	template<typename T, typename... Ts> struct index;
	template<typename T, typename... Ts> struct index<T, T, Ts...> : std::integral_constant<int, 0> {};
	template<typename T, typename U, typename... Ts> struct index<T, U, Ts...> : std::integral_constant<int, index<T, Ts...>::value + 1> {};

	template<int n, typename... Ts> struct nth_impl;
	template<typename T, typename... Ts> struct nth_impl<0, T, Ts...> {
		using type = T;
	};
	template<int n, typename T, typename... Ts> struct nth_impl<n, T, Ts...> {
		using type = typename nth_impl<n - 1, Ts...>::type;
	};
	template<int n, typename... Ts> using nth = typename nth_impl<n, Ts...>::type;

	template<int n, int m, typename... Ts> struct extract_impl;
	template<int n, int m, typename T, typename... Ts>
	struct extract_impl<n, m, T, Ts...> : extract_impl<n, m - 1, Ts...> {};
	template<int n, typename T, typename... Ts>
	struct extract_impl<n, 0, T, Ts...> {
		using types = typename extract_impl<n, n - 1, Ts...>::types::template prepend<T>;
	};
	template<int n, int m> struct extract_impl<n, m> {
		using types = typelist<>;
	};
	template<int n, int m, typename... Ts> using extract = typename extract_impl<n, m, Ts...>::types;

	template<typename S, typename T> struct tt_impl;
	template<typename... Ss, typename... Ts>
	struct tt_impl<typelist<Ss...>, typelist<Ts...>> :
		public std::tuple<Ts...> {

		template<typename... Args> tt_impl(Args &&...args) :
			std::tuple<Ts...>(std::forward<Args>(args)...) {}

		template<typename S> nth<index<S, Ss...>::value, Ts...> get() {
			return std::get<index<S, Ss...>::value>(*this);
		}
	};
	template<typename... Ts> struct tagged_tuple : tt_impl<extract<2, 0, Ts...>, extract<2, 1, Ts...>> {
		template<typename... Args> tagged_tuple(Args &&...args) :
			tt_impl<extract<2, 0, Ts...>, extract<2, 1, Ts...>>(std::forward<Args>(args)...) {}
	};

	template <typename...Ts>
	struct FKeys {
		tagged_tuple<Ts...> fkeys;
	};

	class Graph_Base {
	public:
		Graph_Base() = default;
		Graph_Base(Graph_Base&&) = default;
		Graph_Base& operator=(Graph_Base&&) = default;
		virtual ~Graph_Base() = default;
	};

	template <typename P, typename D, typename C>
	class Graph_Point : Graph_Base {
	public:
		P _parent;
		D _data;
		C _child;

		using _Parent_Type = P;
		using _Data_Type = D;
		using _Child_Type = C;

		Graph_Point() = default;
		Graph_Point(const D& data) : Graph_Base(), _data(data){}
	};


	//template <
	//	typename P, typename D, typename C,
	//	typename P_True_Type,
	//	typename D_True_Type,
	//	typename C_True_Type
	//>
	//class Graph_Data_Type_Deduct : public Graph_Point<P,D,C>{
	//public:
	//	using _Parent_True_Type = P_True_Type;
	//	using _Data_True_Type = D_True_Type;
	//	using _Child_True_type = C_True_Type;

	//	Graph_Data_Type_Deduct() = default;
	//	Graph_Data_Type_Deduct(const D& data) : Graph_Point(data){}
	//};


	//template <typename P, typename D, typename C, typename D_True_Type, typename C_True_Type>
	//class Graph_Vector_Parent : public Graph_Data_Type_Deduct <P,D,C,P::value_type::element_type, D_True_Type, C_True_Type> {
	//public:
	//	Graph_Vector_Parent() = default;
	//	Graph_Vector_Parent(const D& data) : Graph_Data_Type_Deduct(data) {}
	//};


	//template <typename P, typename D, typename C, typename D_True_Type, typename C_True_Type>
	//class Graph_Single_Parent : public virtual Graph_Data_Type_Deduct <P, D, C, P::element_type, D_True_Type, C_True_Type> {
	//public:
	//	Graph_Single_Parent() = default;
	//	Graph_Single_Parent(const D& data) : Graph_Data_Type_Deduct(data) {}
	//};

	//template <typename P, typename D, typename C, typename D_True_Type, typename P_True_Type>
	//class Graph_Vector_Child : public virtual Graph_Data_Type_Deduct <P, D, C, P_True_Type, D_True_Type, C::value_type::element_type> {
	//public:
	//	Graph_Vector_Child() = default;
	//	Graph_Vector_Child(const D& data) : Graph_Data_Type_Deduct(data) {}
	//};

	//template <typename P, typename D, typename C, typename D_True_Type, typename P_True_Type>
	//class Graph_Single_Child : public virtual Graph_Data_Type_Deduct <P, D, C, P_True_Type, D_True_Type, C::value_type::element_type> {
	//public:
	//	Graph_Single_Child() = default;
	//	Graph_Single_Child(const D& data) : Graph_Data_Type_Deduct(data) {}
	//};

	template <typename D, typename C>
	class Graph_Zero_Parent : public virtual Graph_Point<Graph_Nullptr_sRef, D, C> {
	public:
		Graph_Zero_Parent() = default;
		Graph_Zero_Parent(const D& data) : Graph_Point(data) {}
	};

	template <typename P, typename D>
	class Graph_Zero_Child : public Graph_Point<P, D, Graph_Nullptr_sRef> {
	public:
		Graph_Zero_Child() = default;
		Graph_Zero_Child(const D& data) : Graph_Point(data) {}
	};

	class Graph_Converter : public Graph_Zero_Parent<
		Converter_sRef, Graph_Controlles_sRefs> {
	public:
		Graph_Converter() = default;
		Graph_Converter(const Converter_sRef& converter_info) 
			: 
			Graph_Zero_Parent(converter_info)
		{};
	};

	class Graph_Controller : public Graph_Point
		<Graph_Converter_sRef, Controller_sRef, Graph_Groups_Pairs_sRefs> {
	public:
		Graph_Controller() = default;
		Graph_Controller(const Controller_sRef& controller_info)
			:
			Graph_Point(controller_info)
		{}
	};

	class Graph_Group : public Graph_Point
		<Graph_Controlles_sRefs, Group_sRef, Graph_Users_sRefs> {
	public:
		Graph_Group() = default;
		Graph_Group(const Group_sRef& group_info)
			:
			Graph_Point(group_info)
		{}

	};

	class Graph_User : public Graph_Zero_Child
		<Graph_Group_sRef, User_sRef> {
	public:
		Graph_User() = default;
		Graph_User(const User_sRef& user_info)
			: // Построение
			Graph_Zero_Child(user_info)
		{}
	};

	///

	using  User_In_Group_Pair = std::pair<Graph_Group::_Child_Type, Graph_Group::_Child_Type::const_iterator>;
	using Groups_In_Controllers_Pairs = std::vector<std::pair<Graph_Types::Graph_Controller::_Child_Type, Graph_Types::Graph_Controller::_Child_Type::const_iterator>>;
	///
	template <typename Element>
	struct Less {
		constexpr bool operator()(const Element& right, const Element& left) {
			return right->_data->_pk.pk < left->_data->_pk.pk;
		}
	};

	template <>
	struct Less<Graph_Converter_sRef> {
		constexpr bool operator()(const Graph_Converter_sRef& right, const Graph_Converter_sRef& left) {
			return right->_data->_nSn._nSn < left->_data->_nSn._nSn;
		}
	};

	// Трансформируем иходные списки
	template
		<
		template <typename, typename> class From,
		template <typename, typename> class To,
		typename From_Element, typename To_Element
		> // Трансформировать список в список
		inline static decltype(auto) transform(const From<From_Element, std::allocator<From_Element>>& flist, To<To_Element, std::allocator<To_Element>>& tlist) {
		std::transform(
			flist.cbegin(),
			flist.cend(),
			std::back_inserter(tlist),
			[](const From_Element& element)
		{ return nullptr/*std::make_shared<To_Element::element_type>(std::make_shared<To_Element::element_type::_Data_Type>(element))*/; }
		);
		auto new_element = (tlist.cend() - flist.size());
		return new_element;
	}


	template <template <typename, typename> class Save_In, typename Save_In_Element, typename Element> // Аналог для единичного элемента
	inline static decltype(auto) transform(const Element& element, Save_In<Save_In_Element, std::allocator<Save_In_Element>>& s_list)
	{
		s_list.push_back(
			std::make_shared<Save_In_Element::element_type>(
				std::make_shared<Save_In_Element::element_type::_Data_Type::element_type>(element)
				)
		);
		return s_list.back();
	}


	template <typename Element>
	inline static decltype(auto) find_links(const Element& element, const Mysql_Types::Mysql_Groups_In_Controllers_Data_List& all_binds) {
		Mysql_Types::Mysql_Groups_In_Controllers_Data_List bind_by;
		std::remove_copy_if(all_binds.cbegin(), all_binds.cend(), std::back_inserter(bind_by), [&element](auto& link) { return element->_data->_pk.pk == link._id_groups; });
		return bind_by;
	}

	class Building {

		template <typename List, typename Parametr>
		inline static decltype(auto) build_one(List& list, const Parametr& parametr) {
			list.emplace_back(new List::value_type::element_type(parametr));
			return list.back();
		}

		template <typename Parent, typename Child> // Связать родителя и ребенка (Много к много) Специально для controller <-> group
		inline static decltype(auto) bind_one_one(
			const Parent& parent,
			const Child& child,
			const unsigned int position
		)
		{ 
			Child::element_type::_Parent_Type::const_iterator result;
			if ((result = std::find_if(child->_parent.cbegin(), child->_parent.cend(), [parent](const Parent& element) { return parent->_data->_pk.pk == element->_data->_pk.pk; })) != child->_parent.cend())
				throw Programm_Exceptions(
					LoggerFormat::format(
						"Child element already has parent: class parent: '%' with id '%', class child: '%' with id '%'",
						typeid(parent).name(),
						parent->_data->_pk.pk,
						typeid(child).name(),
						child->_data->_pk.pk
					)
				);
			parent->_child.push_back(std::make_shared<Parent::element_type::_Child_Type::value_type::element_type>(position, child));
			child->_parent.push_back(parent);
			return std::prev(parent->_child.cend(), 1);
		}

		template <typename Parent, typename Child> // Связать родителя и ребенка (Много к 1)
		inline static decltype(auto) bind_many_one(const Parent& parent, const Child& child)
		{
			if (child->_parent != nullptr)
				throw Programm_Exceptions(
					LoggerFormat::format(
						"Child element already has parent: class parent: '%' with id '%', class child: '%' with id '%'",
						typeid(parent).name(),
						parent->_data->_pk.pk,
						typeid(child).name(),
						child->_data->_fk.fk
					)
				);
			parent->_child.push_back(child);
			child->_parent = parent;
			return std::prev(parent->_child.cend(), 1);
		}

		template <typename Parent, typename Child> // Отвязать родителя и ребенка (Много к 1)
		inline static void unbind_many_one(const Parent& parent, const Child& child) {
			if (child->_parent == nullptr || parent->_child.empty())
				throw Programm_Exceptions(
					LoggerFormat::format(
						"Cannot unbind child '%:id(%)' from parent '%:id(%)'",
						typeid(child).name(),
						child->_data->_fk.fk,
						typeid(parent).name(),
						parent->_data->_pk.pk
					)
				);
				parent->_child.erase(std::remove_if(
						parent->_child.begin(), 
						parent->_child.end(), 
						[&child](const Parent::element_type::_Child_Type::value_type& element_to_delete)
						{ return child->_data->_pk.pk == element_to_delete->_data->_pk.pk; }
					)
				);
				child->_parent.reset();
		}
	public:
		template <
			typename PList, typename CList
		>
		static void rebuild( // Перестроение (Очистка)
			PList& plist, CList& clist
		)
	{
		for (auto& parent : plist)
		{
			parent->_child.clear();
			CList::const_iterator result;
			auto start_from = clist.cbegin();

			while ((result = std::find_if(start_from, clist.cend(), [parent](const CList::value_type& element) { return parent->_data->_pk.pk == element->_data->_fk.fk; })) != clist.cend())
			{
				*result->_parent.clear();
				start_from = result + 1;
				bind_many_one(parent, *result);
			}
		}
	}

		template <
			typename PList, typename CList
		>
		static void build( // Построение
			PList& plist, CList& clist
		)
		{
			for (auto& parent : plist)
			{
				CList::const_iterator result;
				auto start_from = clist.cbegin();

				while ((result = std::find_if(start_from, clist.cend(), [parent](const CList::value_type& element) { return parent->_data->_pk.pk == element->_data->_fk.fk; })) != clist.cend())
				{
					start_from = result + 1;
					bind_many_one(parent, *result);
				}
			}
		}

		// Спецефичное заполнение таблиц связей (Controller <-> Group)
		static void stiching(
			const Graph_Controlles_sRefs& controllers_srefs,
			const Mysql_Types::Mysql_Groups_In_Controllers_Data_List& mysql_groups_in_controllers_data_list,
			const Graph_Groups_sRefs& groups_srefs
		) 
		{
			for (auto& group_in_controller : mysql_groups_in_controllers_data_list) {
		
				auto controller = std::find_if(
					controllers_srefs.cbegin(),
					controllers_srefs.cend(),
						[group_in_controller](const Graph_Types::Graph_Controller_sRef& controller)
						{
							return group_in_controller._id_controllers == controller->_data->_pk.pk;
						}
					);
				auto group = std::find_if(
					groups_srefs.cbegin(),
					groups_srefs.cend(),
						[group_in_controller](const Graph_Types::Graph_Group_sRef& group)
						{
							return group_in_controller._id_groups == group->_data->_pk.pk;
						}
					);

				if (controller != controllers_srefs.cend() && group != groups_srefs.cend())
					{
						bind_one_one(*controller, *group, group_in_controller._position_in_controller);
					}
					else {
						throw Programm_Exceptions("Not valid bond!");
					}
			}
		}

		///
		template <typename Child_Iterator, typename T> // Заполнение таблиц связей
		inline static void bind_elements(const T& parent_list, Child_Iterator& from, Child_Iterator& to)
		{
			std::for_each(from, to, 
				[&](const std::iterator_traits<Child_Iterator>::value_type& element) 
				{
					auto result = std::find_if(
						parent_list.cbegin(),
						parent_list.cend(),
						[from](const T::value_type& parent) { return parent->_data->_pk.pk == (*from)->_data->_fk.fk; });
					/*(*result)->_child.push_back(*from);
					(*from)->_parent = *result;*/
					bind_many_one(*result, *from);
			});
		}
		
		template <typename Child_Iterator, typename T> // Заполнение таблиц связей Only for controllers <-> groups
		inline static void bind_elements(const T& parent_list, const Mysql_Types::Mysql_Groups_In_Controllers_Data_List& bind_by_list, Child_Iterator& from, Child_Iterator& to) {
			for (auto& bind_element : bind_by_list) {
				auto result_c = std::find_if(parent_list.cbegin(), parent_list.cend(), [bind_element](const T::value_type& element) { return element->_data->_pk.pk == bind_element._id_controllers; });
				auto result_g = std::find_if(from, to, [bind_element](const std::iterator_traits<Child_Iterator>::value_type& element) { return element->_data->_pk.pk == bind_element._id_groups; });
				if ((result_c == parent_list.cend()) || (result_g == to)) {
					bind_one_one(*result_c, *result_g, bind_element._position_in_controller);
				}
			}
			/*for (; from < to; from++) {
			auto result = std::find_if(
			parent_list.cbegin(),
			parent_list.cend(),
			[from](const T::value_type& parent) { return parent->_data->_pk.pk == (*from)->_data->_fk.fk; });
			(*result)->_child.push_back(*from);
			(*from)->_parent = *result;
			}*/
		}

		template <template <typename, typename> class Parent_List, typename Parent_Object, typename Child_Object> // Аналог для единичного элемента (Возврат родителя)
		inline static decltype(auto) bind_element(Parent_List<Parent_Object, std::allocator<Parent_Object>>& parent_list, Child_Object& child_element) {
			auto parent = std::find_if(parent_list.cbegin(), parent_list.cend(), [&child_element](auto& parent) { return parent->_data->_pk.pk == child_element->_data->_fk.fk; });
			if (parent == parent_list.cend()) {
				throw Programm_Exceptions (
					LoggerFormat::format(
						"No group (id:'%') was found for the user (id:'%', name:'%', surname:'%')",
						child_element->_data->_fk.fk,
						child_element->_data->_pk.pk,
						Utils::WideToMulti(child_element->_data->_name._name),
						Utils::WideToMulti(child_element->_data->_surname._surname))
					);
			}
			auto child_in_parent = bind_many_one(*parent, child_element);
			return std::make_pair(std::ref((*parent)->_child), child_in_parent);
		}

		template <template <typename, typename> class Parent_List, typename Parent_Object, typename Child_Object>
		inline static decltype(auto) bind_element(Parent_List<Parent_Object, std::allocator<Parent_Object>>& parent_list, Child_Object& child_element, Mysql_Types::Mysql_Groups_In_Controllers_Data_List& bind_by) {
			Groups_In_Controllers_Pairs parents_list_pair;
			for (auto& bind : bind_by) {
				auto result_c = std::find_if(parent_list.cbegin(), parent_list.cend(), [bind](const auto& element) { return element->_data->_pk.pk == bind._id_controllers; });
				if (result_c == parent_list.cend()) {
					parents_list_pair.emplace_back(
						std::ref((*result_c)->_child),
						bind_one_one(*result_c, child_element, bind._position_in_controller)
					);
				}
			}
			return parents_list_pair;
		}
		///


		template <typename F, template <typename,typename> class T, typename T_O>
		inline static decltype(auto) unbind_elements(const F& unbinding_data_list, T<T_O, std::allocator<T_O>>& unbinding_list) {
			T<T_O, std::allocator<T_O>> unbinded_elements;
			std::for_each(
				unbinding_data_list.cbegin(),
				unbinding_data_list.cend(),
				[&unbinding_list, &unbinded_elements](const F::value_type& element)
				{

					auto result = std::find_if(
						unbinding_list.cbegin(),
						unbinding_list.cend(),
						[&element](const T_O& old_element)
						{	
							return (element._id == old_element->_data->_pk.pk);
						}
					);
					if (result != unbinding_list.cend()) { 
						unbinded_elements.push_back(*result);
						auto old_element = *result;
						unbinding_list.erase(result);
						unbind_many_one(old_element->_parent, old_element);
					}
				}
			);
			return unbinded_elements;
		}
	};


	template <typename Target, typename Less>
	struct Search {

		using Target_Set_Ref = std::unique_ptr<std::set<Target, Less>>;

		// Для диапазона элементов
		template <typename Iterator>
		static decltype(auto) find_iterator(Iterator& from, Iterator& to) {
			Target_Set_Ref targer_set_ref = std::make_unique<Target_Set_Ref::element_type>();
			std::for_each(from, to,
				[&targer_set_ref, &from](const std::iterator_traits<Iterator>::value_type& element)
			{
				find(targer_set_ref, (*from)->_parent);
			}
			);
			return targer_set_ref;
		}

		// Для всего контейнера
		template <template <typename,typename> class List, typename Object>
		static decltype(auto) find_container(const List<Object, std::allocator<Object>>& container) {
			Target_Set_Ref targer_set_ref = std::make_unique<Target_Set_Ref::element_type>();
			std::for_each(container.cbegin(), container.cend(),
				[&targer_set_ref](const std::iterator_traits<List<Object, std::allocator<Object>>::const_iterator>::value_type& element)
				{
					find(targer_set_ref, element->_parent);
				}
			);
			return std::move(targer_set_ref);
		}

		// Для одного объекта
		template <typename Object>
		static decltype(auto) find_single(const Object& object) {
			Target_Set_Ref target_set_ref = std::make_unique<Target_Set_Ref::element_type>();
			find(target_set_ref, object->_parent);
			return std::move(target_set_ref);
		}

		
		/// Можно свой set
		// Для одного родителя
		template <typename Object>
		inline static void find(Target_Set_Ref& targer_set_ref, const Object& element) {
			find(targer_set_ref, element->_parent);
		}

		// Для множества родителей
		template <template <typename, typename> class Container, typename Object>
		inline static void find(Target_Set_Ref& targer_set_ref, const Container<Object, std::allocator<Object>> container) {
			if (container.empty())
				throw Programm_Exceptions(LoggerFormat::format("%'s parent list is empty!", typeid(Object::element_type).name()));
			for (auto& element : container)
				find(targer_set_ref, element->_parent);
		}

		private:
		// Остановка ветки поиска (Целевой объект ветки найден)
		template <>
		inline static void find<Target>(Target_Set_Ref& targer_set_ref, const Target& element) {
			targer_set_ref->insert(element);
		}

	};
//	// Структура, которая используется/заполняется в runtime
//	struct Runtime_Info {
//
//		//Converter info
//		Converter_Handle _converter_handle;
//		Converter_Detail_Info _converter_detail_info;
//		Converter_Connection_Status _converter_connection_info;
//
//		//Controller info
//		Controllers_Detail_Info_List _controllers_detail_info_list;
//		Controllers_Connection_Status_List _controllers_connection_status_list;
//		Controllers_Index_Read_Write_List _controllers_index_read_write_list;
//
//		//Converter connection info
//		Connection_Type _connection_type;
//
//		//Mutex of access
//		Connection_Mutex_Ref _mutex;
//
//		Runtime_Info()
//			:
//			_converter_handle(),
//			_converter_detail_info(),
//			_converter_connection_info(),
//			_controllers_detail_info_list(),
//			_controllers_connection_status_list(),
//			_controllers_index_read_write_list(),
//			_connection_type(),
//			_mutex(std::make_shared<std::mutex>())
//		{}
//
//		Runtime_Info(Runtime_Info&& other)
//			:
//			_converter_detail_info(std::move(other._converter_detail_info)),
//			_converter_connection_info(std::move(other._converter_connection_info)),
//			_controllers_detail_info_list(std::move(other._controllers_detail_info_list)),
//			_controllers_connection_status_list(std::move(other._controllers_connection_status_list)),
//			_controllers_index_read_write_list(std::move(other._controllers_index_read_write_list)),
//			_connection_type(std::move(other._connection_type)),
//			_mutex(std::move(other._mutex))
//		{
//			memset(&other._converter_detail_info, 0, sizeof(other._converter_detail_info));
//			memset(&other._converter_connection_info, 0, sizeof(other._converter_connection_info));
//			//other._controllers_detail_info_list;
//			//other._controllers_connection_status_list;
//			//other._controllers_index_read_write_list;
//			other._connection_type = {};
//		}
//
//		Runtime_Info(const Zguard_Basic_Info& zguard_basic_info) {} //TODO check this
//
//		Runtime_Info(const Runtime_Info& other) = default;
//		Runtime_Info& operator=(Runtime_Info&& other) = default;
//		Runtime_Info& operator=(const Runtime_Info& other) = default;
//		virtual ~Runtime_Info() = default;
//	};
//
//
//	// Структура, которая инкапсулируется в объекте Connection (Создается либо из объекта Mysql_Basic_Info, либо  Zguard_basic_Info)
//	struct Main_Connection_Basic_Info_Types : Runtime_Info {
//
//		Basic_Converter_Data_Ref _converter_main_info;
//
//		Main_Connection_Basic_Info_Types(const Basic_Converter_Data_Ref& basic_converter_data_type)
//
//			: 
//			Runtime_Info(),
//			_converter_main_info(basic_converter_data_type)
//		{
//		}
//		//Main_Connection_Basic_Info_Types(const Zguard_Basic_Info& zguard_basic_info) 
//		//	: 
//		//	Runtime_Info(),
//		//	_converter_main_info(zguard_basic_info._zguard_conveter_data, zguard_basic_info._zguard_converter_ports_data)
//		//{
//		//	std::transform(
//		//		zguard_basic_info._zguard_controllers_data_list.cbegin(),
//		//		zguard_basic_info._zguard_controllers_data_list.cend(),
//		//		std::back_inserter(_controllers_main_info_list),
//		//		[](const Zguard_Controller_Data_Type& zguard_controller_data) -> decltype(auto) {
//		//			return Basic_Controller_Data_Type(zguard_controller_data);
//		//		}
//		//	);
//		//}
//
//		~Main_Connection_Basic_Info_Types() = default;
//	};
//
//	using Main_Connection_Basic_Info_Ref = std::shared_ptr<Main_Connection_Basic_Info_Types>;
//	using Main_Connection_Basic_Info_List = std::vector<Main_Connection_Basic_Info_Types>;
//	using Main_Connection_Basic_Info_List_uRef = std::unique_ptr<Main_Connection_Basic_Info_List>;
//
//	/*template <typename From, typename To>
 /*struct Transorms {
		static decltype(auto) FromTo(From& upoint) {

			auto return_type = std::make_unique<To::element_type>();

			std::transform(
				upoint->cbegin(),
				upoint->cend(),
				std::back_inserter(*return_type),
				[](const From::element_type::value_type& transformed) -> decltype(auto)
					{
						return To::element_type::value_type(transformed);
					}
				);
			upoint.reset(nullptr);
			return return_type;
		}
	};*/
}
#endif
