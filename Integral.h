#pragma once

#include <Windows.h>

#include <exception>
#include <stdexcept>
#include <string>

using namespace std;

class Integral
{
	public:
		const wstring ClassName{ L"IntegralWndClass" };
	private:
		HWND mnWnd, IntegralWnd;

	public:
		explicit Integral(HWND mnWnd);

		HWND GetHWND();

	private:
		LRESULT CALLBACK TableProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

