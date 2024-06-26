#pragma once

#include <Windows.h>

#include <exception>
#include <stdexcept>
#include <string>
#include <vector>

#include "../../utils/GraphicsHelper.cpp"

using namespace std;

class Graphics
{
	enum color
	{
		Blue = RGB(0, 0, 255),
		Green = RGB(0, 255, 0),
		White = RGB(255, 255, 255),
		Black = RGB(0, 0, 0),
	};

	private:
		const wstring ClassName{ L"GraphicsWndClass" }, AppName{ L"������� �������"};
		vector<vector<double>> graphData;
		long scale = 20;
		POINT center;
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

		void DrawAxes();
		void DrawGraph();
};

