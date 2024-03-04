#pragma once

#include <Windows.h>

#include <exception>
#include <stdexcept>
#include <string>

using namespace std;

class ScreenSaver
{
	public:
		const wstring ClassName{ L"ScreenSaverWndClass" };
	private:
		HWND mnWnd, ScreenSaverWnd;

	public:
		explicit ScreenSaver(HWND mnWnd);

		HWND GetHWND();

	private:
		LRESULT CALLBACK TableProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

