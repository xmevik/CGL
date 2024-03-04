#pragma once

#include <Windows.h>

#include <exception>
#include <stdexcept>
#include <string>

using namespace std;

class ScreenSaver
{
	public:
	private:
		const wstring ClassName{ L"ScreenSaverWndClass" }, AppName{ L"Заставка экрана"};
		HWND mnWnd, ScreenSaverWnd, GoBackButton;
		UINT widht{ 500 }, height{ 500 };
		HINSTANCE hInstance;
		// TODO: Not implemented
	public:
		explicit ScreenSaver(HWND mnWnd, HINSTANCE hInstance);

		HWND GetHWND() const;

	private:
		LRESULT CALLBACK TableProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

