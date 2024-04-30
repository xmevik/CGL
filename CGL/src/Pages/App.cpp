#include <Windows.h>
#include <commctrl.h>
#include "headers/App.h"
#include "headers/Table.h"
#include "headers/Expression.h"
#include "headers/Graphics.h"
#include "headers/Integral.h"
#include "headers/ScreenSaver.h"
#include "resource.h"

App::App(HINSTANCE hInstance)
{
	try
	{
		this->hInstance = hInstance;

		this->initNativeWindowObj();
		this->createNativeWindowControls();
	}
	catch (const exception& e)
	{
		string exptData = e.what();

		MessageBoxW(nullptr, wstring(begin(exptData), end(exptData)).c_str(), L"Ошибка", MB_ICONERROR | MB_OK);
		ExitProcess(EXIT_FAILURE);
	}
}

int App::Run() const
{
	MSG _msg{};

	ShowWindow(this->Wnd, SW_SHOWDEFAULT);
	UpdateWindow(this->Wnd);

	while (GetMessage(&_msg, nullptr, 0, 0))
	{
		TranslateMessage(&_msg);
		DispatchMessage(&_msg);
	}

	return static_cast<int>(_msg.wParam);
}
void App::initNativeWindowObj()
{
	WNDCLASSEXW mainClass = { sizeof(WNDCLASSEXW) };

	mainClass.cbClsExtra = 0;
	mainClass.cbWndExtra = 0;
	mainClass.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	mainClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	mainClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	mainClass.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
	mainClass.hInstance = this->hInstance;
	mainClass.lpfnWndProc = this->windowProc;
	mainClass.lpszClassName = this->ClassName.c_str();
	mainClass.lpszMenuName = nullptr;
	mainClass.style = 0;

	if (!RegisterClassExW(&mainClass))
		throw runtime_error("Unable to register main window class"s);

	this->Wnd = CreateWindowExW(0l,  this->ClassName.c_str(), this->AppName.c_str(),
								WS_OVERLAPPEDWINDOW | WS_VISIBLE,
								(GetSystemMetrics(SM_CXSCREEN) - this->widht) / 2u,
								(GetSystemMetrics(SM_CYSCREEN) - this->height) / 2u,
								this->widht, this->height,
								nullptr, nullptr, mainClass.hInstance, this);

	if (this->Wnd == INVALID_HANDLE_VALUE)
		throw runtime_error("Unable to create main window"s);
}
void App::createNativeWindowControls()
{
	const auto buttonXY = buttonDefaultClientXY(widht, height);

	this->TableButton = CreateWindowW(WC_BUTTONW, L"1. Таблица данных", WS_VISIBLE | WS_CHILD | ES_CENTER,
		buttonXY.first, buttonXY.second, buttonWindowWidht, buttonWindowHeight, this->Wnd,
		reinterpret_cast<HMENU>(App::ButtonsInteraction::TableClicked), nullptr, nullptr);

	this->GraphicsButton = CreateWindowW(WC_BUTTONW, L"2. График данных", WS_VISIBLE | WS_CHILD | ES_CENTER,
		buttonXY.first, buttonXY.second + buttonWindowHeight * 1 + 5, buttonWindowWidht, buttonWindowHeight, this->Wnd,
		reinterpret_cast<HMENU>(App::ButtonsInteraction::GraphicsClicked), nullptr, nullptr);

	this->ExpressionButton = CreateWindowW(WC_BUTTON, L"3. Уравнение", WS_VISIBLE | WS_CHILD | ES_CENTER,
		buttonXY.first, buttonXY.second + buttonWindowHeight * 2 + 10, buttonWindowWidht, buttonWindowHeight, this->Wnd,
		reinterpret_cast<HMENU>(App::ButtonsInteraction::ExpressionClicked), nullptr, nullptr);

	this->IntegralButton = CreateWindowW(WC_BUTTON, L"4. Интеграл", WS_VISIBLE | WS_CHILD | ES_CENTER,
		buttonXY.first, buttonXY.second + buttonWindowHeight * 3 + 15, buttonWindowWidht, buttonWindowHeight, this->Wnd,
		reinterpret_cast<HMENU>(App::ButtonsInteraction::IntegralClicked), nullptr, nullptr);

	this->ScreenSaverButton = CreateWindowW(WC_BUTTON, L"5. Заставка", WS_VISIBLE | WS_CHILD | ES_CENTER,
		buttonXY.first, buttonXY.second + buttonWindowHeight * 4 + 20, buttonWindowWidht, buttonWindowHeight, this->Wnd,
		reinterpret_cast<HMENU>(App::ButtonsInteraction::ScreenSaverClicked), nullptr, nullptr);

	this->AboutButton = CreateWindowW(WC_BUTTON, L"6. Об авторе", WS_VISIBLE | WS_CHILD | ES_CENTER,
		buttonXY.first, buttonXY.second + buttonWindowHeight * 5 + 25, buttonWindowWidht, buttonWindowHeight, this->Wnd,
		reinterpret_cast<HMENU>(App::ButtonsInteraction::AboutClicked), nullptr, nullptr);

	this->ExitButton = CreateWindowW(WC_BUTTON, L"Выход", WS_VISIBLE | WS_CHILD | ES_CENTER,
		buttonXY.first, buttonXY.second + buttonWindowHeight * 6 + 30, buttonWindowWidht, buttonWindowHeight, this->Wnd,
		reinterpret_cast<HMENU>(App::ButtonsInteraction::ExitClicked), nullptr, nullptr);

	if (!this->TableButton || !this->GraphicsButton || !this->ExpressionButton || !this->IntegralButton || !this->ScreenSaverButton || !this->AboutButton || !this->ExitButton)
		throw runtime_error("Error, can't create some of the button");
}
LRESULT CALLBACK App::windowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_COMMAND:
			return handleCommand(hwnd, uMsg, wParam, lParam);
		case WM_DESTROY:
		{
			PostQuitMessage(EXIT_SUCCESS);
			return 0;
		}
		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
			break;
	}
}
LRESULT CALLBACK App::handleCommand(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (static_cast<App::ButtonsInteraction>(LOWORD(wParam)))
	{
		case App::ButtonsInteraction::TableClicked:
		{
			HINSTANCE hInstance = GetModuleHandleW(NULL);
			this->table = new Table(hwnd, hInstance);

			this->table->ShowHWND(SW_SHOWDEFAULT);

			return TRUE;
		}
		case App::ButtonsInteraction::GraphicsClicked:
		{
			HINSTANCE hInstance = GetModuleHandleW(NULL);
			this->graphics = new Graphics(hwnd, hInstance);

			this->graphics->ShowHWND(SW_SHOWDEFAULT);

			return TRUE;
		}
		case App::ButtonsInteraction::ExpressionClicked:
		{
			HINSTANCE hInstance = GetModuleHandleW(NULL);
			this->expression = new Expression(hwnd, hInstance);

			this->expression->ShowHWND(SW_SHOWDEFAULT);

			return TRUE;
		}
		case App::ButtonsInteraction::IntegralClicked:
		{
			HINSTANCE hInstance = GetModuleHandleW(NULL);
			this->integral = new Integral(hwnd, hInstance);

			this->integral->ShowHWND(SW_SHOWDEFAULT);

			return TRUE;
		}
		case App::ButtonsInteraction::ScreenSaverClicked:
		{
			HINSTANCE hInstance = GetModuleHandleW(NULL);
			this->screenSaver = new ScreenSaver(hwnd, hInstance);

			this->screenSaver->ShowHWND();

			return TRUE;
		}
		case App::ButtonsInteraction::AboutClicked:
		{
			DialogBoxW(nullptr, MAKEINTRESOURCEW(IDD_ABOUTBOX), hwnd, AboutProc);
			return TRUE;
		}
		case App::ButtonsInteraction::ExitClicked:
		{
			if (MessageBoxW(hwnd, L"Вы действительно хотите выйти?", L"Close application", MB_OKCANCEL) == IDOK)
				DestroyWindow(hwnd);

			return EXIT_SUCCESS;
		}
		case App::ButtonsInteraction::DestroyClicked:
		{
			HWND wnd = reinterpret_cast<HWND>(lParam);
			if(wnd != this->prevClosedWnd)
				if (MessageBoxW(hwnd, L"Это действие закроет окно", L"Close window", MB_OKCANCEL) == IDOK)
				{
					this->prevClosedWnd = wnd;
					DestroyWindow(wnd);
				}
			return EXIT_SUCCESS;
		}
		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
			break;
	}
}
LRESULT CALLBACK App::AboutProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (uMsg)
	{
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			EndDialog(hwnd, LOWORD(wParam));
			return TRUE;
		}
		break;
	}
	return FALSE;
}