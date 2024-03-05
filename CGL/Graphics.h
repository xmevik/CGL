#pragma once

#include <Windows.h>

#include <exception>
#include <stdexcept>
#include <string>

using namespace std;

class Graphics
{
	public:

	private:
		const wstring ClassName{ L"GraphicsWndClass" }, AppName{ L"Графики функций"};
		HWND mnWnd, GraphicsWnd, GoBackButton;
		UINT widht{ 500 }, height{ 500 };
		HINSTANCE hInstance;
		// TODO: Not implemented
	public:
		explicit Graphics(HWND mnHwnd, HINSTANCE hInstance);

		HWND GetHWND() const;

	private:
		LRESULT CALLBACK GraphicsProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

