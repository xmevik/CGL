#pragma once

#include <Windows.h>

#include <exception>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

class Graphics
{
	enum color
	{
		Blue = RGB(0, 0, 255),
		Green = RGB(0, 255, 0),
		White = RGB(255, 255, 255),
	};

	private:
		const wstring ClassName{ L"GraphicsWndClass" }, AppName{ L"Графики функций"};
		vector<vector<double>> graphData;
		HDC hdc;
		HPEN mnPen, firtsGraphPen, secGraphPen;
		HWND mnWnd, GraphicsWnd;
		int width{ 1001 }, height{ 563 };
		HINSTANCE hInstance;

	public:
		explicit Graphics(HWND &mnWnd, HINSTANCE &hInstance);

		void ShowHWND(int nCmdShow) const;

	private:
		static LRESULT CALLBACK GraphicsProc(HWND, UINT, WPARAM, LPARAM);
		LRESULT CALLBACK windowProc(HWND, UINT, WPARAM, LPARAM);
		void initNativeObj();
		void createNativeControls();

		void DrawAxes() const;
		void DrawGraph();
};

