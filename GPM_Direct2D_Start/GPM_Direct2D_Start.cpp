
#include <windows.h>
#include <stdlib.h>
#include <string.h>

#include "CApp.h"

#include <d2d1.h>
#pragma comment(lib, "d2d1.lib")

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg = {};

	if (!FAILED(CApp::GetInst()->Init(hInstance, nCmdShow, POINT{1000, 1000})))
	{
		msg = CApp::GetInst()->RunLoop();
	}
	CApp::GetInst()->ReleaseInst();

	return (int)msg.wParam;
}