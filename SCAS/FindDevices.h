#pragma once
 
class FindDevices
{
private:
	struct mConverter {
		_ZG_ENUM_IPCVT_INFO mCurrentConvertor; // Общая информация о конвертореы
		_ZP_PORT_INFO mCurrentConvertorPorts[2]; // Общая информация о портах конвертора TODO to vector
		std::vector<_ZG_FIND_CTR_INFO> mCurrentControllers; // Подключенные к конвертору контроллеры
	}; // Структура данных

	mConverter *mCurrentConverterStruct; // Текущий обрабатываемый конвертер
	std::unique_ptr<std::vector<mConverter>> mConvertorsList; // Список обработанных конверторов

	const ZP_PORT_TYPE mConvertorPortType = ZP_PORT_IP;
	

	bool findConvertor(HANDLE*); // Поиск конверторов
	HANDLE tryOpenConvertor(); // Попытка занять конвертер
	void findControllers(HANDLE*); // Поиск контроллеров в конверторе

	int numberOfConverters = 0; // Количество обработанных конвертовро
	int numberOfControllers = 0; // Количество 

public:
	FindDevices();
	~FindDevices();

	typedef mConverter TypeOfData; // Тип для внешних зависимостей

	bool beginScanNetwork(const _ZP_SEARCH_PARAMS); // Начало сканирования сети, rescan
	bool beginScanConverter();
	std::vector<mConverter> getVector(); // Получить список конверторов
	int getNumberOfConverters();
	int getNumberOfControllers();

};

