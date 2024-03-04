#pragma once

#include <Windows.h>

#include <exception>
#include <stdexcept>
#include <string>

using namespace std;

class Table
{
	public:

	private:
		const wstring ClassName{ L"TableWndClass" }, AppName{ L"Таблица"};
		HWND mnWnd, TableWnd, hListView, GoBackButton;
		UINT widht{ 500 }, height{ 500 };
		HINSTANCE hInstance;
		// TODO: Not implemented
	public:
		explicit Table(HWND mnWnd, HINSTANCE hInstance);

		HWND GetHWND() const;

	private:
		LRESULT CALLBACK TableProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

