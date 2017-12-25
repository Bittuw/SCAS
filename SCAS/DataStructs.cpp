#include "stdafx.h"
#include "DataStructs.h"

const std::unique_ptr<std::list<std::shared_ptr<Connection>>> _convertorsInfoList = std::make_unique<std::list<std::shared_ptr<Connection>>>();
const std::unique_ptr<SpecialList> _converterInfoListTest = std::make_unique<SpecialList>();
const std::unique_ptr<HANDLE> _globalExitThread = std::make_unique<HANDLE>(CreateEvent(NULL, TRUE, FALSE, NULL));
const std::unique_ptr<HANDLE> _globalNotifiedThreadReset = std::make_unique<HANDLE>(CreateEvent(NULL, TRUE, FALSE, NULL));
const std::unique_ptr<std::vector<_ZG_CTR_EVENT>> testList = std::make_unique<std::vector<_ZG_CTR_EVENT>>();

LPCTSTR EventTypeList[] = {
	TEXT(""),
	TEXT("Open button"),				// Открыто кнопкой изнутри
	TEXT("Key not found"),				// Ключ не найден в банке ключей
	TEXT("Open key"),					// Ключ найден, дверь открыта
	TEXT("Key unscheduled"),			// Ключ найден, доступ не разрешен
	TEXT("Open RS485"),					// Открыто оператором по сети
	TEXT("Door is blocked (key)"),		// Ключ найден, дверь заблокирована
	TEXT("Door is blocked (button)"),	// Попытка открыть заблокированную дверь кнопкой
	TEXT("Door is broken"),				// Дверь взломана
	TEXT("Door is left open"),			// Дверь оставлена открытой (timeout)
	TEXT("Passage"),					// Проход состоялся
	TEXT("Sensor 1"),					// Сработал датчик 1
	TEXT("Sensor 2"),					// Сработал датчик 2
	TEXT("Controller is rebooted"),		// Перезагрузка контроллера
	TEXT("Button is disabled"),			// Заблокирована кнопка открывания
	TEXT("Double pass"),				// Попытка двойного прохода
	TEXT("Door opened"),				// Дверь открыта штатно
	TEXT("Door closed"),				// Дверь закрыта
	TEXT("Power off"),					// Пропало питание
	TEXT("Power is on (ElectroControl)"),	// Включение электропитания
	TEXT("Power is off (ElectroControl)"),	// Включение электропитания
	TEXT("Enable the lock (trigger)"),		// Включение замка (триггер)
	TEXT("Disable the lock (trigger)"),	// Отключение замка (триггер)
	TEXT("Changed state Mode"),			// Изменение состояния Режим
	TEXT("Changed state Fire"),			// Изменение состояния Пожара
	TEXT("Changed state Security"),		// Изменение состояния Охраны
	TEXT("Unknown key"),				// Неизвестный ключ
	TEXT("Passage in the gateway"),		// Совершен вход в шлюз
	TEXT("Blocked the entrance to the gateway (busy)"),		// Заблокирован вход в шлюз (занят)
	TEXT("Allowed to enter the gateway"),	// Разрешен вход в шлюз
	TEXT("AntiPassBack"),				// Заблокирован проход (Антипассбек)
	TEXT("Hotel40"),
	TEXT("Hotel41")
};
//
LPCTSTR DirectList[] = {
	TEXT(""),
	TEXT("IN"),   // Вход
	TEXT("OUT")   // Выход
};