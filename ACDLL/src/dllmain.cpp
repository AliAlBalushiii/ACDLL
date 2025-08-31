// dllmain.cpp : Defines the entry point for the DLL application.
#include <Windows.h>
#include <iostream>
#include "constants.h"
#include "genCode.h"
#include "esp.h"
#include "../Detours/src/detours.h"
#include "menu.h"

#pragma comment(lib, "detours.lib")

void aimbot() {
    while (true)
    {
        resetPointers();
        ESP::aimbot();
        Sleep(50);
        if (GetAsyncKeyState(VK_DELETE))
        {
            Menu::toggleMenu();
        }
    }
}

void hook() 
{
    Sleep(1000);
    std::cout << "Hook thread started" << std::endl;

    DisableThreadLibraryCalls(hModule);
    if (DetourTransactionBegin() != NO_ERROR) {
        std::cerr << "DetourTransactionBegin failed" << std::endl;
        return;
    }
    //DetourTransactionBegin();
    
    DetourUpdateThread(GetCurrentThread());
    if (DetourAttach(&(PVOID&)originalSwapBuffers, Menu::newSwapBuffers) != NO_ERROR) {
        std::cerr << "DetourAttach failed!" << std::endl;
    }

	//DetourAttach(&(PVOID&)originalSwapBuffers, Menu::newSwapBuffers);
    
    if (DetourTransactionCommit() != NO_ERROR) {  // <-- THIS WAS MISSING
        std::cerr << "DetourTransactionCommit failed!" << std::endl;
    }
}
void console() {
	AllocConsole();
    freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
    freopen_s((FILE**)stderr, "CONOUT$", "w", stderr);
    freopen_s((FILE**)stdin, "CONIN$", "r", stdin);
	std::cout << "Console initialized." << std::endl;

    while (true) {
        std::string input;
        std::cin >> input;

        if (input == "heal")
        {
            *healthPtr += 20;
            std::cout << *healthPtr << std::endl;
        }
        if (input == "x")
        {
            //playerclass->pos.x += 3.0f;
            std::cout << playerclass->pos.x << std::endl;
        }
        if (input == "up")
        {
            playerclass->pos.y += 5;
            std::cout << playerclass->pos.y << std::endl;
        }
        if (input == "ent")
        {
            
            while (true)
            {
                for (int i = 1; i <= amount; i++)
                {
                    std::cout << "Player[" << i << "] " << "x:" << players->players[i]->pos.x << " y:" << players->players[i]->pos.y << " z:" << players->players[i]->pos.z << std::endl;
                }
                Sleep(1);
                system("cls");
            }
        }
        
    }
    FreeConsole();

}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)console, nullptr, 0, nullptr);
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)hook, nullptr, 0, nullptr);
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)aimbot, nullptr, 0, nullptr);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

