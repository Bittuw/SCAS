#pragma once
 
class FindDevices
{
private:
	struct mConverter {
		_ZG_ENUM_IPCVT_INFO mCurrentConvertor; // ����� ���������� � �����������
		_ZP_PORT_INFO mCurrentConvertorPorts[2]; // ����� ���������� � ������ ���������� TODO to vector
		std::vector<_ZG_FIND_CTR_INFO> mCurrentControllers; // ������������ � ���������� �����������
	}; // ��������� ������

	mConverter *mCurrentConverterStruct; // ������� �������������� ���������
	std::unique_ptr<std::vector<mConverter>> mConvertorsList; // ������ ������������ �����������

	const ZP_PORT_TYPE mConvertorPortType = ZP_PORT_IP;
	

	bool findConvertor(HANDLE*); // ����� �����������
	HANDLE tryOpenConvertor(); // ������� ������ ���������
	void findControllers(HANDLE*); // ����� ������������ � ����������

	int numberOfConverters = 0; // ���������� ������������ �����������
	int numberOfControllers = 0; // ���������� 

public:
	FindDevices();
	~FindDevices();

	typedef mConverter TypeOfData; // ��� ��� ������� ������������

	bool beginScanNetwork(const _ZP_SEARCH_PARAMS); // ������ ������������ ����, rescan
	bool beginScanConverter();
	std::vector<mConverter> getVector(); // �������� ������ �����������
	int getNumberOfConverters();
	int getNumberOfControllers();

};

