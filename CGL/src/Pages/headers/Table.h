#pragma once

#include <Windows.h>

#include <exception>
#include <stdexcept>
#include <string>
#include <vector>

#include "./../../utils/TablesHelper.cpp"

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
		UINT widht{ 600 }, height{ 600 };
		HINSTANCE hInstance;
		vector<vector<double>> tableData;
		vector<vector<wstring>> minMaxData;

	public:
		explicit Table(HWND& mnWnd, HINSTANCE& hInstence);

		void ShowHWND(int nCmdShow) const;
	private:
		static LRESULT CALLBACK TableProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		LRESULT CALLBACK windowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		LRESULT CALLBACK handleCommand(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) const;
		void initNativeObj();
		void createNativeControls();
		BOOL WINAPI AddListViewItems(int colNum, int textMaxLen, std::vector<double> item) const;
		BOOL WINAPI AddConcreteListViewItem(int colNum, int textMaxLen, std::vector<wstring> item) const;
		int SetListViewColumns(int colNum, int textMaxLen, wstring header[5]) const;
		void CreateListView();
};

