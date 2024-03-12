#include "App.h"
#include "Table.h"
#include "Expression.h"
#include "Graphics.h"
#include "Integral.h"
#include "ScreenSaver.h"
#include "resource.h"


App::App(HINSTANCE hInstance)
{
	using namespace std;

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

App::~App()
{
}

int App::Run()
{
	HACCEL hAccelTable = LoadAcceleratorsW(this->hInstance, L"nullptr");

	MSG _msg{};

	ShowWindow(this->Wnd, SW_SHOWDEFAULT);
	UpdateWindow(this->Wnd);

	while (GetMessage(&_msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(_msg.hwnd, hAccelTable, &_msg))
		{
			TranslateMessage(&_msg);
			DispatchMessage(&_msg);
		}
	}

	return static_cast<int>(_msg.wParam);
}

void App::initNativeWindowObj()
{
	using std::runtime_error;

	WNDCLASSEXW mainClass = { sizeof(WNDCLASSEXW) };

	mainClass.cbClsExtra = 0;
	mainClass.cbWndExtra = 0;
	mainClass.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	mainClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	mainClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	mainClass.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
	mainClass.hInstance = this->hInstance;
	mainClass.lpfnWndProc = this->applicationProc;
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

	this->TableButton = CreateWindowW(L"button", L"1. Таблица данных", WS_VISIBLE | WS_CHILD | ES_CENTER,
		buttonXY.first, buttonXY.second, buttonWindowWidht, buttonWindowHeight, this->Wnd,
		reinterpret_cast<HMENU>(App::ButtonsInteraction::TableClicked), nullptr, nullptr);

	this->GraphicsButton = CreateWindowW(L"button", L"2. График данных", WS_VISIBLE | WS_CHILD | ES_CENTER,
		buttonXY.first, buttonXY.second + buttonWindowHeight * 1 + 5, buttonWindowWidht, buttonWindowHeight, this->Wnd,
		reinterpret_cast<HMENU>(App::ButtonsInteraction::GraphicsClicked), nullptr, nullptr);

	this->ExpressionButton = CreateWindowW(L"button", L"3. Уравнение", WS_VISIBLE | WS_CHILD | ES_CENTER, 
		buttonXY.first, buttonXY.second + buttonWindowHeight * 2 + 10, buttonWindowWidht, buttonWindowHeight, this->Wnd,
		reinterpret_cast<HMENU>(App::ButtonsInteraction::ExpressionClicked), nullptr, nullptr);

	this->IntegralButton = CreateWindowW(L"button", L"4. Интеграл", WS_VISIBLE | WS_CHILD | ES_CENTER, 
		buttonXY.first, buttonXY.second + buttonWindowHeight * 3 + 15, buttonWindowWidht, buttonWindowHeight, this->Wnd,
		reinterpret_cast<HMENU>(App::ButtonsInteraction::IntegralClicked), nullptr, nullptr);

	this->ScreenSaverButton = CreateWindowW(L"button", L"5. Заставка", WS_VISIBLE | WS_CHILD | ES_CENTER,
		buttonXY.first, buttonXY.second + buttonWindowHeight * 4 + 20, buttonWindowWidht, buttonWindowHeight, this->Wnd,
		reinterpret_cast<HMENU>(App::ButtonsInteraction::ScreenSaverClicked), nullptr, nullptr);

	this->AboutButton = CreateWindowW(L"button", L"6. Об авторе", WS_VISIBLE | WS_CHILD | ES_CENTER,
		buttonXY.first, buttonXY.second + buttonWindowHeight * 5 + 25, buttonWindowWidht, buttonWindowHeight, this->Wnd,
		reinterpret_cast<HMENU>(App::ButtonsInteraction::AboutClicked), nullptr, nullptr);

	this->ExitButton = CreateWindowW(L"button", L"Выход", WS_VISIBLE | WS_CHILD | ES_CENTER,
		buttonXY.first, buttonXY.second + buttonWindowHeight * 6 + 30, buttonWindowWidht, buttonWindowHeight, this->Wnd,
		reinterpret_cast<HMENU>(App::ButtonsInteraction::ExitClicked), nullptr, nullptr);

	if (!this->TableButton || !this->GraphicsButton || !this->ExpressionButton || !this->IntegralButton || !this->ScreenSaverButton || !this->AboutButton || !this->ExitButton)
		throw runtime_error("Error, can't create some of the button");

	HFONT hFont = CreateFontW(18, 0, 0, 0, FW_REGULAR, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH, L"Aldrich");

	SendMessageW(this->TableButton, WM_SETFONT, reinterpret_cast<WPARAM>(hFont), TRUE);
	SendMessageW(this->GraphicsButton, WM_SETFONT, reinterpret_cast<WPARAM>(hFont), TRUE);
	SendMessageW(this->ExpressionButton, WM_SETFONT, reinterpret_cast<WPARAM>(hFont), TRUE);
	SendMessageW(this->IntegralButton, WM_SETFONT, reinterpret_cast<WPARAM>(hFont), TRUE);
	SendMessageW(this->ScreenSaverButton, WM_SETFONT, reinterpret_cast<WPARAM>(hFont), TRUE);
	SendMessageW(this->AboutButton, WM_SETFONT, reinterpret_cast<WPARAM>(hFont), TRUE);
	SendMessageW(this->ExitButton, WM_SETFONT, reinterpret_cast<WPARAM>(hFont), TRUE);
}

LRESULT CALLBACK App::applicationProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	App* hApp;
	if (uMsg == WM_CREATE)
	{
		hApp = static_cast<App*>(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams);
		SetLastError(0);
		if (!SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(hApp)))
			if (GetLastError() != 0)
				return false;
	}
	else
	{
		hApp = reinterpret_cast<App*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	}

	if (hApp)
	{
		hApp->Wnd = hwnd;
		return hApp->windowProc(hwnd, uMsg, wParam, lParam);
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK App::windowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_COMMAND:
			return handleCommand(hwnd, uMsg, wParam, lParam);
		case WM_SIZE:
		{
			ButtonPosResize(hwnd, lParam);
			UpdateWindow(hwnd);

			return TRUE;
		}
		// Трюк ниже позволяет перетаскивать окно за любую его часть.
		case WM_LBUTTONDOWN: // Ловим нажатие ЛКМ.
		{
			// Отправляемое сообщение буквально значит "нажата ЛКМ на заголовке окна".
			::SendMessageW(hwnd, WM_NCLBUTTONDOWN, HTCAPTION, 0);
			break;
		}
		case WM_MOVING:
		{
			static const ::HCURSOR cursor{
				::LoadCursorW(nullptr, IDC_SIZEALL)
			};

			::SetCursor(cursor);
			break;
		}
		case WM_CLOSE:
		{
			if (MessageBoxW(hwnd, L"Вы действительно хотите выйти?", L"Close application", MB_OKCANCEL) == IDOK)
				DestroyWindow(hwnd);

			return EXIT_SUCCESS;
		}
		case WM_DESTROY:
		{
			PostQuitMessage(EXIT_SUCCESS);
			return 0;
		}
		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
			break;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK App::handleCommand(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (static_cast<App::ButtonsInteraction>(LOWORD(wParam)))
	{
		case App::ButtonsInteraction::TableClicked:
		{
			if (this->table == nullptr)
			{
				HINSTANCE hInstance = GetModuleHandleW(NULL);
				this->table = new Table(hwnd, hInstance);
			}
			this->table->ShowHWND(SW_SHOWDEFAULT);

			return TRUE;
		}
		case App::ButtonsInteraction::GraphicsClicked:
		{
			if (this->graphics == nullptr)
			{
				HINSTANCE hInstance = GetModuleHandleW(NULL);
				this->graphics = new Graphics(hwnd, hInstance);
			}
			this->graphics->ShowHWND(SW_SHOWDEFAULT);

			return TRUE;
		}
		case App::ButtonsInteraction::ExpressionClicked:
		{
			if (this->expression == nullptr)
			{
				HINSTANCE hInstance = GetModuleHandleW(NULL);
				this->expression = new Expression(hwnd, hInstance);
			}
			this->expression->ShowHWND(SW_SHOWDEFAULT);

			return TRUE;
		}
		case App::ButtonsInteraction::IntegralClicked:
		{
			if (this->integral == nullptr)
			{
				HINSTANCE hInstance = GetModuleHandleW(NULL);
				this->integral = new Integral(hwnd, hInstance);
			}
			this->integral->ShowHWND(SW_SHOWDEFAULT);

			return TRUE;
		}
		case App::ButtonsInteraction::ScreenSaverClicked:
		{
			if (this->screenSaver == nullptr)
			{
				HINSTANCE hInstance = GetModuleHandleW(NULL);
				this->screenSaver = new ScreenSaver(hwnd, hInstance);
			}
			this->screenSaver->ShowHWND(SW_SHOWDEFAULT);

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
		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
			break;
	}
}

pair<UINT, UINT> App::buttonDefaultClientXY(UINT Widht, UINT Height)
{
	this->widht = Widht;
	this->height = Height;

	const UINT x = this->widht / 2 - (this->buttonWindowWidht / 2);
	const UINT y = this->height / 2 - (this->buttonWindowHeight * 5);

	return make_pair(x, y);
}

void App::ButtonPosResize(HWND hwnd, LPARAM lParam)
{
	int widht = LOWORD(lParam);
	int height = HIWORD(lParam);
	const auto buttonXY = buttonDefaultClientXY(LOWORD(lParam), HIWORD(lParam));

	SetWindowPos(this->TableButton, HWND_TOP, buttonXY.first, buttonXY.second, NULL, NULL, SWP_NOSIZE | SWP_NOZORDER);
	SetWindowPos(this->GraphicsButton, HWND_TOP, buttonXY.first, buttonXY.second + buttonWindowHeight * 1 + 5, NULL, NULL, SWP_NOSIZE | SWP_NOZORDER);
	SetWindowPos(this->ExpressionButton, HWND_TOP, buttonXY.first, buttonXY.second + buttonWindowHeight * 2 + 10, NULL, NULL, SWP_NOSIZE | SWP_NOZORDER);
	SetWindowPos(this->IntegralButton, HWND_TOP, buttonXY.first, buttonXY.second + buttonWindowHeight * 3 + 15, NULL, NULL, SWP_NOSIZE | SWP_NOZORDER);
	SetWindowPos(this->ScreenSaverButton, HWND_TOP, buttonXY.first, buttonXY.second + buttonWindowHeight * 4 + 20, NULL, NULL, SWP_NOSIZE | SWP_NOZORDER);
	SetWindowPos(this->AboutButton, HWND_TOP, buttonXY.first, buttonXY.second + buttonWindowHeight * 5 + 25, NULL, NULL, SWP_NOSIZE | SWP_NOZORDER);
	SetWindowPos(this->ExitButton, HWND_TOP, buttonXY.first, buttonXY.second + buttonWindowHeight * 6 + 30, NULL, NULL, SWP_NOSIZE | SWP_NOZORDER);
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