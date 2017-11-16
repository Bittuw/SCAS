#include "stdafx.h"
#include "FindDevices.h"

/// Инициализация ссылок
FindDevices::FindDevices()
{
	this->mCurrentConverterStruct = new mConverter();
	ZeroMemory(&this->mCurrentConverterStruct, sizeof(mCurrentConverterStruct));
	this->mConvertorsList = std::make_unique<std::vector<mConverter>>();
}


FindDevices::~FindDevices()
{
}


bool FindDevices::beginScanNetwork(const _ZP_SEARCH_PARAMS searchParams) {
	// TODO log trace
	HANDLE hSearch;

	if (!CheckZGError(ZG_SearchDevices(&hSearch, &((_ZP_SEARCH_PARAMS &)searchParams), FALSE, TRUE), _T("ZG_SearchDevices"))) {
		return FALSE; // TODO log trace
	}
	// TODO log trace
	if (findConvertor(&hSearch)) {
		// TODO log trace
		ZG_CloseHandle(hSearch);
		return TRUE;
	} 
	else {
		// TODO log trace
		ZG_CloseHandle(hSearch);
		return FALSE;
	}
}


bool FindDevices::findConvertor(HANDLE *hSearch) {
	// TODO log trace
	HRESULT rFoundConvector;
	INT_PTR nPortCount;
	
	while ((rFoundConvector = ZG_FindNextDevice(
		*hSearch, 
		&(this->mCurrentConverterStruct->mCurrentConvertor), 
		this->mCurrentConverterStruct->mCurrentConvertorPorts, 
		_countof(this->mCurrentConverterStruct->mCurrentConvertorPorts),
		&nPortCount)) == S_OK) 
	{

		HANDLE hOpenedConvector = tryOpenConvertor();

		// TODO log trace
		if (hOpenedConvector != NULL) {
			findControllers(&hOpenedConvector);
		}
		else {
			// TODO log trace
		}
	
		this->mConvertorsList->push_back(
			*mCurrentConverterStruct
		);
	}

	if (!this->mConvertorsList->size())
		return TRUE;
	return FALSE;
	// TODO log trace
}


HANDLE FindDevices::tryOpenConvertor() {
	// TODO log trace
	for (int i = 0; i < 2; i++) {
		if (!(this->mCurrentConverterStruct->mCurrentConvertorPorts[i].nFlags & ZP_PIF_BUSY & ZP_PIF_USER)) {

			HANDLE openConvector;
			_ZG_CVT_OPEN_PARAMS openConvectorParams;
			ZeroMemory(&openConvectorParams, sizeof(openConvectorParams));
			openConvectorParams.pszName = this->mCurrentConverterStruct->mCurrentConvertorPorts[i].szName;
			openConvectorParams.nType = this->mConvertorPortType;

			if (CheckZGError(ZG_Cvt_Open(&openConvector, &openConvectorParams, NULL), _T("ZG_Cvt_Open")))
				return openConvector;

		}
	}
	// TODO log trace
	return nullptr;
}


void FindDevices::findControllers(HANDLE *mOpenedConvector) {
	// TODO log trace
	INT MaxCount = 0;
	HRESULT hController;
	_ZG_FIND_CTR_INFO mControllerInfo;
	if (!CheckZGError(ZG_Cvt_SearchControllers(*mOpenedConvector, MaxCount, NULL), _T("ZG_Cvt_SearchControllers")));
	
	while ((hController = ZG_Cvt_FindNextController(*mOpenedConvector, &(_ZG_FIND_CTR_INFO&)mControllerInfo)) == S_OK) {
		// TODO log trace
		this->mCurrentConverterStruct->mCurrentControllers.push_back(mControllerInfo);
		numberOfControllers++;
	}

	// TODO log trace
}


std::vector<FindDevices::mConverter> FindDevices::getVector() {
	// TODO log trace
	return *(this->mConvertorsList);
	// TODO log trace
}


int FindDevices::getNumberOfConverters() {
	// TODO log trace
	if (this->numberOfConverters == NULL)
		this->numberOfConverters = this->mConvertorsList->size();
	return this->numberOfConverters;
	// TODO log trace
}


int FindDevices::getNumberOfControllers() {
	// TODO log trace
	return numberOfControllers;
}