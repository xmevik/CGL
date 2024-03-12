#pragma once

#include <Windows.h>

#include <exception>
#include <stdexcept>
#include <string>

using namespace std;

class Table
{
	enum PageInteraction
	{
		GoBackClicked,

	};

	private:
		const wstring ClassName{ L"TableWndClass" }, AppName{ L"Таблица"};
		HWND mnWnd, TableWnd, hListView, GoBackButton;
		UINT widht{ 500 }, height{ 500 };
		HINSTANCE hInstance;

	public:
		explicit Table(HWND& mnWnd, HINSTANCE& hInstence);

		void ShowHWND(int nCmdShow) const;
	private:
		static LRESULT CALLBACK TableProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		LRESULT CALLBACK windowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		LRESULT CALLBACK handleCommand(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		void initNativeObj();
		void createNativeControls();
};

