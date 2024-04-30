#include <Windows.h>
#include <commctrl.h>
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
}
void Integral::createNativeControls()
{
	this->GoBackButton = CreateWindowExW(0l, WC_BUTTONW, L"Вернуться назад", WS_VISIBLE | WS_CHILD | ES_CENTER,
		10, 10, 150, 25, this->IntegralWnd,
		reinterpret_cast<HMENU>(Integral::PageInteraction::GoBackClicked), nullptr, nullptr);

	this->RecalculateButton = CreateWindowExW(0l, WC_BUTTONW, L"Пересчитать интеграл", WS_VISIBLE | WS_CHILD | ES_CENTER,
		170, 10, 160, 25, this->IntegralWnd,
		reinterpret_cast<HMENU>(Integral::PageInteraction::RecalculateClicked), nullptr, nullptr);

	this->AEdit = CreateWindowExW(0l, WC_EDITW, L"15", WS_CHILD | WS_VISIBLE | ES_NUMBER, 95, 50, 40, 20, this->IntegralWnd, nullptr, nullptr, nullptr);

	this->BEdit = CreateWindowExW(0l, WC_EDITW, L"20", WS_CHILD | WS_VISIBLE | ES_NUMBER, 95, 75, 40, 20, this->IntegralWnd, nullptr, nullptr, nullptr);
}
LRESULT CALLBACK Integral::IntegralProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	Integral* hIntegral = reinterpret_cast<Integral*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

	if (hIntegral)
	{
		hIntegral->IntegralWnd = hwnd;
		return hIntegral->windowProc(hwnd, uMsg, wParam, lParam);
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
LRESULT CALLBACK Integral::windowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) 
	{
		case WM_COMMAND:
		{
			return this->handleCommand(hwnd, uMsg, wParam, lParam);
		}
		case WM_CLOSE:
		{						// App::ButtonsInteraction::DestroyClicked
			return SendMessage(this->mnWnd, WM_COMMAND, LOWORD(1555), reinterpret_cast<LPARAM>(this->IntegralWnd));
		}
		case WM_PAINT:
		{
			::PAINTSTRUCT ps{};
			::HDC hdc{ BeginPaint(this->IntegralWnd, &ps) };

			std::wstring trapezoidalStr = doubleToWString(this->trapezoidal, 18);
			std::wstring simpsonStr = doubleToWString(this->simpson, 18);
			std::wstring midpointStr = doubleToWString(this->midpoint, 18);

			::TextOutW(hdc, 10, 50, L"Граница A = ", ::lstrlenW(L"Граница A = "));
			::TextOutW(hdc, 10, 75, L"Граница B = ", ::lstrlenW(L"Граница B = "));
			::TextOutW(hdc, 10, 100, L"Интегрирование методом трапеций =", ::lstrlenW(L"Интегрирование методом трапеций ="));
			::TextOutW(hdc, 270, 100, trapezoidalStr.c_str(), ::lstrlenW(trapezoidalStr.c_str()));
			::TextOutW(hdc, 10, 125, L"Интегрирование методом Симпсона =", ::lstrlenW(L"Интегрирование методом Симпсона ="));
			::TextOutW(hdc, 270, 125, simpsonStr.c_str(), ::lstrlenW(simpsonStr.c_str()));
			::TextOutW(hdc, 10, 150, L"Интегрирование методом средних прямоугольников =", ::lstrlenW(L"Интегрирование методом средних прямоугольников ="));
			::TextOutW(hdc, 380, 150, midpointStr.c_str(), ::lstrlenW(midpointStr.c_str()));

			EndPaint(this->IntegralWnd, &ps);
			return TRUE;
		}
		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}
LRESULT CALLBACK Integral::handleCommand(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (static_cast<Integral::PageInteraction>(LOWORD(wParam)))
	{
		case Integral::PageInteraction::GoBackClicked:
		{								// App::ButtonsInteraction::DestroyClicked
			return SendMessageW(this->mnWnd, WM_COMMAND, LOWORD(1555), reinterpret_cast<LPARAM>(this->IntegralWnd));
		}
		case Integral::PageInteraction::RecalculateClicked:
		{
			char inputAEdit[16u]{ 0 },
				 inputBEdit[16u]{ 0 };

			::GetWindowTextA(this->AEdit, inputAEdit,
				sizeof(inputAEdit) / sizeof(char) - 1);

			::GetWindowTextA(this->BEdit, inputBEdit,
				sizeof(inputBEdit) / sizeof(char) - 1);

			int AEdit{ 0u },
				BEdit{ 0u };

			AEdit = std::atoi(inputAEdit);
			BEdit = std::atoi(inputBEdit);

			this->trapezoidal = trapezoidalIntegral(AEdit, BEdit);
			this->simpson = simpsonIntegral(AEdit, BEdit);
			this->midpoint = midpointIntegral(AEdit, BEdit);
			
			InvalidateRect(this->IntegralWnd, NULL, TRUE);

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