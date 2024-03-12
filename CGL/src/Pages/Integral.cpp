#include "headers/Integral.h"

Integral::Integral(HWND& mnHwnd, HINSTANCE& hInstance)
{
	this->mnWnd = mnHwnd;
	this->hInstance = hInstance;

	this->initNativeObj();
	this->createNativeControls();
}

void Integral::initNativeObj()
{
	WNDCLASSEXW integralClass{ sizeof(WNDCLASSEXW) };

	integralClass.cbClsExtra = 0;
	integralClass.cbWndExtra = 0;
	integralClass.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	integralClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	integralClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	integralClass.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
	integralClass.hInstance = this->hInstance;
	integralClass.lpfnWndProc = this->IntegralProc;
	integralClass.lpszClassName = this->ClassName.c_str();
	integralClass.lpszMenuName = nullptr;
	integralClass.style = 0;

	RegisterClassExW(&integralClass);

	this->IntegralWnd = CreateWindowExW(0L, integralClass.lpszClassName, this->AppName.c_str(),
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		(GetSystemMetrics(SM_CXSCREEN) - this->widht) / 2u,
		(GetSystemMetrics(SM_CYSCREEN) - this->height) / 2u,
		this->widht, this->height,
		this->mnWnd, nullptr, this->hInstance, this);

	if (this->IntegralWnd == INVALID_HANDLE_VALUE)
		throw runtime_error("Unable to create main window"s);
}

void Integral::createNativeControls()
{
	this->GoBackButton = CreateWindowExW(0l, L"button", L"Вернуться назад", WS_VISIBLE | WS_CHILD | ES_CENTER,
		10, 10, 150, 25, this->IntegralWnd,
		reinterpret_cast<HMENU>(Integral::PageInteraction::GoBackClicked), nullptr, nullptr);
}

LRESULT CALLBACK Integral::IntegralProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	Integral* hIntegral;
	if (uMsg == WM_CREATE)
	{
		hIntegral = static_cast<Integral*>(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams);
		SetLastError(0);
		if (!SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(hIntegral)))
			if (GetLastError() != 0)
				return false;
	}
	else
	{
		hIntegral = reinterpret_cast<Integral*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	}

	if (hIntegral)
	{
		hIntegral->IntegralWnd = hwnd;
		return hIntegral->windowProc(hwnd, uMsg, wParam, lParam);
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK Integral::windowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_COMMAND:
	{
		return this->handleCommand(hwnd, uMsg, wParam, lParam);
	}
	case WM_CLOSE:
	{						// App::ButtonsInteraction::DestroyClicked
		SendMessage(this->mnWnd, WM_COMMAND, LOWORD(1555), reinterpret_cast<LPARAM>(this->IntegralWnd));

		return TRUE;
	}
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	}
}

LRESULT CALLBACK Integral::handleCommand(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (static_cast<Integral::PageInteraction>(LOWORD(wParam)))
	{
	case Integral::PageInteraction::GoBackClicked:
	{						// App::ButtonsInteraction::DestroyClicked
		SendMessage(this->mnWnd, WM_COMMAND, LOWORD(1555), reinterpret_cast<LPARAM>(this->IntegralWnd));

		return TRUE;
	}
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}

void Integral::ShowHWND(int nCmdShow) const
{
	ShowWindow(this->IntegralWnd, nCmdShow);
	UpdateWindow(this->IntegralWnd);
}