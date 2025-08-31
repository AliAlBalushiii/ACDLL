#pragma once
#include <Windows.h>

namespace Menu {
	void init();
	void toggleMenu();
	void render();
	void startRender();
	void endRender();
	BOOL __stdcall newSwapBuffers(HDC hdc);
}