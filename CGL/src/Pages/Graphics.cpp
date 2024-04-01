#include "headers/Graphics.h"

Graphics::Graphics(HWND &mnHwnd, HINSTANCE &hInstance)
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
	WNDCLASSEXW GraphicsClass{ sizeof(WNDCLASSEXW) };

	GraphicsClass.cbClsExtra = 0;
	GraphicsClass.cbWndExtra = 0;
	GraphicsClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	GraphicsClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	GraphicsClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	GraphicsClass.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
	GraphicsClass.hInstance = this->hInstance;
	GraphicsClass.lpfnWndProc = this->GraphicsProc;
	GraphicsClass.lpszClassName = this->ClassName.c_str();
	GraphicsClass.lpszMenuName = nullptr;
	GraphicsClass.style = 0;

	RegisterClassExW(&GraphicsClass);

	this->GraphicsWnd = CreateWindowExW(0L, GraphicsClass.lpszClassName, this->AppName.c_str(),
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		(GetSystemMetrics(SM_CXSCREEN) - this->width) / 2u,
		(GetSystemMetrics(SM_CYSCREEN) - this->height) / 2u,
		this->width, this->height,
		this->mnWnd, nullptr, this->hInstance, this);

	if (this->GraphicsWnd == INVALID_HANDLE_VALUE)
		throw runtime_error("Unable to create main window"s);
}

void Graphics::createNativeControls()
{
	this->hdc = GetDC(this->GraphicsWnd);
}

LRESULT CALLBACK Graphics::GraphicsProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	Graphics* hGraphics = reinterpret_cast<Graphics*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

	if (hGraphics)
	{
		hGraphics->GraphicsWnd = hwnd;
		return hGraphics->windowProc(hwnd, uMsg, wParam, lParam);
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK Graphics::windowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			this->hdc = BeginPaint(hwnd, &ps);
			this->mnPen = CreatePen(PS_SOLID, 2, this->color::White);
			this->firtsGraphPen = CreatePen(PS_SOLID, 2, this->color::Green);
			this->secGraphPen = CreatePen(PS_SOLID, 2, this->color::Blue);

			SelectObject(this->hdc, mnPen);
			this->DrawAxes();
			this->DrawGraph();

			DeleteObject(this->mnPen);
			DeleteObject(this->firtsGraphPen);
			DeleteObject(this->secGraphPen);
			ReleaseDC(hwnd, this->hdc);
			EndPaint(hwnd, &ps);
			break;
		}

		case WM_SIZE:
		{
			this->width = LOWORD(lParam);
			this->height = HIWORD(lParam);
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		}

		case WM_CLOSE:
		{								// App::ButtonsInteraction::DestroyClicked
			SendMessageW(this->mnWnd, WM_COMMAND, LOWORD(1555), reinterpret_cast<LPARAM>(this->GraphicsWnd));
			return EXIT_SUCCESS;
			break;
		}

		case WM_DESTROY:
		{
			SendMessageW(this->mnWnd, WM_COMMAND, LOWORD(1555), reinterpret_cast<LPARAM>(this->GraphicsWnd));
			return EXIT_SUCCESS;
			break;
		}

		default:
		{
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
			break;
		}
	}

	return TRUE;
}

void Graphics::DrawAxes() const {
	MoveToEx(this->hdc, 0, this->height / 2, NULL); // Y
	LineTo(this->hdc, this->width, height / 2);

	MoveToEx(this->hdc, this->width / 2, 0, NULL); // X
	LineTo(this->hdc, this->width / 2, this->height);

	POINT center = POINT{ this->width / 2, this->height / 2 };

	//	x+
	for (int i = center.x; i < this->width - 8; i += 10)
	{
		MoveToEx(this->hdc, i, this->height / 2 - 3, NULL);
		LineTo(this->hdc, i, this->height / 2 + 3);
	}

	//	x-
	for (int i = center.x; i >=0 ; i -= 10)
	{
		MoveToEx(this->hdc, i, this->height / 2 - 3, NULL);
		LineTo(this->hdc, i, this->height / 2 + 3);
	}

	// y-
	for (int i = center.y; i <= this->height; i += 10) {
		MoveToEx(this->hdc, this->width / 2 - 3, i, NULL);
		LineTo(this->hdc, this->width / 2 + 3, i);
	}

	// y+
	for (int i = center.y; i > 8; i -= 10) {
		MoveToEx(this->hdc, this->width / 2 - 3, i, NULL);
		LineTo(this->hdc, this->width / 2 + 3, i);
	}

	// x arrow
	MoveToEx(this->hdc, this->width, this->height / 2, NULL);
	LineTo(this->hdc, this->width - 8, this->height / 2 - 5);
	MoveToEx(this->hdc, this->width, this->height / 2, NULL);
	LineTo(this->hdc, this->width- 8, this->height / 2 + 5);

	// y arrow
	MoveToEx(this->hdc, this->width / 2, 0, NULL);
	LineTo(this->hdc, this->width / 2 - 5, 0 + 8);
	MoveToEx(this->hdc, this->width / 2, 0, NULL);
	LineTo(this->hdc, this->width / 2 + 5, 0 + 8);

	// Axes namings
	SetBkColor(this->hdc, this->color::Black);
	SetTextColor(this->hdc, this->color::White);
	TextOutW(this->hdc, this->width - 10, this->height / 2 - 22, L"X", lstrlenW(L"X"));
	//TextOutW(this->hdc, 10, 10, L"X", lstrlenW(L"X"));
	TextOutW(this->hdc, this->width / 2 + 8, 0, L"Y", lstrlenW(L"Y"));
}

void Graphics::DrawGraph() {
	if (this->graphData.empty()) return;

	// Пример отрисовки одного графика (упрощенно)
	for (size_t i = 0; i < this->graphData[0].size() - 1; ++i) {
		int x1 = static_cast<int>(i * (this->width / this->graphData[0].size()));
		int y1 = this->height / 2 - static_cast<int>(this->graphData[0][i] * 20); // Умножаем на масштаб

		int x2 = static_cast<int>((i + 1) * (this->width / this->graphData[0].size()));
		int y2 = this->height / 2 - static_cast<int>(this->graphData[0][i + 1] * 20); // Умножаем на масштаб

		MoveToEx(this->hdc, x1, y1, NULL);
		LineTo(this->hdc, x2, y2);
	}
}

void Graphics::ShowHWND(int nCmdShow) const
{
	ShowWindow(this->GraphicsWnd, nCmdShow);

	UpdateWindow(this->GraphicsWnd);
}