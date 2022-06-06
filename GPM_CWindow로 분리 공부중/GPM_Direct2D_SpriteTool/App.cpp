#include "App.h"

#include "D2DCore.h"

CApp::CApp()
	: m_hInstance(nullptr)
	, m_hMainWnd(nullptr)
	, m_pWindow(nullptr)
	//, m_pD2D1Factory(nullptr)
	//, m_pDWriteFactory(nullptr)
	//, m_pDWriteTextFormat(nullptr)
{
}

CApp::~CApp()
{
}

HRESULT CApp::Init(HINSTANCE _hInstance, int _nCmdShow)
{
	m_pWindow = new CWindow();
	m_hMainWnd = m_pWindow->Create(_hInstance, _nCmdShow);

	if (NULL != m_hMainWnd)
	{
		return S_OK;
	}
}

int CApp::Run()
{
	MSG msg = {};
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}

void CApp::Release()
{
	
}
