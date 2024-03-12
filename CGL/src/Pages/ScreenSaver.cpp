#include "headers/ScreenSaver.h"

ScreenSaver::ScreenSaver(HWND mnHwnd, HINSTANCE hInstance)
{
	this->mnWnd = mnHwnd;
	this->hInstance = hInstance;

	this->ScreenSaverWnd = CreateWindowW(this->ClassName.c_str(), this->AppName.c_str(),
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		this->widht, this->height,
		nullptr, nullptr, this->hInstance, this);

	if (this->ScreenSaverWnd == INVALID_HANDLE_VALUE)
		throw runtime_error("Unable to create main window"s);
}
// TODO: Not implemented
void ScreenSaver::ShowHWND(int nCmdShow) const
{
	ShowWindow(this->ScreenSaverWnd, nCmdShow);
	UpdateWindow(this->ScreenSaverWnd);
}