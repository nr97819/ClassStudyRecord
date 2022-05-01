#include "CApp.h"

#include "CInputMgr.h"

CApp* CApp::m_app = nullptr;

CApp::CApp()
	: m_hWnd(0)
	, m_hInst(0)
	, m_hDC(0)
	, m_hMemDC(0)

	, m_szWindowClass{}
	, m_szTitle{}
	, m_pResolution{}
{
	wcscpy_s(m_szWindowClass, L"DesktopApp");
	wcscpy_s(m_szTitle, L"Windows Desktop Guided Tour Application");
}

CApp::~CApp()
{}

void CApp::ReleaseInst()
{
	if (nullptr != m_app)
		delete m_app;

	if (nullptr != m_hDC)
		DeleteDC(m_hDC);

	if (nullptr != m_hMemDC)
		DeleteDC(m_hMemDC);
}

LRESULT CALLBACK CApp::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return m_app->MyProc(hWnd, message, wParam, lParam);
}

LRESULT CALLBACK CApp::MyProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	switch (_message)
	{
	case WM_CREATE:
		break;
	case WM_PAINT:
		hdc = BeginPaint(_hWnd, &ps);
		EndPaint(_hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(_hWnd, _message, _wParam, _lParam);
		break;
	}
	return 0;
}

bool CApp::InitAPI(HINSTANCE hInstance, int nCmdShow)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = m_szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			L"Call to RegisterClassEx failed!",
			L"Windows Desktop Guided Tour",
			NULL);

		return false;
	}

	m_hInst = hInstance;

	m_hWnd = CreateWindow(
		m_szWindowClass,
		m_szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		1, 1, // 의미 없는 값 (Init에서 바뀔 값)
		NULL,
		NULL,
		hInstance,
		NULL);

	if (!m_hWnd)
	{
		MessageBox(NULL,
			L"Call to CreateWindow failed!",
			L"Windows Desktop Guided Tour",
			NULL);

		return false;
	}

	ShowWindow(m_hWnd, nCmdShow);
	UpdateWindow(m_hWnd);

	return true;
}

void CApp::RunLoop(MSG& _msg)
{
	while (true)
	{
		if (PeekMessage(&_msg, NULL, 0, 0, PM_REMOVE))
		{
			if (_msg.message == WM_QUIT)
				break;

			TranslateMessage(&_msg);
			DispatchMessage(&_msg);
		}
		else
		{
			Progress();
		}
	}
}

bool CApp::Init(HINSTANCE hInstance, int nCmdShow, POINT _pResolution)
{
	InitAPI(hInstance, nCmdShow);

	// 해상도 받아서 적용
	m_pResolution = _pResolution;
	RECT rt = { 0, 0, m_pResolution.x, m_pResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false); // wMain과는 다르게 데스크탑App이라 메뉴 없었다
	SetWindowPos(m_hWnd, nullptr, 350, 150, rt.right - rt.left, rt.bottom - rt.top, NULL);

	m_hInst = 0;
	m_hDC = 0;
	m_hMemDC = 0;

	// Manager Init =========================
	CInputMgr::GetInst()->Init();
	CGame::GetInst()->Init(m_hDC);
	// ======================================

	m_hDC = GetDC(m_hWnd);
	m_hBitmap = CreateCompatibleBitmap(m_hDC, m_pResolution.x, m_pResolution.y);
	m_hMemDC = CreateCompatibleDC(m_hDC);
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);
	DeleteObject(hOldBitmap);

	return true;
}

void CApp::Progress()
{
	// Update
	Update();

	// Render
	Render();
}

void CApp::Update()
{
	CInputMgr::GetInst()->Update();
	CGame::GetInst()->Update();
}

void CApp::Render()
{
	// Clear Screen
	Rectangle(m_hMemDC, -1, -1, m_pResolution.x + 1, m_pResolution.y + 1);

	// Render Proc
	CGame::GetInst()->Render(m_hMemDC, m_pResolution);


	// TEST ===================
	/*POINT pPos = CInputProc::GetInst()->GetMousePos();
	Rectangle(m_hMemDC, 0, 0, pPos.x, pPos.y);*/


	// Double Buffering
	BitBlt(m_hDC, 0, 0, m_pResolution.x, m_pResolution.y
		, m_hMemDC, 0, 0, SRCCOPY);
	/*BitBlt(m_hDC, 0, 0, m_pResolution.x, m_pResolution.y
		, m_hBmpDC, 0, 0, SRCCOPY);*/
}