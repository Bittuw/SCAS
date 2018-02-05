#pragma once

#ifndef SEARCH_DEVICE
#define SERACH_DEVICE

#include "DataStructs.h"

namespace Seach_Device {

	using namespace Zguard_Types;

	enum class Seach_Type {
		Search_Client_Device,
		Search_Server_Device
	};

	class Basic_Search_Device {
	protected:
		Basic_Search_Device(const _ZP_SEARCH_PARAMS& search_params, const ZP_PORT_TYPE& port_type) 
			:
			_port_type(port_type),
			_search_params(search_params)
		{}
		virtual void search_converters(const Zguard_Basic_Info_List_Ref&) { throw std::logic_error("Need to implement this method!"); };
		virtual void search_controllers(const Zguard_Basic_Info_List_Ref&) { throw std::logic_error("Need to implement this method!"); };
		
		ZP_PORT_TYPE _port_type;
		_ZP_SEARCH_PARAMS _search_params;

	public:
		Zguard_Basic_Info_List_Ref execute();
		static std::unique_ptr<Basic_Search_Device> create_searcher_object(const Seach_Type&, _ZP_SEARCH_PARAMS = {});
		virtual ~Basic_Search_Device() {}

	};

	class Search_Client_Device : public Basic_Search_Device {
		Search_Client_Device(const _ZP_SEARCH_PARAMS& search_params, const ZP_PORT_TYPE& port_type);
	};

	class Search_Server_Device : public Basic_Search_Device {

		Search_Server_Device(const _ZP_SEARCH_PARAMS& search_params, const ZP_PORT_TYPE& port_type)
			: 
			Basic_Search_Device(search_params, port_type)
		{};

		void search_converters(const Zguard_Basic_Info_List_Ref&) override;
		void search_controllers(const Zguard_Basic_Info_List_Ref&) override;

	private:
		bool open_converter(const HANDLE&, const _ZG_CVT_INFO&, const Zguard_Open_Params&); // TODO

	};
}
#endif
