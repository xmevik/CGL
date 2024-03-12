#pragma once

#include <Windows.h>

#include <exception>
#include <stdexcept>
#include <string>

using namespace std;

class Graphics
{
	enum PageInteraction
	{
		GoBackClicked,
	};

	private:
		const wstring ClassName{ L"GraphicsWndClass" }, AppName{ L"Графики функций"};
		HWND mnWnd, GraphicsWnd, GoBackButton;
		UINT widht{ 500 }, height{ 500 };
		HINSTANCE hInstance;

	public:
		explicit Graphics(HWND& mnWnd, HINSTANCE& hInstance);

		void ShowHWND(int nCmdShow) const;

	private:
		static LRESULT CALLBACK GraphicsProc(HWND, UINT, WPARAM, LPARAM);
		LRESULT CALLBACK windowProc(HWND, UINT, WPARAM, LPARAM);
		LRESULT CALLBACK handleCommand(HWND, UINT, WPARAM, LPARAM);
		void initNativeObj();
		void createNativeControls();
};

