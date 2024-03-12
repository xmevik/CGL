#include "headers/Expression.h"

Expression::Expression(HWND &mnHwnd, HINSTANCE &hInstance)
{
	this->mnWnd = mnHwnd;
	this->hInstance = hInstance;

	this->ExpressionWnd = CreateWindowW(this->ClassName.c_str(), this->AppName.c_str(),
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		this->widht, this->height,
		nullptr, nullptr, this->hInstance, this);

	if (this->ExpressionWnd == INVALID_HANDLE_VALUE)
		throw runtime_error("Unable to create main window"s);
}
// TODO: Not implemented
void Expression::ShowHWND(int nCmdShow) const
{
	ShowWindow(this->ExpressionWnd, nCmdShow);
	UpdateWindow(this->ExpressionWnd);
}