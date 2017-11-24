#pragma once

class Connection;

struct AvailableConnection { // TODO возможная замена для MainInfo
	_ZG_ENUM_IPCVT_INFO* converterInfo; // Общая информация  о конверторе
	std::vector<_ZP_PORT_INFO>* converterPorts; // Список портов
	mutable std::vector<_ZG_FIND_CTR_INFO>* controllersInfo; // Список конверторов
	ZP_PORT_TYPE* portType; // Тип подключения
	//_ZG_CVT_OPEN_PARAMS openConverterParams; // TODO параметры подключения (Возможность задать)
	Connection* connection; // Интерфейс соединение (Для работы с конвертором/контроллеро)
};

static const std::unique_ptr<std::vector<AvailableConnection>> _convertorsInfoList = std::unique_ptr<std::vector<AvailableConnection>>(new std::vector<AvailableConnection>);