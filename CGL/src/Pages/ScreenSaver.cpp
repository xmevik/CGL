#include "../Components/MatrixScreenSaver/shell/shell.h"
#include "headers/ScreenSaver.h"
#include <sstream>
#include <iomanip>
ScreenSaver::ScreenSaver(HWND &mnHwnd, HINSTANCE &hInstance)
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
	saverClass.lpfnWndProc = this->windowProc;
	saverClass.lpszClassName = this->ClassName.c_str();
	saverClass.lpszMenuName = nullptr;
	saverClass.style = 0;

	RegisterClassExW(&saverClass);

	this->ScreenSaverWnd = CreateWindowExW(0L, this->ClassName.c_str(), this->AppName.c_str(), 
		WS_OVERLAPPEDWINDOW | WS_MAXIMIZE, 0, 0, Horzres, Vertres, NULL, NULL, hInstance, NULL);
}
void ScreenSaver::createNativeControls()
{
	this->hdc = GetDC(this->ScreenSaverWnd);
	this->Horzres = GetDeviceCaps(this->hdc, HORZRES);
	this->Vertres = GetDeviceCaps(this->hdc, VERTRES);

	this->ThreadParam.hdc = this->hdc;
	this->ThreadParam.Horzres = this->Horzres;
	this->ThreadParam.Vertres = this->Vertres;
	this->ThreadParam.Parameters = this->Parameters;

	this->MatrixThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)thread::GraphicsEventThread, reinterpret_cast<LPVOID>(&this->ThreadParam), 0, 0);
}
LRESULT CALLBACK ScreenSaver::windowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_PAINT:
		{
			matrix::InitPaint(hwnd, hdc, &ps);

			break;
		}

		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
			break;
	}
}
void ScreenSaver::ShowHWND() const
{
	ShowWindow(this->ScreenSaverWnd, SW_SHOWMAXIMIZED);
	UpdateWindow(this->ScreenSaverWnd);
	SetFocus(this->ScreenSaverWnd);
}