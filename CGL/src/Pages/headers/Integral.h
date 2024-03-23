#pragma once

#include <Windows.h>

#include <exception>
#include <stdexcept>
#include <string>

#include "../../utils/IntegralHelper.cpp"

using namespace std;

class Integral
{
	enum PageInteraction
	{
		GoBackClicked = 16548,
		RecalculateClicked = 15548,
	};

	private:
		const wstring ClassName{ L"IntegralWndClass" }, AppName{ L"Вычисление интеграла"};
		HWND mnWnd, IntegralWnd, GoBackButton, RecalculateButton, AEdit, BEdit;
		UINT widht{ 500 }, height{ 500 };
		double midpoint = IgHelper::midpointIntegral(15, 20), simpson = IgHelper::simpsonIntegral(15, 20), trapezoidal = IgHelper::trapezoidalIntegral(15, 20);
		HINSTANCE hInstance;

	public:
		explicit Integral(HWND& mnWnd, HINSTANCE& hInstance);

		void ShowHWND(int nCmdShow) const;

	private:
		static LRESULT CALLBACK IntegralProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		LRESULT CALLBACK windowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		LRESULT CALLBACK handleCommand(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		void initNativeObj();
		void createNativeControls();
};

