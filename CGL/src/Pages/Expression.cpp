#include "headers/Expression.h"

Expression::Expression(HWND &mnHwnd, HINSTANCE &hInstance)
{
	this->mnWnd = mnHwnd;
	this->hInstance = hInstance;

	this->initNativeObj();
	this->createNativeControls();
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
	this->GoBackButton = CreateWindowExW(0l, L"button", L"Вернуться назад", WS_VISIBLE | WS_CHILD | ES_CENTER,
		10, 10, 150, 25, this->ExpressionWnd,
		reinterpret_cast<HMENU>(Expression::PageInteraction::GoBackClicked), nullptr, nullptr);
}

LRESULT CALLBACK Expression::ExpressionProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	Expression* hExpression;
	if (uMsg == WM_CREATE)
	{
		hExpression = static_cast<Expression*>(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams);
		SetLastError(0);
		if (!SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(hExpression)))
			if (GetLastError() != 0)
				return false;
	}
	else
	{
		hExpression = reinterpret_cast<Expression*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	}

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
		case WM_CLOSE:
		{						// App::ButtonsInteraction::DestroyClicked
			SendMessage(this->mnWnd, WM_COMMAND, LOWORD(1555), reinterpret_cast<LPARAM>(this->ExpressionWnd));

			return TRUE;
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
		{						// App::ButtonsInteraction::DestroyClicked
			SendMessage(this->mnWnd, WM_COMMAND, LOWORD(1555), reinterpret_cast<LPARAM>(this->ExpressionWnd));

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