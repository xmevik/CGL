#include "Integral.h"

Integral::Integral(HWND& mnHwnd, HINSTANCE& hInstance, WNDCLASSEX& scWnd)
{
	this->mnWnd = mnHwnd;
	this->hInstance = hInstance;

	this->IntegralWnd = CreateWindowW(this->ClassName.c_str(), this->AppName.c_str(),
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		this->widht, this->height,
		nullptr, nullptr, this->hInstance, this);

	if (this->IntegralWnd == INVALID_HANDLE_VALUE)
		throw runtime_error("Unable to create main window"s);
}

void Integral::ShowHWND(int nCmdShow) const
{
	ShowWindow(this->IntegralWnd, nCmdShow);
	UpdateWindow(this->IntegralWnd);
}