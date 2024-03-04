#include "Integral.h"

Integral::Integral(HWND mnHwnd, HINSTANCE hInstance)
{
	this->mnWnd = mnHwnd;
	this->hInstance = hInstance;

	this->IntegralWnd = CreateWindowW(this->ClassName.c_str(), this->AppName.c_str(),
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		(GetSystemMetrics(SM_CXSCREEN) - this->widht) / 2u,
		(GetSystemMetrics(SM_CYSCREEN) - this->height) / 2u,
		this->widht, this->height,
		nullptr, nullptr, this->hInstance, this);

	if (this->IntegralWnd == INVALID_HANDLE_VALUE)
		throw runtime_error("Unable to create main window"s);
}

HWND Integral::GetHWND() const
{
	return this->IntegralWnd;
}