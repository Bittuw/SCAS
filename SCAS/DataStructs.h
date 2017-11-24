#pragma once

class Connection;

struct AvailableConnection { // TODO ��������� ������ ��� MainInfo
	_ZG_ENUM_IPCVT_INFO* converterInfo; // ����� ����������  � ����������
	std::vector<_ZP_PORT_INFO>* converterPorts; // ������ ������
	mutable std::vector<_ZG_FIND_CTR_INFO>* controllersInfo; // ������ �����������
	ZP_PORT_TYPE* portType; // ��� �����������
	//_ZG_CVT_OPEN_PARAMS openConverterParams; // TODO ��������� ����������� (����������� ������)
	Connection* connection; // ��������� ���������� (��� ������ � �����������/�����������)
};

static const std::unique_ptr<std::vector<AvailableConnection>> _convertorsInfoList = std::unique_ptr<std::vector<AvailableConnection>>(new std::vector<AvailableConnection>);