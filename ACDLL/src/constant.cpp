#include "constants.h"
#include <Windows.h>

HMODULE hModule = GetModuleHandle(nullptr);
uintptr_t exeBaseAddress = (uintptr_t)GetModuleHandle(nullptr);

Player* playerclass = *(Player**)(exeBaseAddress + 0x0017E0A8);
uintptr_t playerBaseAddress = (uintptr_t)playerclass;

int* healthPtr = (int*)(playerBaseAddress + 0xEC);

uintptr_t playersAdder = exeBaseAddress + 0x18AC04;
EntityList * players = *(EntityList**)(playersAdder);

int amount = *(int*)(exeBaseAddress + 0x191FD4);

extern float* viewMatrix = (float*)(exeBaseAddress + 0x17DFD0);

void resetPointers() {
	
	playerclass = *(Player**)(exeBaseAddress + 0x0017E0A8);
	playerBaseAddress = (uintptr_t)playerclass;
	amount = *(int*)(exeBaseAddress + 0x191FD4);
}

_wglSwapBuffers originalSwapBuffers = (_wglSwapBuffers)GetProcAddress(GetModuleHandleA("opengl32.dll"), "wglSwapBuffers");

_SDL_SetRelativeMouseMode originalSetRelativeMouseMode = (_SDL_SetRelativeMouseMode)GetProcAddress(GetModuleHandleA("SDL2.dll"), "SDL_SetRelativeMouseMode");