// SCAS.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include "DataStructs.h"
#include "Connection.h"
#include "Utils.h"
#include "DataBase.h"
#include "Main_Connection_Info.h"

#define PRINT(text, ...) _tprintf(TEXT(text), ##__VA_ARGS__)

int MainLoop() {
	if (!CheckZGError(ZG_Initialize(ZP_IF_NO_MSG_LOOP), _T("ZG_Initialize")))
		return 0;

	DataBaseLayer base;
	auto conv_list = base.make_Mysql_Basic_Info_List();
	auto uconv_list = Main_Connection_Basic_Info_Types::FromMysqlToMain(conv_list);
	auto users_list = base.make_Mysql_Users_basic_Info_List();
	
	while (1) {
		//ResetEvent(*_globalExitThread);
		PRINT("Enter commant: \n");
		PRINT("1 - Test Connection\n");
		PRINT("2 - Test SearchDevice\n");
		PRINT("3 - Test NotifyThreads\n");
		PRINT("4 - Test Notified Threads\n");
		PRINT("5 - Test Notify Converter\n");
		PRINT("6 - Test LoggerInterface\n");
		PRINT("7 - Test Formate\n");
		PRINT("8 - Test DataBase\n");
		PRINT("10 - GlobalExit\n");
		PRINT("0 - quit\n");
	
		TCHAR szBuf[128];
		if (_tscanf_s(TEXT("%s"), szBuf, _countof(szBuf)) == 1) {
			_tprintf(TEXT("\n"));
			switch (_ttoi(szBuf)) {
			case 1: 
				//EnumConvertors();
				try {
					//Connection::StaticTest();
				}
				catch (const std::exception& error) {
					std::cout << error.what() << "\n";
				}
				//EnumControllers();
				break;
			case 2: 
				try {
					
				}
				catch (const std::exception& error) {
					std::cout << error.what() << "\n";
				}
				break;
			case 3: // TODO Собрать логи
				try {
					//NotifyThreads::StaticTest();
				}
				catch (const std::exception& error) {
					std::cout << error.what() << "\n";
				}
				break;
			case 4: // TODO 
				//Scanning = std::thread([]() {
				//	(new SearchDevice(*new _ZG_CVT_OPEN_PARAMS))->scanNetwork();
				//});
				//Notify = std::thread([]() {
				//	(new NotifyThreads())->beginListning();
				//});
				//Scanning.join();
				//Notify.join();
				break;
			case 5:
				/*_converterInfoListTest->clear();
				NotifyThreads::runListening();
				Connection::StaticTest();*/
				break;
			case 6:
				for (int i = 0; i < 100; i++) {
					Log(MessageTypes::DEBUG) << std::string("hello");
					Log(MessageTypes::ERR) << std::string("error");
					Log(MessageTypes::WARNING) << std::string("warning");
				}

				break;
			case 7:
				std::cout << LoggerFormat::format("% world %  %", "Hello", 123, "Lol");
				std::cout << LoggerFormat::format(std::string("% world"), "Hello");
				break;
			case 8:
				break;
			case  10:
				//SetEvent(*_globalExitThread);
				break;
			case 0:
				return 0;
				
			}
		}
		return 0;
	}
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	Log.start();
	setlocale(LC_ALL, "Russian");
	
	CZGuardLoader oZGL;

	if (!oZGL.IsLoaded()) {
		_tprintf(TEXT("Load ZGuard error 0x%X.\n"), oZGL.m_nStatus);
		getchar();
		return 0;
	}
	
	MainLoop();
	
	Log.stop();
    return 0;
}