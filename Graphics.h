#pragma once

#include <Windows.h>

#include <exception>
#include <stdexcept>
#include <string>

using namespace std;

class Graphics
{
	public:
		const wstring ClassName{ L"GraphicsWndClass" };
	private:
		HWND mnWnd, GraphicsWnd;

	public:
		explicit Graphics(HWND mnWnd);

		HWND GetHWND();

	private:
		LRESULT CALLBACK GraphicsProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

