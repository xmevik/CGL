#include <windows.h>
#include"Pages/headers/App.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
	App app{hInstance};

	return app.Run();
}