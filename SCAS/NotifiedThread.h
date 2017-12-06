#pragma once

class NotifiedThread
{
public:
	NotifiedThread(std::shared_ptr<Connection>, std::shared_ptr<HANDLE>);
	~NotifiedThread();
	///////////////
	void startListining();
	bool createNotifies();
	void createNotify(PZG_FIND_CTR_INFO);
	//void closeNotifies();
	///////////////

private:
	std::vector<HANDLE> _waitingConstArray;
	std::vector<HANDLE> _waitingVariableArray;
	std::unique_ptr<std::vector<HANDLE>> _waitingArray;

	std::weak_ptr<Connection> _localConnection; // Weak_ptr на Connection
	std::weak_ptr<HANDLE> _hConverter; // HANDLE конвертора
	std::weak_ptr<std::vector<HANDLE>> _hConctrollers; // Массива HANDLE контроллеров

	std::shared_ptr<HANDLE> _e_localExitThread; // Локальный евент выхода
	std::shared_ptr<HANDLE> _e_newInfo; // Событие перезаписи данных
	std::shared_ptr<HANDLE> _e_destroyed; // Событие уничтожения

	std::unique_ptr<HANDLE> _e_getConverterNotify; // Локальный евент события конвертора
	std::vector<HANDLE> _e_getControllersNotifyList; // Массив евентов контроллерова

	void readConvertorNotify();
	void readControllerNotify();

	void parceConverterNotify();
	void parceControllerNotify();

	///////////////
	void clearNotifyList();
	void getNewPointers(std::shared_ptr<Connection>&);
	void refreshWaitingArray();
	///////////////
};

