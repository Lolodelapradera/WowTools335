#pragma once
#include <Windows.h>
#include <string>


DWORD ReadDWORD(DWORD address);
DWORD _ReadDWORD(DWORD address);
std::string ParseSha1Hash(const DWORD* Seed, const DWORD* p_hash);
DWORD GetBaseAddress();
bool tContains(const char* Data, const char* substring);

template<typename ... Args>
std::string Loggin(bool toConsole, const char* fileName, const std::string& format, Args ... args);