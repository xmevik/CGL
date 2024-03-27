#include <windows.h>

namespace matrix
{
	struct GraphicsParam
	{
		HDC hdc;
		int Horzres;
		int Vertres;
		int* Parameters;
	};

	void InitPaint(HWND&, HDC&, PAINTSTRUCT*);

	void StartMessageEvent(HDC&, int& Horzres, int& Vertres);

	void GreenTextEvent(HDC&, int& Horzres, int& Vertres, int& WaitTimeGreenText);

	void NeoEvent(HDC&, int& Horzres, int& Vertres, int& WaitTimeRandomLettersOnError);
	void RandomLettersEvent(HDC&, int& Horzres, int& Vertres, int& WaitTimeRandomLettersEverywhere, int& WaitTimeRandomLettersOnError);

}
