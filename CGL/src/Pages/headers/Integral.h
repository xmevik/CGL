#pragma once

#include <Windows.h>

#include <exception>
#include <stdexcept>
#include <string>

using namespace std;

class Integral
{
	enum PageInteraction
	{
		GoBackClicked,

	};

	private:
		const wstring ClassName{ L"IntegralWndClass" }, AppName{ L"Вычисление интеграла"};
		HWND mnWnd, IntegralWnd, GoBackButton;
		UINT widht{ 500 }, height{ 500 };
		HINSTANCE hInstance;

	public:
		explicit Integral(HWND& mnWnd, HINSTANCE& hInstance);

		void ShowHWND(int nCmdShow) const;

	private:
		static LRESULT CALLBACK IntegralProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		LRESULT CALLBACK windowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		LRESULT CALLBACK handleCommand(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		void initNativeObj();
		void createNativeControls();
};

