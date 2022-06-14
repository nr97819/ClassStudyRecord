#include "App.h"

#include "D2DCore.h"

CApp::CApp()
	: m_hInstance(nullptr)

	, m_hMainWnd(nullptr)
	, m_pMainWindow(nullptr)
	
	, m_pToolWindow(nullptr)
	, m_hToolWnd(nullptr)
{
}

CApp::~CApp()
{
}

HRESULT CApp::Init(HINSTANCE _hInstance, int _nCmdShow)
{
	CreateWindows(_hInstance, _nCmdShow);

	return S_OK;
}

HRESULT CApp::CreateWindows(HINSTANCE _hInstance, int _nCmdShow)
{

	// [ Main ]
	m_pMainWindow = new CWindow();
	m_hMainWnd = m_pMainWindow->Create(_hInstance, _nCmdShow, L"MainApp", L"Main Window App"); // Show Window 분리 필요
	if (NULL == m_hMainWnd)	
		return E_FAIL;
	m_pMainWindow->_ShowWindow();
	m_pMainWindow->LinkRenderTarget();
	m_pMainWindow->Adjust(POINT{ 700, 700 }, POINT{ 100, 100 });


	// [ Tool ]
	m_pToolWindow = new CWindow();
	m_hToolWnd = m_pToolWindow->Create(_hInstance, _nCmdShow, L"ToolApp", L"Tool Window App");
	if (NULL == m_hToolWnd)	
		return E_FAIL;
	m_pToolWindow->_ShowWindow();
	m_pToolWindow->LinkRenderTarget(); //전용 함수 필요
	m_pToolWindow->Adjust(POINT{ 300, 700 }, POINT{ 800, 100 });



	// Tool Window 크기 조정하면 Main Window도 영향을 받아서, 되돌리는 코드
	m_pMainWindow->GetRT()->Resize({ (UINT32)700, (UINT32)700 });



	return S_OK;
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
