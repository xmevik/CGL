#include "headers/Table.h"

Table::Table(HWND mnHwnd, HINSTANCE hInstance)
{
	this->mnWnd = mnHwnd;
	this->hInstance = hInstance;

	this->initNativeObj();
	this->createNativeControls();
}

void Table::initNativeObj()
{
	WNDCLASSEXW tableClass{ sizeof(WNDCLASSEXW) };

	tableClass.cbClsExtra = 0;
	tableClass.cbWndExtra = 0;
	tableClass.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	tableClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	tableClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	tableClass.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
	tableClass.hInstance = this->hInstance;
	tableClass.lpfnWndProc = this->TableProc;
	tableClass.lpszClassName = this->ClassName.c_str();
	tableClass.lpszMenuName = nullptr;
	tableClass.style = 0;

	if (!RegisterClassExW(&tableClass))
		throw runtime_error("Unable to register main window class"s);

	this->TableWnd = CreateWindowExW(0L, tableClass.lpszClassName, this->AppName.c_str(),
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		this->widht, this->height,
		this->mnWnd, nullptr, this->hInstance, this);

	if (this->TableWnd == INVALID_HANDLE_VALUE)
		throw runtime_error("Unable to create main window"s);
}

void Table::createNativeControls()
{
	this->GoBackButton = CreateWindowExW(0l, L"button", L"��������� �����", WS_VISIBLE | WS_CHILD | ES_CENTER,
		10, 10, 150, 25, this->TableWnd,
		reinterpret_cast<HMENU>(Table::PageInteraction::GoBackClicked), nullptr, nullptr);
}

LRESULT CALLBACK Table::TableProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	Table* hTable;
	if (uMsg == WM_CREATE)
	{
		hTable = static_cast<Table*>(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams);
		SetLastError(0);
		if (!SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(hTable)))
			if (GetLastError() != 0)
				return false;
	}
	else
	{
		hTable = reinterpret_cast<Table*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	}

	if (hTable)
	{
		hTable->TableWnd = hwnd;
		return hTable->windowProc(hwnd, uMsg, wParam, lParam);
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK Table::windowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
		case WM_COMMAND:
		{
			return this->handleCommand(hwnd, uMsg, wParam, lParam);
		}
		case WM_CLOSE:
		{
			if (MessageBoxW(this->TableWnd, L"�� ������������� ������ �����?", L"Close application", MB_OKCANCEL) == IDOK)
				ShowWindow(this->TableWnd, SW_HIDE);

			ShowWindow(this->mnWnd, SW_SHOW);
			UpdateWindow(this->mnWnd);
			return EXIT_SUCCESS;
		}
		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
			break;
	}
}

LRESULT CALLBACK Table::handleCommand(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (static_cast<Table::PageInteraction>(LOWORD(wParam)))
	{
		case Table::PageInteraction::GoBackClicked:
		{
			if (MessageBoxW(hwnd, L"��� �������� ������� ����", L"Close window", MB_OKCANCEL) == IDOK)
				DestroyWindow(hwnd);

			return EXIT_SUCCESS;
		}
		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}

// TODO: Not implemented
void Table::ShowHWND(int nCmdShow) const
{
	ShowWindow(this->TableWnd, nCmdShow);
	UpdateWindow(this->TableWnd);
}