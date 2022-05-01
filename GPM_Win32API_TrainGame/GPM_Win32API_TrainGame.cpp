#include <windows.h>

#include "CApp.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg{};
	if (false != CApp::GetInst()->Init(hInstance, nCmdShow, POINT{ 640, 640 }))
	{
		CApp::GetInst()->RunLoop(msg);
	}
	CApp::GetInst()->ReleaseInst();

	return (int)msg.wParam;
}