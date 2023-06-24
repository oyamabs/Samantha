// dllmain.cpp : Définit le point d'entrée de l'application DLL.
#include "pch.h"
#include "Addresses.h"
#include "Samantha.h"

BOOL WINAPI SamThread(HMODULE hMod) {
    Samantha::ExecTrainer(hMod);
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
        CloseHandle(CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)SamThread, hModule, 0, NULL));
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

