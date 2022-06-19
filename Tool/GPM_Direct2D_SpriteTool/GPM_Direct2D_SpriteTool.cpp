
#include <windows.h>

#include "App.h"

int CALLBACK WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpCmdLine, int _nCmdShow)
{
	int msg = {};

	CApp app;
	if (SUCCEEDED(app.Init(_hInstance, _nCmdShow)))
	{
		msg = app.Run();
	}
	app.Release();

	return msg;
}

