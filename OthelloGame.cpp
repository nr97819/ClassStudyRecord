#include <Windows.h>
#include <cstdio>

#include "App.h"

int CALLBACK WinMain(_In_ HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;

	//CApp app;
	if (CApp::GetInstance()->Initialize(hInstance, nCmdShow))
	{
		msg = CApp::GetInstance()->RunLoop();
	}
	CApp::DeleteInstance();

	return (int)msg.wParam;
}
