#pragma once

#include <Windows.h>

#include <exception>
#include <stdexcept>
#include <string>

#include "../../utils/ExpressionHelper.cpp"

using namespace std;

class Expression
{
	enum PageInteraction
	{
		GoBackClicked = 16548,
		RecalculateClicked = 15548,
	};
	private:
		const wstring ClassName{ L"ExpressionWndClass" }, AppName{ L"Выражение" };
		HWND mnWnd, ExpressionWnd, GoBackButton, RecalculateButton, AEdit, BEdit, EEdit;
		double bisection = bisectionMethod(15, 20, 0.001), chord = chordMethod(15, 20, 0.001);
		UINT widht{ 500 }, height{ 500 };
		HINSTANCE hInstance;
		// TODO: Not implemented
	public:
		explicit Expression(HWND &mnWnd, HINSTANCE &hInstance);

		void ShowHWND(int nCmdShow) const;

	private:
		static LRESULT CALLBACK ExpressionProc(HWND, UINT, WPARAM, LPARAM);
		LRESULT CALLBACK windowProc(HWND, UINT, WPARAM, LPARAM);
		LRESULT CALLBACK handleCommand(HWND, UINT, WPARAM, LPARAM);
		void initNativeObj();
		void createNativeControls();
};

