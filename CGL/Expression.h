#pragma once

#include <Windows.h>

#include <exception>
#include <stdexcept>
#include <string>

using namespace std;

class Expression
{
	public:

	private:
		const wstring ClassName{ L"ExpressionWndClass" }, AppName{ L"Выражение" };
		HWND mnWnd, ExpressionWnd,  GoBackButton;
		UINT widht{ 500 }, height{ 500 };
		HINSTANCE hInstance;

	public:
		explicit Expression(HWND mnWnd, HINSTANCE hInstance);

		HWND GetHWND() const;

	private:
		LRESULT CALLBACK TableProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

