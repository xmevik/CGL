#include "Table.h"

Table::Table(HWND mnHwnd, HINSTANCE hInstance)
{
	this->mnWnd = mnHwnd;
	this->hInstance = hInstance;

	this->TableWnd = CreateWindowW(this->ClassName.c_str(), this->AppName.c_str(),
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		this->widht, this->height,
		nullptr, nullptr, this->hInstance, this);

	if (this->TableWnd == INVALID_HANDLE_VALUE)
		throw runtime_error("Unable to create main window"s);
}
// TODO: Not implemented
void Table::ShowHWND(int nCmdShow) const
{
	ShowWindow(this->TableWnd, nCmdShow);
	UpdateWindow(this->TableWnd);
}