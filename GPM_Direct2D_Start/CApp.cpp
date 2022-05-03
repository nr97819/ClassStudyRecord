#include "CApp.h"

CApp* CApp::m_app = nullptr;

CApp::CApp()
	: m_hInst(0)
	, m_hWnd(0)
	, m_ptResolution{}
	, m_rtWndSize{}
	, m_pD2DFactory(nullptr)
	, m_pRenderTarget(nullptr)
	, m_pBlackBrush(0)
{
	wcscpy_s(m_szWindowClass, L"DesktopApp");
	wcscpy_s(m_szTitle, L"Windows Desktop Guided Tour Application");
}

CApp::~CApp()
{
	if (m_pRenderTarget) 
		m_pRenderTarget->Release();

	if (m_pD2DFactory) 
		m_pD2DFactory->Release();
}

HRESULT CApp::InitAPI(HINSTANCE hInstance, int nCmdShow)
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

		return E_FAIL;
	}

	m_hInst = hInstance;

	m_hWnd = CreateWindow(
		m_szWindowClass,
		m_szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		1, 1,
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

		return E_FAIL;
	}

	ShowWindow(m_hWnd, nCmdShow);
	UpdateWindow(m_hWnd);

	return S_OK;
}

HRESULT CApp::InitD2D()
{
	if(FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2DFactory)))
		return E_FAIL;

	if (FAILED(
		m_pD2DFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties()
			, D2D1::HwndRenderTargetProperties(
				m_hWnd, D2D1::SizeU(m_rtWndSize.right - m_rtWndSize.left, m_rtWndSize.bottom - m_rtWndSize.top))
			, &m_pRenderTarget)))
		return E_FAIL;

	return S_OK;
}

HRESULT CApp::Init(HINSTANCE hInstance, int nCmdShow, POINT _ptResolution)
{
	m_ptResolution = _ptResolution;
	m_rtWndSize = { 0, 0, m_ptResolution.x, m_ptResolution.y };
	AdjustWindowRect(&m_rtWndSize, WS_OVERLAPPEDWINDOW, false);

	if (FAILED(InitAPI(hInstance, nCmdShow)))
		return E_FAIL;

	if (FAILED(InitD2D()))
		return E_FAIL;

	SetWindowPos(m_hWnd
		, nullptr, 200, 200
		, m_rtWndSize.right - m_rtWndSize.left
		, m_rtWndSize.bottom - m_rtWndSize.top
		, NULL);

	m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &m_pBlackBrush);
	m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Yellow), &m_pYellowBrush);
	m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Gray), &m_pGrayBrush);

	// ============ Chapter 4 ============

	HRESULT hr = S_OK;
	hr = DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory),
		reinterpret_cast<IUnknown**>(&m_pDwriteFactory));
	if (FAILED(hr))
		return E_FAIL;

	static const WCHAR fontName[] = L"Gabriola";
	const FLOAT fontSize = 50.f;

	hr = m_pDwriteFactory->CreateTextFormat(
		fontName, NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		fontSize, L"en-us", &m_pDWTextFormat);
	if (FAILED(hr))
		return E_FAIL;

	return S_OK;
}

void CApp::Update()
{

}

void CApp::Render()
{
	m_pRenderTarget->BeginDraw();

	m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Aqua));
	//m_pRenderTarget->DrawRectangle(D2D1::RectF(100.f, 100.f, 200.f, 200.f), m_pBlackBrush);

	D2D1_SIZE_F rtSize = m_pRenderTarget->GetSize();
	UINT width = static_cast<UINT>(rtSize.width);
	UINT height = static_cast<UINT>(rtSize.height);

	for (UINT x = 0; x < width; x += 10)
	{
		m_pRenderTarget->DrawLine(
			D2D1::Point2F(static_cast<FLOAT>(x), 0.f),
			D2D1::Point2F(static_cast<FLOAT>(x), rtSize.height),
			m_pGrayBrush, 0.5f);
	}

	for (UINT y = 0; y < height; y += 10)
	{
		m_pRenderTarget->DrawLine(
			D2D1::Point2F(0.f, static_cast<FLOAT>(y)),
			D2D1::Point2F(rtSize.width, static_cast<FLOAT>(y)),
			m_pGrayBrush, 0.5f);
	}

	m_pRenderTarget->DrawRectangle(
		D2D1::RectF(rtSize.width / 2 - 100.f
					, rtSize.height / 2 - 100.f
					, rtSize.width / 2 + 100.f
					, rtSize.height / 2 + 100.f), m_pBlackBrush);

	m_pRenderTarget->FillRectangle(
		D2D1::RectF(rtSize.width / 2 - 50.f
			, rtSize.height / 2 - 50.f
			, rtSize.width / 2 + 50.f
			, rtSize.height / 2 + 50.f), m_pBlackBrush);


	// ============ Chapter 4 ============

	WCHAR wcText[] = L"Hello World";
	m_pRenderTarget->DrawTextW(wcText, ARRAYSIZE(wcText) - 1,
		m_pDWTextFormat, D2D1::RectF(400, 400, rtSize.width, rtSize.height),
		m_pBlackBrush);

	m_pRenderTarget->EndDraw();
}

MSG CApp::RunLoop()
{
	MSG msg = {};
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Render();
		}
	}

	return msg;
}

LRESULT CALLBACK CApp::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	switch (message)
	{
	case WM_CREATE:
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
	return 0;
}