// StringConv.h : This file contains the interface to StringConv.cpp.
//

#pragma once

#include <string>

using namespace std;

///Converts UTF-8 to UTF-16
wstring StringToWchar(const string& str);

///Converts UTF-16 to UTF-8
string WcharToString(const wstring& wstr);

