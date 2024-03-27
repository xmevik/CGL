#include "../Components/MatrixScreenSaver/shell/shell.h"
#include "headers/ScreenSaver.h"

#include <sstream>
#include <iomanip>

ScreenSaver::ScreenSaver(HWND mnHwnd, HINSTANCE hInstance)
{
	this->mnWnd = mnHwnd;
	this->hInstance = hInstance;

	this->initNativeObj();
	this->createNativeControls();
}

void ScreenSaver::initNativeObj()
{
	WNDCLASSEXW saverClass{ sizeof(WNDCLASSEXW) };

	saverClass.cbClsExtra = 0;
	saverClass.cbWndExtra = 0;
	saverClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	saverClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	saverClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	saverClass.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
	saverClass.hInstance =  this->hInstance;
	saverClass.lpfnWndProc = this->SaverProc;
	saverClass.lpszClassName = this->ClassName.c_str();
	saverClass.lpszMenuName = nullptr;
	saverClass.style = 0;

	RegisterClassExW(&saverClass);

	this->ScreenSaverWnd = CreateWindowExW(0L, this->ClassName.c_str(), this->AppName.c_str(), WS_OVERLAPPEDWINDOW | WS_MAXIMIZE, 0, 0, Horzres, Vertres, NULL, NULL, hInstance, NULL); // Window creation
	
	if (this->ScreenSaverWnd == INVALID_HANDLE_VALUE)
		throw runtime_error("Unable to create main window"s);

	this->Parameters = shell::LoadConfig();

	SetWindowLongW(this->ScreenSaverWnd, GWL_STYLE, WS_POPUP);
	SetWindowLongW(this->ScreenSaverWnd, GWL_EXSTYLE, WS_EX_TOPMOST);

	SetWindowLongW(this->ScreenSaverWnd, GWL_EXSTYLE, GetWindowLong(this->ScreenSaverWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
	SetLayeredWindowAttributes(this->ScreenSaverWnd, 0, this->Parameters[3], LWA_ALPHA);
}

void ScreenSaver::createNativeControls()
{
	int Error = shell::CheckConfigValues(this->Parameters);

	if (Error != 0)
	{
		if (Error == -1)
		{
			MessageBoxW(this->ScreenSaverWnd, L"File config.txt is missing or corrupted!", L"Critical error", 0);
		}

		PostQuitMessage(0);
	}

	this->hdc = GetDC(this->ScreenSaverWnd);
	this->Horzres = GetDeviceCaps(this->hdc, HORZRES);
	this->Vertres = GetDeviceCaps(this->hdc, VERTRES);

	this->ThreadParam.hdc = this->hdc;
	this->ThreadParam.Horzres = this->Horzres;
	this->ThreadParam.Vertres = this->Vertres;
	this->ThreadParam.Parameters = this->Parameters;

	this->MatrixThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)thread::GraphicsEventThread, reinterpret_cast<LPVOID>(&this->ThreadParam), 0, 0);
}

LRESULT CALLBACK ScreenSaver::SaverProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	ScreenSaver* hSaver;
	if (uMsg == WM_CREATE)
	{
		hSaver = static_cast<ScreenSaver*>(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams);
		SetLastError(0);
		if (!SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(hSaver)))
			if (GetLastError() != 0)
				return false;
	}
	else
	{
		hSaver = reinterpret_cast<ScreenSaver*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	}

	if (hSaver)
	{
		hSaver->ScreenSaverWnd = hwnd;
		return hSaver->windowProc(hwnd, uMsg, wParam, lParam);
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK ScreenSaver::windowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	SetCursorPos(this->Horzres - 15, this->Vertres - 25);

	switch (uMsg)
	{
		case WM_KEYDOWN:
		{
			TerminateThread(this->MatrixThread, 0);
			EndPaint(hwnd, &ps);
			DestroyWindow(this->ScreenSaverWnd);// App::ButtonsInteraction::DestroyClicked
			SendMessage(this->mnWnd, WM_COMMAND, LOWORD(1556), reinterpret_cast<LPARAM>(this->ScreenSaverWnd));

			break;
		}

		case WM_PAINT:
		{
			matrix::InitPaint(hwnd, hdc, &ps);

			break;
		}

		case WM_DESTROY:
		{
			TerminateThread(this->MatrixThread, 0);
			EndPaint(hwnd, &ps);				
			DestroyWindow(this->ScreenSaverWnd);// App::ButtonsInteraction::DestroyClicked
			SendMessage(this->mnWnd, WM_COMMAND, LOWORD(1556), reinterpret_cast<LPARAM>(this->ScreenSaverWnd));

			break;
		}

		default:
		{
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
			break;
		}
	}

	SetCursorPos(this->Horzres - 25, this->Vertres - 25);

	return 0;
}
// TODO: Not implemented
void ScreenSaver::ShowHWND() const
{
	ShowWindow(this->ScreenSaverWnd, SW_SHOWMAXIMIZED);

	UpdateWindow(this->ScreenSaverWnd);
	SetFocus(this->ScreenSaverWnd);
}