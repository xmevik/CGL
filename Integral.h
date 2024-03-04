#pragma once

#include <Windows.h>

#include <exception>
#include <stdexcept>
#include <string>

using namespace std;

class Integral
{
	public:
	private:
		const wstring ClassName{ L"IntegralWndClass" }, AppName{ L"Вычисление интеграла"};
		HWND mnWnd, IntegralWnd, GoBackButton;
		UINT widht{ 500 }, height{ 500 };
		HINSTANCE hInstance;

	public:
		explicit Integral(HWND mnHwnd, HINSTANCE hInstance);

		HWND GetHWND() const;

	private:
		LRESULT CALLBACK TableProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

