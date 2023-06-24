#include "pch.h"
#include "Samantha.h"
#include <d3d9.h>

constexpr int SLEEP_DELAY = 5;

void Samantha::DrawText(const char* text) {

}

void Samantha::ExecTrainer(HMODULE hMod) {
    // Starting the trainer by initializing debug console
    AllocConsole();
    FILE* pF;
    freopen_s(&pF, "CONOUT$", "w", stdout);

    SetConsoleTitleA("Samantha Trainer");

    // Hack loop
    bool bRunning = true;

    while (bRunning) {
        Sleep(SLEEP_DELAY); // Avoiding thread to work "too much"

        if (GetAsyncKeyState(VK_END) & 1) {
            bRunning = false;
        }

        
    }

    // Destroying the console
    FreeConsole();
    fclose(pF);

    // Leaving the thread to eject the trainer
    FreeLibraryAndExitThread(hMod, NULL);
}