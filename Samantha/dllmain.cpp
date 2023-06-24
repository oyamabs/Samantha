// dllmain.cpp : Définit le point d'entrée de l'application DLL.
#include "pch.h"
#include "Addresses.h"

BOOL WINAPI SamThread(HMODULE hMod) {
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);

    FreeConsole();
    fclose(f);
    FreeLibraryAndExitThread(hMod, NULL);
    return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        const HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)SamThread, hModule, 0, NULL);
        
        CloseHandle(hThread);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

