#pragma once

#include <Windows.h>
#include <strsafe.h>

#include <iostream>
#include <filesystem>
#include <sstream>

#include "StringCast.h"

#define LOG std::cerr << std::filesystem::path(__FILE__).filename().string() << ":" << __LINE__ << " [" << __FUNCTION__ << "] "
#define LAST_ERROR_MSG(dwError) GetLastErrorMsg(__FUNCTION__, dwError)

inline std::ostream& operator<<(std::ostream& os, const RECT& rect)
{
	return os << "RECT: {" << rect.left << ", " << rect.top << ", " << rect.right << ", " << rect.bottom << "}";
}

inline std::ostream& operator<<(std::ostream& os, const POINT& point)
{
	return os << "POINT: {" << point.x << ", " << point.y << "}";
}

inline std::ostream& operator<<(std::ostream& os, const SIZE& size)
{
	return os << "SIZE: {" << size.cx << ", " << size.cy << "}";
}

inline std::string GetLastErrorMsg(const std::string strFunction, DWORD dwError) {
	LPWSTR lpMsgBuf;

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dwError,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPWSTR)&lpMsgBuf,
		0, 
		NULL
	);

	std::stringstream ss;
	ss << "Last Error: [" << dwError << "] " << string_cast(lpMsgBuf) << " in " << strFunction;

	LocalFree(lpMsgBuf);

	return ss.str();
}