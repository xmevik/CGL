#pragma once

#include <Windows.h>

#include <exception>
#include <stdexcept>
#include <string>

using namespace std;

class Expression
{
	enum PageInteraction
	{
		GoBackClicked,
	};
	private:
		const wstring ClassName{ L"ExpressionWndClass" }, AppName{ L"Выражение" };
		HWND mnWnd, ExpressionWnd, GoBackButton;
		UINT widht{ 500 }, height{ 500 };
		HINSTANCE hInstance;
		// TODO: Not implemented
	public:
		explicit Expression(HWND &mnWnd, HINSTANCE &hInstance);

		void ShowHWND(int nCmdShow) const;

	private:
		static LRESULT CALLBACK ExpressionProc(HWND, UINT, WPARAM, LPARAM);
		LRESULT CALLBACK windowProc(HWND, UINT, WPARAM, LPARAM);
		LRESULT CALLBACK handleCommand(HWND, UINT, WPARAM, LPARAM);
		void initNativeObj();
		void createNativeControls();
};

