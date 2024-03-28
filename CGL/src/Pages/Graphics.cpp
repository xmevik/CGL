#include "headers/Graphics.h"

Graphics::Graphics(HWND& mnHwnd, HINSTANCE& hInstance)
{
	this->mnWnd = mnHwnd;
	this->hInstance = hInstance;

	this->initNativeObj();
	this->createNativeControls();

	if (!SetWindowLongPtr(this->GraphicsWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this)))
		if (GetLastError() != 0)
			throw runtime_error("Can't register window pointer");
}

void Graphics::initNativeObj()
{
	WNDCLASSEXW graphicsClass{ sizeof(WNDCLASSEXW) };

	graphicsClass.cbClsExtra = 0;
	graphicsClass.cbWndExtra = 0;
	graphicsClass.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	graphicsClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	graphicsClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	graphicsClass.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
	graphicsClass.hInstance = this->hInstance;
	graphicsClass.lpfnWndProc = this->GraphicsProc;
	graphicsClass.lpszClassName = this->ClassName.c_str();
	graphicsClass.lpszMenuName = nullptr;
	graphicsClass.style = 0;

	RegisterClassExW(&graphicsClass);

	this->GraphicsWnd = CreateWindowExW(0L, graphicsClass.lpszClassName, this->AppName.c_str(),
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		(GetSystemMetrics(SM_CXSCREEN) - this->widht) / 2u,
		(GetSystemMetrics(SM_CYSCREEN) - this->height) / 2u,
		this->widht, this->height,
		this->mnWnd, nullptr, this->hInstance, this);

	if (this->GraphicsWnd == INVALID_HANDLE_VALUE)
		throw runtime_error("Unable to create main window"s);
}

void Graphics::createNativeControls()
{
	this->GoBackButton = CreateWindowExW(0l, L"button", L"Вернуться назад", WS_VISIBLE | WS_CHILD | ES_CENTER,
		10, 10, 150, 25, this->GraphicsWnd,
		reinterpret_cast<HMENU>(Graphics::PageInteraction::GoBackClicked), nullptr, nullptr);
}

LRESULT CALLBACK Graphics::GraphicsProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	Graphics* hTable = reinterpret_cast<Graphics*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

	if (hTable)
	{
		hTable->GraphicsWnd = hwnd;
		return hTable->windowProc(hwnd, uMsg, wParam, lParam);
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK Graphics::windowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
		case WM_COMMAND:
		{
			return this->handleCommand(hwnd, uMsg, wParam, lParam);
		}
		case WM_CLOSE:
		{						// App::ButtonsInteraction::DestroyClicked
			SendMessage(this->mnWnd, WM_COMMAND, LOWORD(1555), reinterpret_cast<LPARAM>(this->GraphicsWnd));

			return TRUE;
		}
		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
			break;
	}
}

LRESULT CALLBACK Graphics::handleCommand(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (static_cast<Graphics::PageInteraction>(LOWORD(wParam)))
	{
		case Graphics::PageInteraction::GoBackClicked:
		{						// App::ButtonsInteraction::DestroyClicked
			SendMessage(this->mnWnd, WM_COMMAND, LOWORD(1555), reinterpret_cast<LPARAM>(this->GraphicsWnd));

			return TRUE;
		}
		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}

void Graphics::ShowHWND(int nCmdShow) const
{
	ShowWindow(this->GraphicsWnd, nCmdShow);
	UpdateWindow(this->GraphicsWnd);
}