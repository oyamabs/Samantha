#include <iostream>
#include <Windows.h>
#include "Proc.h"

int main()
{
    DWORD dPid = 0;

    dPid = GetPID(L"BlackOps.exe");

    if (dPid == 0) {
        std::cout << "[-] Call of Duty Black Ops n'a pas �t� trouv�. V�rifiez que le jeu est bien lanc� avant de relancer Samantha Injector!" << std::endl;
        system("pause");
        return 1;
    }

    std::cout << "[+] Call of Duty Black Ops trouv�! Injection du DLL en cours" << std::endl;

    HANDLE hProc;
    hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dPid);

    if (hProc && hProc != INVALID_HANDLE_VALUE) {
        void* loc = VirtualAllocEx(hProc, 0, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
        
        const char* dllPath = "C:\\Samantha.dll";

        WriteProcessMemory(hProc, loc, dllPath, strlen(dllPath) + 1, 0);

        HANDLE hThread = CreateRemoteThread(hProc, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, loc, 0, 0);

        if (hThread)
            CloseHandle(hThread);
    }

    if (hProc)
        CloseHandle(hProc);

    std::cout << "[+] DLL inject�! Vous pouvez fermer cette fen�tre" << std::endl;
    system("pause");

    return 0;
}
