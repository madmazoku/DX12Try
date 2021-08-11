#pragma once

#include <Windows.h>

#include <string>
#include <vector>

inline std::string string_cast(const std::wstring& wstr, unsigned int codePage = CP_ACP)
{
    int length = ::WideCharToMultiByte(codePage, 0, wstr.c_str(), -1, NULL, 0, NULL, NULL);
    if (length <= 1)
        return std::string();
    length--;

    std::vector<CHAR> buffer(length);
    ::WideCharToMultiByte(codePage, 0, wstr.c_str(), -1, buffer.data(), length, NULL, NULL);

    return std::string(buffer.begin(), buffer.end());
}

inline std::wstring wstring_cast(const std::string& str, unsigned int codePage = CP_ACP)
{
    int length = ::MultiByteToWideChar(codePage, 0, str.c_str(), -1, NULL, 0);
    if (length <= 1)
        return std::wstring();
    length--;

    std::vector<WCHAR> buffer(length);
    ::MultiByteToWideChar(codePage, 0, str.c_str(), -1, buffer.data(), length);

    return std::wstring(buffer.begin(), buffer.end());
}
