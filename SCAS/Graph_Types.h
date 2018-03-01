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

	class Graph_Converter;
	class Graph_Controller;
	class Graph_User;
	class Graph_Group;

	///
	/// Declarations of main types's fields
	///

	using Graph_Converter_sRef = std::shared_ptr<Graph_Converter>; // Указатель на конвертер
	using Graph_Controller_sRef = std::shared_ptr<Graph_Controller>; // Указатель на контроллер
	using Graph_User_sRef = std::shared_ptr<Graph_User>; // Указатель на пользователя
	using Graph_Group_sRef = std::shared_ptr<Graph_Group>; // Указатель на группу

	using Graph_Converters_sRefs = std::vector<Graph_Converter_sRef>; // Список указателей на конверторы
	using Graph_Controlles_sRefs = std::vector<Graph_Controller_sRef>; // Список указателей на контроллеры
	using Graph_Users_sRefs = std::vector<Graph_User_sRef>; // Список указателей на пользователей
	using Graph_Groups_sRefs = std::vector<Graph_Group_sRef>; // Список указателй на группы

	using Grapg_Group_Pair = std::pair<unsigned int, Graph_Group_sRef>; // Пара "позиция:группа"
	using Graph_Groups_Pairs_sRefs = std::vector<std::pair<unsigned int, Graph_Group_sRef>>; // Список пар "позиция:группа"
	//using Graph_Converters_sRefs_Set = std::set<Graph_Converter_sRef>;

	//class Graph_Converter {
	//public:
	//	Converter_sRef _converter_info_ref;
	//	Graph_Controlles_sRefs _controllers_list;
	//	Graph_Converter(const Converter_sRef& converter_info) 
	//		: // Построение
	//		_converter_info_ref(converter_info)
	//	{};
	//	bool operator<(const Graph_Converter& right) {
	//		return this->_converter_info_ref->_nSn < right._converter_info_ref->_nSn;
	//	}
	//};

	//class Graph_Controller {
	//public:
	//	Controller_sRef _controller_info_ref;
	//	Graph_Converter_sRef _converter_ref;
	//	Graph_Groups_Pairs_sRefs _groups_pairs_list;
	//	Graph_Controller() = delete;
	//	Graph_Controller(const Controller_sRef& controller_info)
	//		: // Построение без связывания
	//		_controller_info_ref(controller_info)
	//	{}
	//	Graph_Controller(const Controller_sRef& controller_info, const Graph_Converter_sRef& converter) 
	//		: // Построение с связыванием
	//		_controller_info_ref(controller_info),
	//		_converter_ref(converter)
	//	{}
	//};

	//class Graph_User {
	//public:
	//	User_sRef _user_ref;
	//	Graph_Group_sRef _group_ref;
	//	Graph_User() = delete;
	//	Graph_User(const User_sRef& user_info)
	//		: // Потсроение без связывание
	//		_user_ref(user_info)
	//	{}
	//	Graph_User(const User_sRef& user_info, const Graph_Group_sRef& group) 
	//		: // Построение с связывание
	//		_user_ref(user_info),
	//		_group_ref(group)
	//	{}
	//};
	
	//class Graph_Group {
	//public:
	//	Group_sRef _group_ref;
	//	Graph_Controlles_sRefs _controllers_list;
	//	Graph_Users_sRefs _users_list;
	//	Graph_Group(const Group_sRef& group_info) 
	//		: // Построение
	//		_group_ref(group_info)
	//	{}
	//};

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

	template <typename P, typename D, typename C>
	class Graph_Point {
	public:
		P _parent;
		D _data;
		C _child;

		using _parent_type = P;
		using _data_type = D;
		using _child_type = C;

		Graph_Point(const D& data) : _data(data){}
		virtual ~Graph_Point() = default;
	};

	template <typename D, typename C>
	class Graph_Zero_Parent : public Graph_Point<nullptr_t, D, C> {
	public:
		Graph_Zero_Parent(const D& data) : Graph_Point(data) {}
	};

	template <typename P, typename D>
	class Graph_Zero_Child : public Graph_Point<P, D, nullptr_t> {
	public:
		Graph_Zero_Child(const D& data) : Graph_Point(data) {}
	};

	class Graph_Converter : public Graph_Zero_Parent<
		Converter_sRef, Graph_Controlles_sRefs> {
	public:
		Graph_Converter(const Converter_sRef& converter_info) 
			: // Построение
			Graph_Zero_Parent(converter_info)
		{};
	};

	class Graph_Controller : public Graph_Point
		<Graph_Converter_sRef, Controller_sRef, Graph_Groups_Pairs_sRefs> {
	public:
		Graph_Controller(const Controller_sRef& controller_info)
			:
			Graph_Point(controller_info)
		{}
	};

	class Graph_Group : public Graph_Point
		<Graph_Controlles_sRefs, Group_sRef, Graph_Users_sRefs> {
	public:
		Graph_Group(const Group_sRef& group_info)
			:
			Graph_Point(group_info)
		{}
	};

	class Graph_User : public Graph_Zero_Child
		<Graph_Group_sRef, User_sRef> {
	public:
		Graph_User(const User_sRef& user_info)
			: // Построение
			Graph_Zero_Child(user_info)
		{}
	};

	/*template <typename DList, typename GList, typename F>
	inline static void transform_one(DList& dlist, GList& glist, const F& tr) {
		dlist.emplace_back(new DList::value_type::element_type(tr));
		glist.emplace_back(new DList::value_type::element_type(dlist.back()));
	}*/

	// Трансформируем иходные списки
	template <
		typename From, typename To, 
		typename F = From::value_type, 
		typename T = To::value_type::element_type,
		typename Arg = T::_data_type::element_type>
	inline static decltype(auto) transform(const From& flist, To& tlist) {
		auto start_new = tlist.cend();
		std::transform(
			flist.cbegin(), 
			flist.cend(), 
			std::back_inserter(tlist), 
			[](const F& felement) 
		{ return std::make_shared<T>(std::make_shared<Arg>(felement)); }
		);
		return start_new;
	}

	class Building {
		
		template <typename List, typename Parametr>
		inline static decltype(auto) build_one(List& list, const Parametr& parametr) {
			list.emplace_back(new List::value_type::element_type(parametr));
			return list.back();
		}

		template <typename Parent, typename Child>
		inline static void bind_one_one(const Parent& parent, const Child& child, const unsigned int position) { // Специально для controller <-> group
			Child::element_type::_parent_type::const_iterator result;
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
			parent->_child.emplace_back(position, child);
			child->_parent.push_back(parent);
		}

		template <typename Parent, typename Child>
		inline static void bind_many_one(const Parent& parent, const Child& child) /*Один родитель - много детей*/ {
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
		}

	public:
		template <
			typename PList, typename CList
		>
		static void build(
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
	};
	

	//template <typename PElement, typename CElement>
	//inline static void bind_many_one(const PElement& parent, const CElement& child) /*Один родитель - много детей*/ { 
	//	if (child->_parent != nullptr)
	//		throw Programm_Exceptions(
	//			LoggerFormat::format(
	//					"Chile element already has parent: class parent: '%' with id '%', class child: '%' with id '%'",
	//					typeid(parent).name(),
	//					parent->_data->_id,
	//					typeid(child).name(),
	//					child->_data->_id
	//				)
	//		);
	//	parent->_child.push_back(child);
	//	child->_parent = parent;
	//}

	
	/*template <typename P, typename CList>
	static void bind_one_many(const P& pElement, const CList& clist) {
	
		static_assert(std::is_function<F>::value, "Last parametr is not a boolean functor!");
	
		CList::const_iterator result;
		auto start_from = clist.cbegin();

		while ((result = std::find_if(start_from, clist.cend(), [&](const CList::value_type& cElement) { pElement; }) != clist.cend()))
		{
			start_from = result + 1;
			bind_one_one(element, *result);
		}
	}*/


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
