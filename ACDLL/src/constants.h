#pragma once
#include <Windows.h>
#include "genCode.h"
#include <vector>

extern HMODULE hModule;
extern uintptr_t exeBaseAddress;

extern Player* playerclass;
extern uintptr_t playerBaseAddress;

extern int* healthPtr;

extern EntityList* players;
extern int amount;
extern float* viewMatrix;

void resetPointers();

typedef BOOL(__stdcall* _wglSwapBuffers)(HDC hdc);
extern _wglSwapBuffers originalSwapBuffers;

typedef int(__fastcall* _SDL_SetRelativeMouseMode)(int mode);
extern _SDL_SetRelativeMouseMode originalSetRelativeMouseMode;

//eninty list be like mov [edi + edx*4]
						//[address off array + index * 4]


 