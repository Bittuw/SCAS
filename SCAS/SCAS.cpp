// SCAS.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include "Connection.h"
#include "SearchDevice.h"
#include "SpecialList.h"
#include "NotifyThreads.h"

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

HANDLE g_hNotify = NULL;
HANDLE g_hEvent = NULL;
HANDLE g_hThread = NULL;
BOOL g_fThreadActive;
HANDLE g_hCvt = NULL;
_ZP_DD_NOTIFY_SETTINGS rNS = { 0 };;

HRESULT CheckNotifyMsgs()
{
	HRESULT hr;
	UINT nMsg;
	LPARAM nMsgParam;
	while ((hr = ZG_GetNextMessage(g_hNotify, &nMsg, &nMsgParam)) == S_OK)
	{
		switch (nMsg)
		{
		case ZP_N_INSERT:
		{
			PZP_DDN_PORT_INFO pInfo = (PZP_DDN_PORT_INFO)nMsgParam;
			_tprintf(TEXT("Port insert: %s (%s) %s;\n"),
				pInfo->rPort.szName,
				pInfo->rPort.szFriendly,
				(pInfo->rPort.nFlags & ZP_PIF_BUSY) ? TEXT(" busy") : TEXT(""));
		}
		break;
		case ZP_N_REMOVE:
		{
			PZP_DDN_PORT_INFO pInfo = (PZP_DDN_PORT_INFO)nMsgParam;
			_tprintf(TEXT("Port removed: %s (%s);\n"),
				pInfo->rPort.szName,
				pInfo->rPort.szFriendly);
		}
		break;
		case ZP_N_CHANGE:
		{
			PZP_DDN_PORT_INFO pInfo = (PZP_DDN_PORT_INFO)nMsgParam;
			_tprintf(TEXT("Port changed (%.2Xh): %s (%s)%s;\n"),
				pInfo->nChangeMask,
				pInfo->rPort.szName,
				pInfo->rPort.szFriendly,
				(pInfo->rPort.nFlags & ZP_PIF_BUSY) ? TEXT(" busy") : TEXT(""));
		}
		break;
		}
	}
	if (hr == ZP_S_NOTFOUND)
		hr = S_OK;
	return hr;
}

DWORD WINAPI NotifyThreadProc(LPVOID lpParameter)
{
	while (g_fThreadActive)
	{
		if (WaitForSingleObject(g_hEvent, INFINITE) == WAIT_OBJECT_0)
		{
			ResetEvent(g_hEvent);
			if (g_hNotify != NULL)
				CheckNotifyMsgs();
		}
	}
	return 0;
}

void StartNotifyThread()
{
	if (g_hThread != NULL)
		return;
	DWORD nThreadId;
	g_fThreadActive = TRUE;
	g_hThread = CreateThread(NULL, 0, NotifyThreadProc, NULL, 0, &nThreadId);
}

void StopNotifyThread()
{
	if (g_hThread == NULL)
		return;
	g_fThreadActive = FALSE;
	SetEvent(g_hEvent);
	WaitForSingleObject(g_hThread, INFINITE);
	CloseHandle(g_hThread);
	g_hThread = NULL;
}

void MainLoop() {
	if (!CheckZGError(ZG_Initialize(ZP_IF_NO_MSG_LOOP), _T("ZG_Initialize")))
		return;

	//std::thread Scanning, Notify;

	while (1) {
		PRINT("Enter commant: \n");
		PRINT("1 - Test Connection\n");
		PRINT("2 - Test SearchDevice\n");
		PRINT("3 - TestSpecialList\n");
		PRINT("4 - Test Notified Threads\n");
		PRINT("0 - quit\n");
	
		TCHAR szBuf[128];
		if (_tscanf_s(TEXT("%s"), szBuf, _countof(szBuf)) == 1) {
			_tprintf(TEXT("\n"));
			switch (_ttoi(szBuf)) {
			case 1: 
				//EnumConvertors();
				try {
					Connection::StaticTest();
				}
				catch (const SearchError& error) {
					std::cout << error.what() << "\n";
				}
				//EnumControllers();
				break;
			case 2: 
				try {
					SearchDevice::StaticTest();
				}
				catch (const SearchError& error) {
					std::cout << error.what() << "\n";
				}
				break;
			case 3: // TODO Собрать логи
			//	SpecialList::StaticTest();
				//temp.setList(std::move(*(new std::unique_ptr<std::list<std::shared_ptr<Connection>>>(new std::list<std::shared_ptr<Connection>>))));
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

	//g_hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	//rNS.nNMask = ZP_NF_EXIST | ZP_NF_CHANGE | ZP_NF_IPDEVICE;
	//rNS.hEvent = g_hEvent;


	MainLoop();

    return 0;
}

