#pragma once
#include <Windows.h>
#include <TlHelp32.h>

DWORD GetPID(const wchar_t* procName);