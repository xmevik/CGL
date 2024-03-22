#pragma once

#include <Windows.h>

#include <exception>
#include <stdexcept>
#include <string>

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
		double midpoint{ 5 }, simpson{ 5 }, trapezoidal{ 5 };
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

