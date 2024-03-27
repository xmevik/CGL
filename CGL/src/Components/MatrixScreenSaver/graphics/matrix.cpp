#include <time.h>

#include "matrix.h"

namespace
{
	HPEN Main_pen, Error_pen, Black_pen;
	HBRUSH Main_brush, Error_brush;

	namespace color
	{
		int Black = RGB(0, 0, 0);
		int Green = RGB(0, 255, 0);
	}
}

namespace
{
	void InitHpen()
	{
		Main_pen = CreatePen(PS_SOLID, 1, color::Green);
		Error_pen = CreatePen(PS_SOLID, 1, color::Green);
		Black_pen = CreatePen(PS_SOLID, 1, color::Black);
	}

	void InitHbrush()
	{
		Main_brush = CreateSolidBrush(color::Black);
		Error_brush = CreateSolidBrush(color::Green);
	}

	void WriteMessageToNeo(HDC hdc, int Horzres, int Vertres)
	{
		SetTextColor(hdc, color::Green);
		SetBkColor(hdc, color::Black);
		SelectObject(hdc, Main_pen);
		SelectObject(hdc, Main_brush);

		int _rand_x = rand() % (Horzres - 400),
			_rand_y = rand() % (Vertres - 350);

		Rectangle(hdc, _rand_x, _rand_y, _rand_x + 400, _rand_y + 100);

		wchar_t MessageToNeo1[16] = { L"Wake up, Neo..." };
		wchar_t MessageToNeo2[22] = { L"The Matrix has you..." };
		wchar_t MessageToNeo3[28] = { L"Follow the white rabbit." };

		TextOutW(hdc, _rand_x + 25, _rand_y + 20, &MessageToNeo1[0], 1);
		for (int i = 1; i < 16; i++)
		{
			TextOutW(hdc, _rand_x + 30 + i * 14, _rand_y + 20, &MessageToNeo1[i], 1);

			Sleep(100);
		}
		TextOutW(hdc, _rand_x + 200, _rand_y + 25, L" ", 1);

		Sleep(500);

		for (int i = 0; i < 22; i++)
		{
			TextOutW(hdc, _rand_x + 25 + i * 13, _rand_y + 40, &MessageToNeo2[i], 1);

			Sleep(100);
		}
		TextOutW(hdc, _rand_x + 200, _rand_y + 25, L" ", 1);

		Sleep(500);

		for (int i = 0; i < 28; i++)
		{
			TextOutW(hdc, _rand_x + 25 + i * 13, _rand_y + 60, &MessageToNeo3[i], 1);

			Sleep(100);
		}
		TextOutW(hdc, _rand_x + 200, _rand_y + 25, L" ", 1);
	}

	void WriteRandomLettersEverywhere(HDC hdc, int Horzres, int Vertres, int WaitTime) // Colorized text
	{
		for (int i = 0; i < 5 * (Horzres + Vertres); i++)
		{

			int _rand_x = rand() % Horzres,
				_rand_y = rand() % Vertres;

			int Text_color_R = rand() % 255,
				Text_color_G = rand() % 255,
				Text_color_B = rand() % 255;
			SetTextColor(hdc, RGB(Text_color_R, Text_color_G, Text_color_B));

			wchar_t symb;
			symb = (rand() % 255);
			TextOutW(hdc, _rand_x, _rand_y, &symb, 1);

			Sleep(WaitTime);
		}
	}

	void WriteRandomLettersOnError(HDC hdc, int Horzres, int Vertres, int WaitTime)
	{
		SetBkColor(hdc, color::Black);

		for (int i = 0; i < 100; i++)
		{
			int Text_color_R = rand() % 255,
				Text_color_G = rand() % 255,
				Text_color_B = rand() % 255;
			SetTextColor(hdc, RGB(Text_color_R, Text_color_G, Text_color_B));

			int _rand_x = (rand() % 300) + Horzres / 2 - 150,
				_rand_y = (rand() % 100) + Vertres / 2 - 50;

			wchar_t symb;
			symb = (rand() % 255);
			TextOutW(hdc, _rand_x, _rand_y, &symb, 1);

			Sleep(WaitTime);
		}
	}

	void Restart(HDC hdc, int Horzres, int Vertres, int WaitTime) // System restart
	{
		Sleep(3000);

		SetTextColor(hdc, color::Black);
		SetBkColor(hdc, color::Green);
		SelectObject(hdc, Error_pen);
		SelectObject(hdc, Error_brush);

		Rectangle(hdc, Horzres / 2 - 150, Vertres / 2 - 50, Horzres / 2 + 150, Vertres / 2 + 50);

		TextOutW(hdc, Horzres / 2 - 100, Vertres / 2 - 20, L"CRITICAL FAILURE IN SYSTEM", 26);
		TextOutW(hdc, Horzres / 2 - 125, Vertres / 2, L" ", 1);
		TextOutW(hdc, Horzres / 2 - 75, Vertres / 2, L"INITIATING RESTART", 18);
		TextOutW(hdc, Horzres / 2 - 125, Vertres / 2, L" ", 1);

		Sleep(2000);

		WriteRandomLettersOnError(hdc, Horzres, Vertres, WaitTime);

		Sleep(1000);

		SelectObject(hdc, Black_pen);
		SelectObject(hdc, Main_brush);

		Rectangle(hdc, 0, 0, Horzres, Vertres);

		Sleep(1000);
	}
}

namespace matrix
{
	void InitPaint(HWND& hWnd, HDC& hdc, PAINTSTRUCT* paintstruct)
	{
		hdc = BeginPaint(hWnd, paintstruct);

		InitHpen();
		InitHbrush();

		SetTextColor(hdc, color::Green);
		SetBkColor(hdc, color::Black);
	}

	void StartMessageEvent(HDC& hdc, int& Horzres, int& Vertres)
	{
		SetTextColor(hdc, color::Green);
		SetBkColor(hdc, color::Black);

		constexpr auto SM2Len = 6;
		constexpr auto SM3Len = 17;

		wchar_t StartMessage2[SM2Len] = { L"start" };
		wchar_t StartMessage3[SM3Len] = { L" Calculating.exe" };

		TextOutW(hdc, 0, 0, L">", 1);
		TextOutW(hdc, Horzres, Vertres, L" ", 1);
		Sleep(2000);

		TextOutW(hdc, 8, 0, StartMessage2, SM2Len);
		Sleep(150);

		TextOutW(hdc, 8 + SM2Len * 5, 0, StartMessage3, SM3Len);

		for (int i = 0; i < 5; i++)
		{
			TextOutW(hdc, 10 + SM2Len * 5 + SM3Len * 6, 0, L"_", 1);
			Sleep(500);
			TextOutW(hdc, 10 + SM2Len * 5 + SM3Len * 6, 0, L"  ", 2);
			Sleep(500);
		}
	}

	void GreenTextEvent(HDC& hdc, int& Horzres, int& Vertres, int& WaitTimeGreenText)
	{
		SetTextColor(hdc, color::Green);
		SetBkColor(hdc, color::Black);
		SelectObject(hdc, Main_pen);
		SelectObject(hdc, Main_brush);

		for (int i = 0; i < Vertres / 10; i++)
		{
			for (int j = 0; j < Horzres / 10; j++)
			{

				wchar_t symb;
				symb = (rand() % 255);
				TextOutW(hdc, j * 10, i * 10, &symb, 1);
			}
			Sleep(WaitTimeGreenText);
		}
	}

	void NeoEvent(HDC& hdc, int& Horzres, int& Vertres, int& WaitTimeRandomLettersOnError)
	{
		WriteMessageToNeo(hdc, Horzres, Vertres);
		Restart(hdc, Horzres, Vertres, WaitTimeRandomLettersOnError);
	}


	void RandomLettersEvent(HDC& hdc, int& Horzres, int& Vertres, int& WaitTimeRandomLettersEverywhere, int& WaitTimeRandomLettersOnError)
	{
		WriteRandomLettersEverywhere(hdc, Horzres, Vertres, WaitTimeRandomLettersEverywhere);
		Restart(hdc, Horzres, Vertres, WaitTimeRandomLettersOnError);
	}
}