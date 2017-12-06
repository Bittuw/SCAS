#pragma once
class NotifiedThread
{
public:
	NotifiedThread(std::shared_ptr<Connection>, std::shared_ptr<HANDLE>);
	~NotifiedThread();

	void startListining();
	bool createNotify();

private:
	std::vector<HANDLE> _waitingFirstArray;
	std::vector<HANDLE> _waitingSecondArray;

	std::weak_ptr<Connection> _localConnection; // Weak_ptr на Connection
	std::weak_ptr<HANDLE> _hConverter; // HANDLE конвертора
	std::weak_ptr<std::vector<std::unique_ptr<HANDLE>>> _hConctrollers; // Массива HANDLE контроллеров

	std::shared_ptr<HANDLE> _e_localExitThread; // Локальный евент выхода
	std::shared_ptr<HANDLE> _e_newInfo; // Событие перезаписи данных
	std::shared_ptr<HANDLE> _e_destroyed; // Событие уничтожения

	std::unique_ptr<HANDLE> _e_getConverterNotify; // Локальный евент события конвертора
	std::vector<HANDLE> _e_getControllersNotifyList; // Массив евентов контроллерова

	void switchFirstEvent(DWORD&);
	void switchSecondEvent(DWORD&);
	void readNotify();

	void waitFirstEvent();
	void waitSecondEvent();
};

