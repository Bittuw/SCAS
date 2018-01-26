#pragma once
struct Available_Connection;

template <typename Ret_data>
struct Return_Data {
	Connection_Error_Code _code;
	std::shared_ptr<Ret_data> _data = nullptr;

	Return_Data(const Connection_Error_Code& code, std::shared_ptr<Ret_data>& data)
		: _code(code), _data(data) {}
};

using AV_list = std::vector<std::shared_ptr<Available_Connection>>;

class SearchDevice 
{

	//TODO Главная задача: вернуть список AV

public:
	SearchDevice(_ZG_CVT_OPEN_PARAMS);
	~SearchDevice();

	//SearchDevice_RetrurnData<AV_list> scanNetwork();


#ifdef _DEBUG
	static bool StaticTest();
#endif

private:
	
	HANDLE _handle_Search; // Дескриптор поиска
	std::shared_ptr<Available_Connection> _connection_Data; // Текущий найденный конвертер
	std::shared_ptr<Connection> _current_Connection; // Текущий подключенный конвертер

	_ZG_CVT_OPEN_PARAMS _search_Params; // Параметры поиска

	static void custome_seach_converter();
	static void custome_search_controllers(HANDLE&);
};

