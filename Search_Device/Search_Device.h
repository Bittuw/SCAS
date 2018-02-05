#ifndef SEARCH_DEVICE
#define SERACH_DEVICE

#ifdef SEARCH_DEVICE_EXPORTS	
#define SEARCH_DEVICE_API __declspec(dllexport)
#else
#define SEARCH_DEVICE_API __declspec(dllimport)
#endif

#include "Zguard_Types.h"

namespace Seach_Device {

	using namespace Zguard_Basic_Info_Types;

	enum class Seach_Type {
		Search_Client_Device,
		Search_Server_Device
	};
}

class SEARCH_DEVICE_API Basic_Search_Device {
protected:
	Basic_Search_Device(const _ZP_SEARCH_PARAMS& search_params, const ZP_PORT_TYPE& port_type)
		:
		_port_type(port_type),
		_search_params(search_params)
	{}
	virtual void search_converters(Seach_Device::Zguard_Basic_Info_List_uRef&) { throw std::logic_error("Need to implement this method!"); };
	virtual void search_controllers(Seach_Device::Zguard_Basic_Info_List_uRef&) { throw std::logic_error("Need to implement this method!"); };

	ZP_PORT_TYPE _port_type;
	_ZP_SEARCH_PARAMS _search_params;

public:
	Seach_Device::Zguard_Basic_Info_List_Ref execute();
	static std::unique_ptr<Basic_Search_Device> create_searcher_object(const Seach_Device::Seach_Type&, _ZP_SEARCH_PARAMS = {});
	virtual ~Basic_Search_Device() {}

};


class SEARCH_DEVICE_API Search_Client_Device : public Basic_Search_Device { // TODO сделать ожидание потока поиска клиентов и нужен тест
public:
	Search_Client_Device(const _ZP_SEARCH_PARAMS& search_params, const ZP_PORT_TYPE& port_type)
		:Basic_Search_Device(search_params, port_type)
	{};
};


class SEARCH_DEVICE_API Search_Server_Device : public Basic_Search_Device { // TODO нужен тест
public:
	Search_Server_Device(const _ZP_SEARCH_PARAMS& search_params, const ZP_PORT_TYPE& port_type)
		:
		Basic_Search_Device(search_params, port_type)
	{};
protected:
	void search_converters(Seach_Device::Zguard_Basic_Info_List_uRef&) override;
	void search_controllers(Seach_Device::Zguard_Basic_Info_List_uRef&) override;

private:
	bool open_converter(Seach_Device::Zguard_Basic_Info&, HANDLE&, _ZG_CVT_INFO&, Seach_Device::Zguard_Open_Params&);
};
#endif

