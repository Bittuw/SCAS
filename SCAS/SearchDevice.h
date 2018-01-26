#pragma once
struct AvailableConnection;

template <typename Ret_data>
struct Return_Data {
	ErrorCode code = NotDefined;
	std::shared_ptr<Ret_data> data = nullptr;
};

using AV_list = std::vector<std::shared_ptr<AvailableConnection>>;

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
	std::shared_ptr<AvailableConnection> _connection_Data; // Текущий найденный конвертер
	std::shared_ptr<Connection> _current_Connection; // Текущий подключенный конвертер

	_ZG_CVT_OPEN_PARAMS _search_Params; // Параметры поиска

	void custome_seach_converter();
	void custome_search_controllers(HANDLE&);
};

