#pragma once
// New windows view
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <Windows.h>

#include <exception>
#include <stdexcept>
#include <string>

using namespace std;

class App
{
	public:
		enum class ButtonsInteraction
		{
			TableClicked = 7707,
			GraphicsClicked = 5670,
			ExpressionClicked = 8920,
			IntegralClicked = 7401,
			ScreenSaverClicked = 2398,
			AboutClicked = 4702,
			ExitClicked = 4584
		};

	private:
		const wstring AppName{ L"CGL" }, ClassName{ L"MainWndClass" };
		HWND Wnd{}, TableButton{}, GraphicsButton{}, ExpressionButton{}, IntegralButton{}, ScreenSaverButton{}, AboutButton{}, ExitButton{};
		Table* table = nullptr;
		Graphics* graphics = nullptr;
		Expression* expression = nullptr;
		Integral* integral = nullptr;
		ScreenSaver* screenSaver = nullptr;
		HINSTANCE hInstance;
		const UINT buttonWindowWidht{ 200 }, buttonWindowHeight{ 30 };
		UINT widht{ 500 }, height{ 500 };

	public:
		explicit App(HINSTANCE hInstance);
		~App();

		int Run();

	private:
		void initNativeWindowObj();
		void createNativeWindowControls();

		static LRESULT CALLBACK applicationProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		LRESULT CALLBACK windowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		LRESULT CALLBACK handleCommand(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		static LRESULT CALLBACK AboutProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

		pair<UINT, UINT> buttonDefaultClientXY(UINT Widht, UINT Height);
		void ButtonPosResize(HWND hwnd, LPARAM lParam);
};