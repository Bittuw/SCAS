// SCAS.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"


#define PRINT(text) _tprintf(TEXT(text))

const ZP_PORT_TYPE CvtPortType = ZP_PORT_IP;

std::vector<_ZG_ENUM_CVT_INFO> cvtInfoArr;

void EnumConvertors() {
	HANDLE hSearch;
	INT_PTR nDevCount = 0;
	_ZP_SEARCH_PARAMS rSP;
	cvtInfoArr = * new std::vector<_ZG_ENUM_CVT_INFO>;
	ZeroMemory(&rSP, sizeof(rSP));

	if (!CheckZGError(ZG_SearchDevices(&hSearch, &rSP, FALSE, TRUE), _T("ZG_SearchDevices")))
		return;

	__try {

		HRESULT hr;
		_ZP_PORT_INFO cvtPortsInfo[2];
		PZP_PORT_INFO cvtPortInfo;
		_ZG_ENUM_CVT_INFO cvtInfo;
		INT_PTR nPortCount;
	
		cvtInfo.cbSize = sizeof(_ZG_ENUM_CVT_INFO);

		while ((hr = ZP_FindNextDevice(hSearch, &cvtInfo, cvtPortsInfo, _countof(cvtPortsInfo), &nPortCount)) == S_OK) {
			nDevCount++;

			cvtInfoArr.push_back(cvtInfo);

			if (cvtInfo.cbSize == sizeof(_ZG_ENUM_CVT_INFO)) {
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
					(cvtInfo.nVersion & 0xff), (cvtInfo.nVersion >> 8) & 0xff, (cvtInfo.nVersion >> 16) & 0xf);
			}
			for (INT_PTR i = 0; i < nPortCount; i++)
			{
				cvtPortInfo = &cvtPortsInfo[i];
				_tprintf(TEXT("\t%s %s (%s); %s\n"),
					PortTypeStrs[cvtPortInfo->nType],
					cvtPortInfo->szName,
					cvtPortInfo->szFriendly,
					(cvtPortInfo->nFlags & ZP_PIF_BUSY) ? TEXT("busy") : TEXT(""));
			}
		}
		if (!CheckZGError(hr, _T("ZP_FindNextDevice")))
			return;
	}
	__finally {
		ZG_CloseHandle(hSearch);
		_tprintf(TEXT("--------------\n"));
		if (nDevCount > 0)
			_tprintf(TEXT("Found %d converters.\n"), nDevCount);
		else
			_tprintf(TEXT("Converters not found.\n"));
	}
}

inline void PrintMenu() {
	PRINT("Enter commant: \n");
	PRINT("1 - EnumConvertors\n");
	PRINT("2 - EnumControllers\n");
	PRINT("3 - \n");
	PRINT("4 - \n");
	PRINT("0 - quit\n");

	TCHAR szBuf[128];
	if (_tscanf_s(TEXT("%s"), szBuf, _countof(szBuf)) == 1) {
		_tprintf(TEXT("\n"));
		switch (_ttoi(szBuf)) {
		case 1:
			EnumConvertors();
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 0:
			return;
		default:
			PRINT("Invalid command.\n");
		}
	}
}	


void MainLoop() {
	if (!CheckZGError(ZG_Initialize(ZP_IF_NO_MSG_LOOP), _T("ZG_Initialize")))
		return;
	while (1) {
		PrintMenu();
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

