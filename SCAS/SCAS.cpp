// SCAS.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"


#define PRINT(text, ...) _tprintf(TEXT(text), ##__VA_ARGS__)


#define sptr(T) std::shared_ptr<T>
#define mvector(T) std::vector<T>
#define mpair(T, N) std::pair<T, N>

const ZP_PORT_TYPE CvtPortType = ZP_PORT_IP;

sptr(mvector(mpair(_ZG_ENUM_IPCVT_INFO, sptr(_ZP_PORT_INFO)))) cvtInfoArr;

void EnumControllers() {
	for each (mpair(_ZG_ENUM_IPCVT_INFO, sptr(_ZP_PORT_INFO)) convertor in *cvtInfoArr.get())
	{
		for (int nPort = 0; nPort < 2; nPort++)
		
		try {
			_ZG_CVT_OPEN_PARAMS rOp;
			ZeroMemory(&rOp, sizeof(rOp));
			rOp.nType = CvtPortType;
			rOp.pszName = convertor.second->szName;
		}
		catch (std::exception_ptr e) {

		}
	}
}

void EnumConvertors() {

	HANDLE hSearch;
	_ZP_SEARCH_PARAMS rSP;
	ZeroMemory(&rSP, sizeof(rSP));
	cvtInfoArr = 
		sptr(
			mvector(
				mpair(_ZG_ENUM_IPCVT_INFO, sptr(_ZP_PORT_INFO))
			)
		) (new mvector(mpair(_ZG_ENUM_IPCVT_INFO, sptr(_ZP_PORT_INFO))));

	if (!CheckZGError(ZG_SearchDevices(&hSearch, &rSP, FALSE, TRUE), _T("ZG_SearchDevices")))
		return;

	try {

		HRESULT hr;
		_ZP_PORT_INFO cvtPortsInfo[2];
		PZP_PORT_INFO cvtPortInfo;
		_ZG_ENUM_IPCVT_INFO cvtInfo;
		INT_PTR nPortCount;
	
		cvtInfo.cbSize = sizeof(_ZG_ENUM_IPCVT_INFO);

		while ((hr = ZG_FindNextDevice(hSearch, &cvtInfo, cvtPortsInfo, _countof(cvtPortsInfo), &nPortCount)) == S_OK) {

			cvtInfoArr->push_back(std::make_pair(cvtInfo, sptr(_ZP_PORT_INFO) (cvtPortsInfo)));
			
			/*if (cvtInfo.cbSize == sizeof(_ZG_ENUM_IPCVT_INFO)) {
				_tprintf(TEXT("%d. %s, s/n: %d, v%d.%d.%d, mode: %s;\n"),
					nDevCount,
					CvtTypeStrs[cvtInfo.nType],
					cvtInfo.nSn,
					(cvtInfo.nVersion & 0xff), (cvtInfo.nVersion >> 8) & 0xff, (cvtInfo.nVersion >> 16) & 0xff,
					GuardModeStrs[cvtInfo.nMode]);
			}
			else {
				_tprintf(TEXT("%d. model: %d, s/n: %d, v%d.%d.%d;\n"),
					nDevCount,
					cvtInfo.nModel,
					cvtInfo.nSn,
					(cvtInfo.nVersion & 0xff), (cvtInfo.nVersion >> 8) & 0xff, (cvtInfo.nVersion >> 16) & 0xff);
			}
			for (INT_PTR i = 0; i < nPortCount; i++)
			{
				cvtPortInfo = &cvtPortsInfo[i];
				_tprintf(TEXT("\t%s %s (%s); %s\n"),
					PortTypeStrs[cvtPortInfo->nType],
					cvtPortInfo->szName,
					cvtPortInfo->szFriendly,
					(cvtPortInfo->nFlags & ZP_PIF_BUSY) ? TEXT("busy") : TEXT(""));
			}*/
		}
		if (!CheckZGError(hr, _T("ZG_FindNextDevice")))
			return;
	} catch (std::exception e){

	}
	
	ZG_CloseHandle(hSearch);
	_tprintf(TEXT("--------------\n"));

	if (cvtInfoArr->size() > 0) {
		_tprintf(TEXT("Found %d converters.\n\n"), cvtInfoArr->size());
		PRINT("Found %d converters.\n\n", cvtInfoArr->size());
	}
	else
		_tprintf(TEXT("Converters not found.\n\n"));
	
}

void MainLoop() {
	if (!CheckZGError(ZG_Initialize(ZP_IF_NO_MSG_LOOP), _T("ZG_Initialize")))
		return;
	while (1) {
		PRINT("Enter commant: \n");
		PRINT("1 - Scan Network\n");
		PRINT("2 - Connect\n");
		PRINT("3 - \n");
		PRINT("4 - \n");
		PRINT("0 - quit\n");
	
		TCHAR szBuf[128];
		if (_tscanf_s(TEXT("%s"), szBuf, _countof(szBuf)) == 1) {
			_tprintf(TEXT("\n"));
			switch (_ttoi(szBuf)) {
			case 1: // TODO сделать анализ сети (Найти конверторы и контроллеры на них) и собрать все в массив
				EnumConvertors();
				//EnumControllers();
				break;
			case 2: // TODO Подписатья на контроллеры для сбора событий онлайн
				break;
			case 3: // TODO Собрать логи с конверторов и контроллеров
				break;
			case 4: // TODO 
				break;
			case 0:
				return;
			default:
				PRINT("Invalid command.\n\n");
				break;
			}
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Russian");

	CZGuardLoader oZGL;

	if (!oZGL.IsLoaded()) {
		_tprintf(TEXT("Load ZGuard error 0x%X.\n"), oZGL.m_nStatus);
		getchar();
		return 0;
	}

	MainLoop();

    return 0;
}

