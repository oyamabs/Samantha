#include "pch.h"
#include "Samantha.h"
#include "Addresses.h"
#include "Codes.h"
#include "proc.h"
#include "httplib.h"

constexpr int SLEEP_DELAY = 5;
httplib::Server pSrv;

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

void Samantha::ExecServer(sParameters* sParams, bool* pRunning) {
    
    pSrv.Get("/", [](const httplib::Request&, httplib::Response& res) {
        res.set_content("/ - display this message\n/setGodMode - sets god mode\n/setUnlimitedAmmos - Set unlimited ammos\n/setUnlimitedPoints - sets unlimited points\n/setPoints/:points - sets number of points (max: 2147483647)\n/setNoclip - sets no clip mode", "text/plain");
    });

    pSrv.Get("/setGodMode", [&](const httplib::Request&, httplib::Response& res) {
        sParams->bGodMode = !sParams->bGodMode;

        SetGodMode(sParams->bGodMode);
    });

    pSrv.Get("/setUnlimitedPoints", [&](const httplib::Request&, httplib::Response& res) {
        sParams->bInfinitePoints = !sParams->bInfinitePoints;

        SetInfinitePoints(sParams->bInfinitePoints);
    });

    pSrv.Get("/setUnlimitedAmmos", [&](const httplib::Request&, httplib::Response& res) {
        sParams->bUnlimitedAmmos = !sParams->bUnlimitedAmmos;

        SetUnlimitedAmmos(sParams->bUnlimitedAmmos);
    });
    
    pSrv.Get("/setNoclip", [&](const httplib::Request&, httplib::Response& res) {
        sParams->bNoclip = !sParams->bNoclip;

        SetNoclip(sParams->bNoclip);
    });

    pSrv.Get("/setPoints/:points", [&](const httplib::Request& req, httplib::Response& res) {
        std::string sPoints = req.path_params.at("points");

        try {
            *Player::iPoints = std::stoi(sPoints.c_str());;
        }
        catch (std::exception& e) {
            MsgBox(L"Erreur lors de l'attribution des points ! Le type doit être un nombre !");
        }
    });

    pSrv.listen("0.0.0.0", 1337);
}

void Samantha::ExecTrainer(HMODULE hMod) {
    // Starting the trainer by initializing debug console
    AllocConsole();
    FILE* pF;
    freopen_s(&pF, "CONOUT$", "w", stdout);

    MsgBox(L"Trainer Injected ! Press <PageUp> for displaying help !");
    SetConsoleTitleA("Samantha Trainer");
    
    // Starting hack
    bool bRunning = true;
    sParameters params;

    // Starting web server
    std::thread tWebServer(ExecServer, &params, &bRunning);

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
            params.bNoclip = !params.bNoclip;

            Samantha::SetNoclip(params.bNoclip);
        }

        if (GetAsyncKeyState(VK_F3) & 1) {
            params.bGodMode = !params.bGodMode;

            Samantha::SetGodMode(params.bGodMode);
        }

        if (GetAsyncKeyState(VK_F4) & 1) {
            params.bUnlimitedAmmos = !params.bUnlimitedAmmos;

            Samantha::SetUnlimitedAmmos(params.bUnlimitedAmmos);
        }

        if (GetAsyncKeyState(VK_F5) & 1) {
            params.bInfinitePoints = !params.bInfinitePoints;

            Samantha::SetInfinitePoints(params.bInfinitePoints);
        }
    }

    // Destroying the console
    FreeConsole();
    fclose(pF);

    pSrv.stop();
    // Leaving the thread to eject the trainer
    FreeLibraryAndExitThread(hMod, NULL);
}