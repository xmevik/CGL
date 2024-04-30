#include "headers/Graphics.h"

Graphics::Graphics(HWND &mnHwnd, HINSTANCE &hInstance)
{
	this->mnWnd = mnHwnd;
	this->hInstance = hInstance;

	this->initNativeObj();
	this->createNativeControls();
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
	GraphicsClass.lpfnWndProc = this->windowProc;
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
}
void Graphics::createNativeControls()
{
	this->hdc = GetDC(this->GraphicsWnd);
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
}
void Graphics::DrawAxes() 
{
	MoveToEx(this->hdc, 0, this->height / 2, NULL); // Y
	LineTo(this->hdc, this->width, height / 2);

	MoveToEx(this->hdc, this->width / 2, 0, NULL); // X
	LineTo(this->hdc, this->width / 2, this->height);

	this->center = POINT{ this->width / 2, this->height / 2 };

	//	x+
	for (int i = this->center.x; i < this->width - 8; i += this->scale)
	{
		MoveToEx(this->hdc, i, this->height / 2 - 3, NULL);
		LineTo(this->hdc, i, this->height / 2 + 3);
	}

	//	x-
	for (int i = this->center.x; i >=0 ; i -= this->scale)
	{
		MoveToEx(this->hdc, i, this->height / 2 - 3, NULL);
		LineTo(this->hdc, i, this->height / 2 + 3);
	}

	// y-
	for (int i = this->center.y; i <= this->height; i += this->scale) {
		MoveToEx(this->hdc, this->width / 2 - 3, i, NULL);
		LineTo(this->hdc, this->width / 2 + 3, i);
	}

	// y+
	for (int i = this->center.y; i > 8; i -= this->scale) {
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
	TextOutW(this->hdc, this->width / 2 + 8, 0, L"Y", lstrlenW(L"Y"));
}
void Graphics::DrawGraph() 
{
	if (this->graphData.size() == 0)
	{
		static double a = -3.14159265358979323846, b = 3.14159265358979323846, n = 20;
		this->graphData = GhHelper::getVectorDatas(a, b, n);
	}

	bool isFirstElementFound = false;
	SelectObject(this->hdc, this->firtsGraphPen);
	for (auto& data : this->graphData)
	{
		if (!isFirstElementFound)
		{
			MoveToEx(this->hdc, center.x + (data[0] * this->scale), center.y + (data[1] * this->scale), NULL);
			isFirstElementFound = true;
			continue;
		}

		LineTo(this->hdc, center.x + (data[0] * this->scale), center.y + (data[1] * this->scale));
		if (this->graphData[graphData.size()-1] == data)
		{
			TextOutW(this->hdc, center.x + (data[0] * this->scale), center.y + (data[1] * this->scale) + 10, L"F1(X)", lstrlenW(L"F1(X)"));
		}
	}

	isFirstElementFound = false;
	SelectObject(this->hdc, this->secGraphPen);
	for (auto& data : this->graphData)
	{
		if (!isFirstElementFound)
		{
			MoveToEx(this->hdc, center.x + (data[0] * this->scale), center.y + (data[2] * this->scale), NULL);
			isFirstElementFound = true;
			continue;
		}

		LineTo(this->hdc, center.x + (data[0] * this->scale), center.y + (data[2] * this->scale));
		if (this->graphData[graphData.size()-1] == data)
		{
			TextOutW(this->hdc, center.x + (data[0] * this->scale), center.y + (data[2] * this->scale) - 25, L"F2(X)", lstrlenW(L"F2(X)"));
		}
	}
}
void Graphics::ShowHWND(int nCmdShow) const
{
	ShowWindow(this->GraphicsWnd, nCmdShow);
	UpdateWindow(this->GraphicsWnd);
}