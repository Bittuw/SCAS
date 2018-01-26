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

	//TODO ������� ������: ������� ������ AV

public:
	SearchDevice(_ZG_CVT_OPEN_PARAMS);
	~SearchDevice();

	//SearchDevice_RetrurnData<AV_list> scanNetwork();


#ifdef _DEBUG
	static bool StaticTest();
#endif

private:
	
	HANDLE _handle_Search; // ���������� ������
	std::shared_ptr<Available_Connection> _connection_Data; // ������� ��������� ���������
	std::shared_ptr<Connection> _current_Connection; // ������� ������������ ���������

	_ZG_CVT_OPEN_PARAMS _search_Params; // ��������� ������

	static void custome_seach_converter();
	static void custome_search_controllers(HANDLE&);
};

