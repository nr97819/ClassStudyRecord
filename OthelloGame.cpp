#include <Windows.h>
#include <cstdio>

#include "App.h"

int CALLBACK WinMain(_In_ HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;

	CApp app;
	CApp::CreateMyApp();
	if (app.Initialize(hInstance, nCmdShow))
	{
		msg = app.RunLoop();
	}
	CApp::DeleteMyApp();

	return (int)msg.wParam;
}
