#include <Windows.h>
#include <commctrl.h>

#include "headers/Expression.h"

Expression::Expression(HWND &mnHwnd, HINSTANCE &hInstance)
{
	this->mnWnd = mnHwnd;
	this->hInstance = hInstance;

	this->initNativeObj();
	this->createNativeControls();

	if (!SetWindowLongPtr(this->ExpressionWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this)))
		if (GetLastError() != 0)
			throw runtime_error("Can't register window pointer");
}

void Expression::initNativeObj()
{
	WNDCLASSEXW expressionClass{ sizeof(WNDCLASSEXW) };

	expressionClass.cbClsExtra = 0;
	expressionClass.cbWndExtra = 0;
	expressionClass.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	expressionClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	expressionClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	expressionClass.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
	expressionClass.hInstance = this->hInstance;
	expressionClass.lpfnWndProc = this->ExpressionProc;
	expressionClass.lpszClassName = this->ClassName.c_str();
	expressionClass.lpszMenuName = nullptr;
	expressionClass.style = 0;

	RegisterClassExW(&expressionClass);

	this->ExpressionWnd = CreateWindowExW(0L, expressionClass.lpszClassName, this->AppName.c_str(),
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		(GetSystemMetrics(SM_CXSCREEN) - this->widht) / 2u,
		(GetSystemMetrics(SM_CYSCREEN) - this->height) / 2u,
		this->widht, this->height,
		this->mnWnd, nullptr, this->hInstance, this);

	if (this->ExpressionWnd == INVALID_HANDLE_VALUE)
		throw runtime_error("Unable to create main window"s);
}
void Expression::createNativeControls()
{
	this->GoBackButton = CreateWindowExW(0l, WC_BUTTONW, L"Вернуться назад", WS_VISIBLE | WS_CHILD | ES_CENTER,
		10, 10, 150, 25, this->ExpressionWnd,
		reinterpret_cast<HMENU>(Expression::PageInteraction::GoBackClicked), nullptr, nullptr);

	this->RecalculateButton = CreateWindowExW(0l, WC_BUTTONW, L"Пересчитать интеграл", WS_VISIBLE | WS_CHILD | ES_CENTER,
		170, 10, 160, 25, this->ExpressionWnd,
		reinterpret_cast<HMENU>(Expression::PageInteraction::RecalculateClicked), nullptr, nullptr);

	this->AEdit = CreateWindowExW(0l, WC_EDITW, L"-15", WS_CHILD | WS_VISIBLE, 95, 50, 40, 20, this->ExpressionWnd, nullptr, nullptr, nullptr);

	this->BEdit = CreateWindowExW(0l, WC_EDITW, L"20", WS_CHILD | WS_VISIBLE, 95, 75, 40, 20, this->ExpressionWnd, nullptr, nullptr, nullptr);

	this->EEdit = CreateWindowExW(0l, WC_EDITW, L"0.001", WS_CHILD | WS_VISIBLE, 100, 100, 40, 20, this->ExpressionWnd, nullptr, nullptr, nullptr);
}

LRESULT CALLBACK Expression::ExpressionProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	Expression* hExpression = reinterpret_cast<Expression*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

	if (hExpression)
	{
		hExpression->ExpressionWnd = hwnd;
		return hExpression->windowProc(hwnd, uMsg, wParam, lParam);
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK Expression::windowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
		case WM_COMMAND:
		{
			return this->handleCommand(hwnd, uMsg, wParam, lParam);
		}
		case WM_PAINT:
		{
			::PAINTSTRUCT ps{};
			::HDC hdc{ BeginPaint(this->ExpressionWnd, &ps) };

			std::wstring bisectionStr, chordStr;
			if (this->bisection == -1.024)
				bisectionStr = L"Невозможные корни на концах интервала";
			else
				bisectionStr = doubleToWStringW(this->bisection, 18);

			if (this->chord == -1.024)
				chordStr = L"Невозможные корни на концах интервала";
			else
				chordStr = doubleToWStringW(this->chord, 18);

			::TextOutW(hdc, 10, 50, L"Граница A = ", ::lstrlenW(L"Граница A = "));
			::TextOutW(hdc, 10, 75, L"Граница B = ", ::lstrlenW(L"Граница B = "));
			::TextOutW(hdc, 10, 100, L"Точность E = ", ::lstrlenW(L"Точность E = "));
			::TextOutW(hdc, 10, 125, L"Вычисление уравнения методом бисекции =", ::lstrlenW(L"Вычисление уравнения методом бисекции ="));
			::TextOutW(hdc, 310, 125, bisectionStr.c_str(), ::lstrlenW(bisectionStr.c_str()));
			::TextOutW(hdc, 10, 150, L"Вычисление уравнения методом хорд =", ::lstrlenW(L"Вычисление уравнения методом хорд ="));
			::TextOutW(hdc, 285, 150, chordStr.c_str(), ::lstrlenW(chordStr.c_str()));

			EndPaint(this->ExpressionWnd, &ps);
			return TRUE;
		}
		case WM_CLOSE:
		{								// App::ButtonsInteraction::DestroyClicked
			return SendMessageW(this->mnWnd, WM_COMMAND, LOWORD(1555), reinterpret_cast<LPARAM>(this->ExpressionWnd));
		}
		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
			break;
	}
}

LRESULT CALLBACK Expression::handleCommand(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (static_cast<Expression::PageInteraction>(LOWORD(wParam)))
	{
		case Expression::PageInteraction::GoBackClicked:
		{								// App::ButtonsInteraction::DestroyClicked
			return SendMessageW(this->mnWnd, WM_COMMAND, LOWORD(1555), reinterpret_cast<LPARAM>(this->ExpressionWnd));
		}
		case Expression::PageInteraction::RecalculateClicked:
		{
			char inputAEdit[16u]{ 0 },
				 inputBEdit[16u]{ 0 },
				 inputEEdit[16u]{ 0 };

			::GetWindowTextA(this->AEdit, inputAEdit,
				sizeof(inputAEdit) / sizeof(char) - 1);

			::GetWindowTextA(this->BEdit, inputBEdit,
				sizeof(inputBEdit) / sizeof(char) - 1);

			::GetWindowTextA(this->EEdit, inputEEdit,
				sizeof(inputEEdit) / sizeof(char) - 1);

			int AEdit{ 0u },
				BEdit{ 0u };

			double EEdit{ 0u };

			AEdit = std::atoi(inputAEdit);
			BEdit = std::atoi(inputBEdit);
			EEdit = std::atof(inputEEdit);

			this->bisection = bisectionMethod(AEdit, BEdit, EEdit);
			this->chord = chordMethod(AEdit, BEdit, EEdit);

			InvalidateRect(this->ExpressionWnd, NULL, TRUE);

			return TRUE;
		}
		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}

void Expression::ShowHWND(int nCmdShow) const
{
	ShowWindow(this->ExpressionWnd, nCmdShow);
	UpdateWindow(this->ExpressionWnd);
}