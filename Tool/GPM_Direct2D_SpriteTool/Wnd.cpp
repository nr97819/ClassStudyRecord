#include "Wnd.h"

#include "D2DCore.h"

CWnd::CWnd()
	: m_pRenderTarget(nullptr)
	, m_hWnd(nullptr)
	, m_hInstance(0)
	, m_nCmdShow(0)

	, m_pMyBitmap(nullptr)
	, m_pMyWICBitmap(nullptr)
{
}

CWnd::~CWnd()
{
}

HWND CWnd::Create(HINSTANCE _hInstance, int _nCmdShow, 
	const wstring& _wsClassName, const wstring& _wsTitleName, PROC_FPTR _fpProc, bool _bMenu)
{
	HRESULT hr = S_OK;

	m_wClassName = _wsClassName;
	m_wTitleName = _wsTitleName;

	/*wcscpy_s(m_wsMainWndClassName, ARRAYSIZE(L"MainApp"), L"MainApp");
	wcscpy_s(m_wsMainWndTitle, ARRAYSIZE(L"Main Application"), L"Main Application");*/

	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = _fpProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = sizeof(LONG_PTR);
	wcex.hInstance = _hInstance;
	wcex.hIcon = LoadIcon(_hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	if(true == _bMenu)
		wcex.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	else
		wcex.lpszMenuName = NULL;
	wcex.lpszClassName = m_wClassName.c_str();
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			L"Call to RegisterClassEx failed!",
			L"Windows Desktop Guided Tour",
			NULL);

		return NULL;
	}

	m_hInstance = _hInstance;
	m_nCmdShow = _nCmdShow;

	m_hWnd = CreateWindow(
		m_wClassName.c_str(),
		m_wTitleName.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		1000, 1000,
		NULL,
		NULL,
		m_hInstance,
		this);

	if (!m_hWnd)
	{
		MessageBox(NULL,
			L"Call to CreateWindow failed!",
			L"Windows Desktop Guided Tour",
			NULL);

		return NULL;
	}
	
	//	CD2DCore::GetInst()->CreateMyTextFormat(L"Gabriola", 50);

	//	CD2DCore::GetInst()->GetD2D1Factory();
	//	CD2DCore::GetInst()->GetDWriteFactory();
	//	CD2DCore::GetInst()->GetWICImagingFactory();

	if (FAILED(hr))
		return NULL;
	else
		return m_hWnd;
}

HRESULT CWnd::InitTarget()
{
	HRESULT hr = S_OK;

	hr = CD2DCore::GetInst()->InitFactory();
	hr = CD2DCore::GetInst()->InitRenderTarget(m_hWnd, &m_pRenderTarget);
	if (FAILED(hr)) return E_FAIL;

	return S_OK;
}

HRESULT CWnd::InitBitmap(const wstring& _wsImageFileName)
{
	HRESULT hr = S_OK;

	m_pMyBitmap = new CBitmap();
	hr = m_pMyBitmap->Create(_wsImageFileName, m_pRenderTarget);

	m_pMyWICBitmap = new CWICBitmap();
	hr = m_pMyWICBitmap->Create(_wsImageFileName, m_pRenderTarget);
	if (FAILED(hr)) return E_FAIL;

	return S_OK;
}

void CWnd::_ShowWindow()
{
	ShowWindow(m_hWnd, m_nCmdShow);
	UpdateWindow(m_hWnd);
}

void CWnd::Adjust(const POINT& _ptResolution, const POINT& _ptPos)
{
	RECT rtResolution = { 0, 0, _ptResolution.x, _ptResolution.y };
	AdjustWindowRect(&rtResolution, WS_OVERLAPPEDWINDOW, true);
	SetWindowPos(m_hWnd, nullptr, _ptPos.x, _ptPos.y, rtResolution.right - rtResolution.left, rtResolution.bottom - rtResolution.top, 0);
}

LRESULT CALLBACK CWnd::WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
	CWnd* window = nullptr;
	if (_message == WM_NCCREATE)
	{
		LPCREATESTRUCT pCS = (LPCREATESTRUCT)_lParam;
		SetLastError(0); // 이전 오류값 지우기
		window = reinterpret_cast<CWnd*>(pCS->lpCreateParams);
		if (!SetWindowLongPtr(_hWnd, GWLP_USERDATA, (LONG_PTR)window))
		{
			if (GetLastError() != NULL)
				return E_FAIL;
		}
	}
	else { window = reinterpret_cast<CWnd*>(GetWindowLongPtr(_hWnd, GWLP_USERDATA)); }

	if (window) { return window->WndMsgProc(_hWnd, _message, _wParam, _lParam); }

	return DefWindowProc(_hWnd, _message, _wParam, _lParam);
}

void CWnd::Update()
{
	// TEST
	CD2DCore::GetInst()->Test();
}

void CWnd::Render()
{
	ID2D1HwndRenderTarget* pRenderTarget = GetRT();
	ID2D1Bitmap* pD2DBitmap = GetMyBitmap()->GetD2DBitmap();

	pRenderTarget->BeginDraw();
	D2D1_SIZE_F rtSize = pRenderTarget->GetSize();

	// clear
	pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));

	pRenderTarget->DrawBitmap(
		pD2DBitmap,
		D2D1::RectF(
			10.f, 10.f,
			10.f + pD2DBitmap->GetSize().width,
			10.f + pD2DBitmap->GetSize().height
		),
		1.0f, // Alpha 값
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		D2D1::RectF(
			0.f, 0.f,
			pD2DBitmap->GetSize().width,
			pD2DBitmap->GetSize().height
		)
	);
	pRenderTarget->EndDraw();
}

void CWnd::Release()
{
	if (m_pMyBitmap) { 
		m_pMyBitmap->Release();
		delete m_pMyBitmap;
		m_pMyBitmap = nullptr; 
	}

	if (m_pRenderTarget) { 
		m_pRenderTarget->Release();
		//delete m_pRenderTarget; // RenderTarget은 Window측에서 직접 delete해주는 것이다.
		m_pRenderTarget = nullptr;
	}
}