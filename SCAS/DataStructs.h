#pragma once

#ifndef DATA_STRUCTS
#define DATA_STRUCTS

#include "DataBaseStructs.h"

namespace Common_Types {

#define Connection_Error_Code_Types \
	X(UNDEFINE, 0) \
	X(SUCCESS, 1) \
	X(CONVERTER_OPEN_FAIL, 2) \
	X(CONVERTER_COMMAND_FAIL, 3) \
	X(CONTROLLER_OPEN_FAIL, 4) \
	X(CONTROLLER_COMMAND_FAIL , 5) \
	X(CONNECTION_FAIL, 6)

	enum class Connection_Error_Code {
#define X(name, value) name = value,
		Connection_Error_Code_Types
#undef X
	};

	static std::string Connection_Error_Code_String[] = {
#define X(name, value) #name,
		Connection_Error_Code_Types
#undef X
	};

	// Common type of return types;
	template <typename Type_Code, typename Return_Data>
	struct Return {
		Type_Code _code;
		std::unique_ptr<Return_Data> _data = nullptr;

		Return(const Type_Code&, std::unique_ptr<Return_Data>&& data)
			: _code(code), _data(std::move(data)) {}
	};

	// Common converter's information types
	using Controller_Info = _ZG_ENUM_IPCVT_INFO; // Common type for mysql
	using Converter_Info_Ref = std::shared_ptr<_ZG_ENUM_IPCVT_INFO>; 
	using Converter_Detail_Info = _ZG_CVT_INFO;
	using Converter_Detail_Info_Ref = std::shared_ptr<Converter_Detail_Info>;
	using Converter_Port_Info = _ZP_PORT_INFO;
	using Converter_Ports_Info_List = std::vector<Converter_Port_Info>;
	using Converter_Ports_Info_List_Ref = std::shared_ptr<Converter_Ports_Info_List>;
	using Converter_Connection_Status = bool;

	// Common controller's information types
	using Controller_Info = _ZG_FIND_CTR_INFO; // Common type for mysql
	using Controllers_Info_List = std::vector<Controller_Info>;
	using Controllers_Info_List_Ref = std::shared_ptr<Controllers_Info_List>;
	using Controller_Detail_Info = _ZG_CTR_INFO;
	using Controllers_Detail_Info_List = std::vector<Controller_Detail_Info>;
	using Controllers_Detail_Info_List_Ref = std::shared_ptr<Controllers_Detail_Info_List>;
	using Controller_Connection_Status = bool;
	using Controllers_Connection_Status_List = std::vector<Controller_Connection_Status>;
	using Controllers_Connection_Status_List_ref = std::shared_ptr<Controllers_Connection_Status_List>;
	using Controller_Index_Read_Write = std::pair<int, int>;;
	using Controllers_Index_Read_Write_List = std::vector<Controller_Index_Read_Write>;
	using Controllers_Index_Read_Write_List_Ref = std::shared_ptr<Controllers_Index_Read_Write_List>;

	using Connection_Mutex_Ref = std::shared_ptr<std::mutex>;
	using Connection_Type = ZP_PORT_TYPE;

	using Global_Connections_List_ref = std::unique_ptr<SpecialList>;


	struct Common_Connection_Data_Type { // TODO проверить работу
	public:
		Controller_Info _converter_info;
		Converter_Ports_Info_List _converter_ports_info_list;
		Controllers_Info_List _controllers_info_list;

		template <typename...Info>
		Common_Connection_Data_Type(Info...args)
			: Common_Connection_Data_Type(args...){}

	protected:
		Common_Connection_Data_Type(Controller_Info controller_info) 
			: _converter_info(controller_info){}
		Common_Connection_Data_Type(Converter_Ports_Info_List converter_ports_info_list) 
			: _converter_ports_info_list(converter_ports_info_list){}
		Common_Connection_Data_Type(Controllers_Info_List controllers_info_list) 
			: _controllers_info_list(controllers_info_list){}
	};

	//Only for Connection
	struct Common_Connection_Inforamtion : public Common_Connection_Data_Type { // TODO make template to get types from parent struct

		Converter_Detail_Info _converter_detail_info;
		Converter_Connection_Status _converter_connection_info;

		Controllers_Detail_Info_List _controllers_detail_info_list;
		Controllers_Connection_Status_List _controllers_connection_status_list;
		Controllers_Index_Read_Write_List _controllers_index_read_write_list;

		Connection_Type _connection_type;

		Connection_Mutex_Ref _mutex;

		Common_Connection_Inforamtion()  {}
	};

}



struct Available_Connection {

	std::shared_ptr<_ZG_ENUM_IPCVT_INFO> converterInfo = nullptr; // Общая информация  о конверторе TODO to binary file
	std::shared_ptr<_ZG_CVT_INFO> converterDetailInfo = nullptr; // Информация после открытия соединения
	std::shared_ptr<std::vector<_ZP_PORT_INFO>> converterPorts = nullptr; // Список портов конвертора TODO to binary file
	bool converterStatus = false; // Создано ли соединение
	
	std::shared_ptr<std::vector<_ZG_FIND_CTR_INFO>> controllersInfo = nullptr; // Список контроллеров TODO to binary file
	std::shared_ptr<std::vector<_ZG_CTR_INFO>> controllersDetailInfo = nullptr; // Информация после открытия соединения
	std::shared_ptr<std::vector<bool>> controllersStatus = nullptr; // Доступность контроллера
	std::shared_ptr<std::vector<std::pair<int, int>>> controllersIndexWriteRead = nullptr; // Список указателей индеков записи/чтения

	ZP_PORT_TYPE portType; // Тип подключения

	std::shared_ptr<std::mutex> mutex = nullptr; // Мьютетс доступа

	Available_Connection(const Available_Connection&) = default;


	Available_Connection() :
		converterInfo(new _ZG_ENUM_IPCVT_INFO),
		converterDetailInfo(new _ZG_CVT_INFO),
		converterPorts(new  std::vector<_ZP_PORT_INFO>),
		controllersInfo(new std::vector<_ZG_FIND_CTR_INFO>),
		controllersStatus(new std::vector<bool>),
		controllersDetailInfo(new std::vector<_ZG_CTR_INFO>),
		controllersIndexWriteRead(new std::vector<std::pair<int, int>>),
		mutex(new std::mutex)
	{
		ZeroMemory(&*converterInfo, sizeof(*converterInfo));
		converterInfo->cbSize = sizeof(_ZG_ENUM_IPCVT_INFO);
		converterPorts->resize(2);
	}

	~Available_Connection() {
		converterInfo = nullptr;
		converterDetailInfo = nullptr;
		converterPorts = nullptr;
		controllersInfo = nullptr;
		controllersStatus = nullptr;
		controllersDetailInfo = nullptr;
		controllersIndexWriteRead = nullptr;
		mutex = nullptr;
	}

	bool operator< (const Available_Connection &right) {
		return converterInfo->nSn < right.converterInfo->nSn;
	}
};

extern const std::unique_ptr<SpecialList> _converterInfoListTest;
extern const std::unique_ptr<HANDLE> _globalExitThread;
extern const std::unique_ptr<HANDLE> _globalNotifiedThreadReset;
//extern const std::unique_ptr<std::vector<_ZG_CTR_EVENT>> testList;

extern LPCTSTR EventTypeList[];
extern LPCTSTR DirectList[];
#endif