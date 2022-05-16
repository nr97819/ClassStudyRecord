
#include <windows.h>

#include "CGameApp.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int msg;
	CGameApp gameApp;

	if (!FAILED(gameApp.Init(hInstance, nCmdShow)))
	{
		msg = gameApp.RunLoop();
	}
	gameApp.Release();

	return msg;
}

