#pragma once

#ifndef UTIL
#define UTIL

#include <stringapiset.h>

namespace Utils {
	inline void WideToMulti(const wchar_t* from, size_t& s_from, char* to, size_t& s_to) {
		WideCharToMultiByte(CP_ACP, 0, from, s_from, to, s_to, 0, 0);
	}

	inline char* WideToMulti(const wchar_t* from, size_t& s_from) {
		char* temp = new char[s_from];
		WideCharToMultiByte(CP_ACP, 0, from, s_from, temp, s_from, 0, 0);
		return temp;
	}

	inline void MultiToWide(const char * from, size_t& s_from, wchar_t* to, size_t& s_to) {
		MultiByteToWideChar(CP_ACP, 0, from, s_from, to, s_to);
	}

	inline wchar_t* MultiToWide(const char* from, const size_t& s_from) {
		wchar_t* temp = new wchar_t[s_from];
		MultiByteToWideChar(CP_ACP, 0, from, s_from, temp, s_from);
		return temp;
	}
}
#endif
