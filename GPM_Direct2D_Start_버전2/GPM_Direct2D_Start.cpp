
#include <windows.h>
#include <stdlib.h>
#include <string.h>

#include "CApp.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg = {};

	if (!FAILED(CApp::GetInst()->Init(hInstance, nCmdShow, POINT{800, 400})))
	{
		msg = CApp::GetInst()->RunLoop();
	}
	CApp::GetInst()->ReleaseInst();

	return (int)msg.wParam;
}