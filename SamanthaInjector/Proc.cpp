#include <Windows.h>
#include <TlHelp32.h>
#include "Proc.h"

DWORD GetPID(const wchar_t* procName) {
	DWORD dPid = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hSnap != INVALID_HANDLE_VALUE) {
		PROCESSENTRY32 procEntry;
		procEntry.dwSize = sizeof(procEntry);

		bool found = false;
		if (Process32First(hSnap, &procEntry)) {
			do {
				if (!_wcsicmp(procName, procEntry.szExeFile)) {
					found = true;
					dPid = procEntry.th32ProcessID;
				}
			} while (!found && Process32Next(hSnap, &procEntry));
		}
	}

	CloseHandle(hSnap);

	return dPid;
}
