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
	std::shared_ptr<AvailableConnection> _connection_Data; // ������� ��������� ���������
	std::shared_ptr<Connection> _current_Connection; // ������� ������������ ���������

	_ZG_CVT_OPEN_PARAMS _search_Params; // ��������� ������

	void custome_seach_converter();
	void custome_search_controllers(HANDLE&);
};

