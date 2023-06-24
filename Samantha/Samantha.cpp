#include "pch.h"
#include "Samantha.h"
#include "Addresses.h"
#include "Codes.h"
#include "proc.h"

constexpr int SLEEP_DELAY = 5;

void Samantha::MsgBox(const wchar_t* msg)
{
    MessageBoxW(NULL, msg, L"Samantha Trainer", MB_OK | MB_ICONINFORMATION);
}

void Samantha::DisplayHelp()
{
    std::cout << "Help" << std::endl;
    std::cout << "> F1 <\tMax de points" << std::endl;
    std::cout << "> F2 <\tNoclip" << std::endl;
    std::cout << "> F3 <\tGod mode" << std::endl;
    std::cout << "> F4 <\tMunitions infinies" << std::endl;
    std::cout << "> F5 <\tPoints infinis" << std::endl;
    std::cout << "==============================================" << std::endl;
    std::cout << "> PageUp <\tAfficher ce message" << std::endl;
    std::cout << "> END <\tDésinjecter le menu" << std::endl;
}

void Samantha::SetNoclip(bool bNoclip)
{
    *Movement::bNoclip = bNoclip;
}

void Samantha::SetGodMode(bool bGodMode)
{
    if (bGodMode)
        Nop(Player::iGodMode, 6);
    else
        Patch(Player::iGodMode, (BYTE*)Player::sGodMode, 6);
}

void Samantha::SetUnlimitedAmmos(bool bUnlimitedAmmos)
{
    if (bUnlimitedAmmos)
        Nop(Player::iUnlimitedAmmos, 3);
    else
        Patch(Player::iUnlimitedAmmos, (BYTE*)Player::sUnlimitedAmmos, 3);
}

void Samantha::SetInfinitePoints(bool bInifinitePoints)
{
    if (bInifinitePoints)
        Nop(Player::iInfinitePointsAddr, 12);
    else
        Patch(Player::iInfinitePointsAddr, (BYTE*)Player::sPoints, 12);
}

void Samantha::QuitTrainer()
{
    Samantha::SetGodMode(false);
    Samantha::SetInfinitePoints(false);
    Samantha::SetNoclip(false);
    Samantha::SetUnlimitedAmmos(false);
}

void Samantha::ExecTrainer(HMODULE hMod) {
    // Starting the trainer by initializing debug console
    AllocConsole();
    FILE* pF;
    freopen_s(&pF, "CONOUT$", "w", stdout);

    MsgBox(L"Trainer Injected ! Press <PageUp> for displaying help !");
    SetConsoleTitleA("Samantha Trainer");

    // Hack loop
    bool bRunning = true;

    // params
    bool bGodMode = false, bNoclip = false, bInfinitePoints = false, bUnlimitedAmmos = false;

    while (bRunning) {
        Sleep(SLEEP_DELAY); // Avoiding thread to work "too much"

        if (GetAsyncKeyState(VK_END) & 1) {
            bRunning = false;
            Samantha::QuitTrainer();
        }

        if (GetAsyncKeyState(VK_F1) & 1)
            *Player::iPoints = INT_MAX;

        if (GetAsyncKeyState(VK_PRIOR) & 1)
            Samantha::DisplayHelp();
        
        if (GetAsyncKeyState(VK_F2) & 1) {
            bNoclip = !bNoclip;

            Samantha::SetNoclip(bNoclip);
        }

        if (GetAsyncKeyState(VK_F3) & 1) {
            bGodMode = !bGodMode;

            Samantha::SetGodMode(bGodMode);
        }

        if (GetAsyncKeyState(VK_F4) & 1) {
            bUnlimitedAmmos = !bUnlimitedAmmos;

            Samantha::SetUnlimitedAmmos(bUnlimitedAmmos);
        }

        if (GetAsyncKeyState(VK_F5) & 1) {
            bInfinitePoints = !bInfinitePoints;

            Samantha::SetInfinitePoints(bInfinitePoints);
        }
    }

    // Destroying the console
    FreeConsole();
    fclose(pF);

    // Leaving the thread to eject the trainer
    FreeLibraryAndExitThread(hMod, NULL);
}