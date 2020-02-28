// StringConv.cpp : This file contains the implementation for StringConv.cpp
//

#include "StringConv.h"

#include <codecvt>

///Class Global Wstring Converter.
wstring_convert<codecvt_utf8_utf16<wchar_t>, wchar_t>converter;

///Converts UTF-8 to UTF-16
wstring StringToWchar(const string& str)
{
	return converter.from_bytes(str);
}

///Converts UTF-16 to UTF-8
string WcharToString(const wstring& wstr)
{
	return converter.to_bytes(wstr);
}