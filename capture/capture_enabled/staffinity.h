#pragma once
#include <Windows.h>

namespace staffinity {
	BOOL CALLBACK EnumWindowsCB(HWND hwnd, LPARAM lParam)
	{
		DWORD pid;
		GetWindowThreadProcessId(hwnd, &pid);

		if (pid == lParam)
			SetWindowDisplayAffinity(hwnd, WDA_NONE);

		return TRUE;
	}

	void SetDisplayAffinity() {
		DWORD pid = GetCurrentProcessId();
		EnumWindows(EnumWindowsCB, pid);
	}
};