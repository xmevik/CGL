#pragma once

#include <Windows.h>

#include <exception>
#include <stdexcept>
#include <string>

#include "../../Components/MatrixScreenSaver/threads.h"

using namespace std;

class ScreenSaver
{
	public:
	private:
		const wstring ClassName{ L"ScreenSaverWndClass" }, AppName{ L"Calculating..."};
		HWND mnWnd, ScreenSaverWnd;
		HANDLE MatrixThread;
		HDC hdc;
		PAINTSTRUCT ps;
		UINT Horzres{ 500 }, Vertres{ 500 };
		int* Parameters;
		bool isScreenSaverActive{ false };
		matrix::GraphicsParam ThreadParam;
		HINSTANCE hInstance;
		// TODO: Not implemented
	public:
		explicit ScreenSaver(HWND mnWnd, HINSTANCE hInstance);

		void ShowHWND() const;

	private:
		static LRESULT CALLBACK SaverProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		LRESULT CALLBACK windowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		void initNativeObj();
		void createNativeControls();
};

