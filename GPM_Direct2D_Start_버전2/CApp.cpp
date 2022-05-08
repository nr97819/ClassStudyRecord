#include "CApp.h"

#include "CTimeMgr.h"
#include "CAnimMgr.h"

#include "CSprite.h"
#include "CAnimation.h"

CApp* CApp::m_app = nullptr;

CApp::CApp()
	: m_hInst(0)
	, m_hWnd(0)
	, m_ptResolution{}
	, m_rtWndSize{}
	//, m_sprite{}
	//, m_iAnimCount(0)
	, m_pD2DFactory(nullptr)
	, m_pRenderTarget(nullptr)
	, m_bitmap(nullptr)
	, m_bitmap_woman(nullptr)
	, m_pSprites(nullptr)
	, m_pSprites_woman(nullptr)
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

	CTimeMgr::GetInst()->ReleaseInst();
	CAnimMgr::GetInst()->ReleaseInst();

	/*if (nullptr != m_bitmap)
		delete m_bitmap;

	if (nullptr != m_pBitmap)
		m_pBitmap->Release();

	if (nullptr != m_pRenderTarget)
		m_pRenderTarget->Release();

	if (nullptr != m_pD2DFactory)
		m_pD2DFactory->Release();

	if (nullptr != m_pWICFactory)
		CoUninitialize();*/
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
	if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2DFactory)))
		return E_FAIL;

	if (FAILED(
		m_pD2DFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(
				m_hWnd, D2D1::SizeU(
					m_rtWndSize.right - m_rtWndSize.left,
					m_rtWndSize.bottom - m_rtWndSize.top)),
			&m_pRenderTarget)))
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

	// Timer
	CTimeMgr::GetInst()->Init();
	CAnimMgr::GetInst()->Init();

	// Animation [1]
	UINT iMAxClip = 4;
	m_bitmap = new CBitmap();
	WCHAR srcName[64] = L"midnight.png";
	m_bitmap->Init(m_pRenderTarget, srcName);

	UINT index = 0;
	m_pSprites = new CSprite[iMAxClip]{};
	D2D1_RECT_F dRectF = {};
	for (UINT y = 0; y < 2; ++y)
	{
		for (UINT x = 0; x < 2; ++x)
		{
			dRectF = { (789.f * (float)x),
						(325.f * (float)y),
						784.f + (789.f * (float)x),
						320.f + (325.f * (float)y) };
			m_pSprites[index] = new CSprite(m_bitmap->GetBitmap(), dRectF);
			++index;
		}
	}
	CAnimMgr::GetInst()->GetAnimMidnight()->SetMaxClip(iMAxClip);
	CAnimMgr::GetInst()->GetAnimMidnight()->SetInterval(0.1);
	CAnimMgr::GetInst()->GetAnimMidnight()->SetClipBuffer(m_pSprites);
	CAnimMgr::GetInst()->GetAnimMidnight()->SetStartPos(0.f, 0.f);

	// Animation [2]
	UINT iMAxClip_woman = 4;
	m_bitmap_woman = new CBitmap();
	WCHAR srcName_woman[64] = L"stardewvalley_woman.png";
	m_bitmap_woman->Init(m_pRenderTarget, srcName_woman);

	UINT index_woman = 0;
	m_pSprites_woman = new CSprite[iMAxClip_woman]{};
	D2D1_RECT_F dRectF_woman = {};
	for (UINT y = 0; y < 1; ++y)
	{
		for (UINT x = 0; x < 4; ++x)
		{
			dRectF_woman = { 22.f + (16.f * (float)x),
						148.f + (0.f * (float)y),
						35.f + (16.f * (float)x),
						173.f + (0.f * (float)y) };
			m_pSprites_woman[index_woman] = new CSprite(m_bitmap_woman->GetBitmap(), dRectF_woman);
			++index_woman;
		}
	}
	CAnimMgr::GetInst()->GetMoveLeft()->SetMaxClip(iMAxClip_woman);
	CAnimMgr::GetInst()->GetMoveLeft()->SetInterval(0.15);
	CAnimMgr::GetInst()->GetMoveLeft()->SetClipBuffer(m_pSprites_woman);
	CAnimMgr::GetInst()->GetMoveLeft()->SetStartPos(50.f, 50.f);

	// Animation[3]
	/*WCHAR srcName_woman[64] = L"stardewvalley_woman.png";
	CAnimMgr::GetInst()->SetAnimation(srcName_woman, m_pRenderTarget, 
		4, 0.15, m_pSprites_woman, 50.f, 50.f);*/

	return S_OK;
}

void CApp::Update()
{
	CTimeMgr::GetInst()->Update();
	CAnimMgr::GetInst()->Update();
}

void CApp::Render()
{
	m_pRenderTarget->BeginDraw();
	m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
	//m_pRenderTarget->Clear(D2D1::ColorF(0xff00ff)); // ¸¶Á¨Å¸

	//m_pRenderTarget->DrawRectangle(D2D1::RectF(100.f, 100.f, 200.f, 200.f), m_pBlackBrush);
	/*
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
		*/

	//m_pRenderTarget->DrawBitmap(m_pBitmap);

	/*m_pRenderTarget->DrawBitmap(m_pBitmap,
		D2D1::RectF(10.f, 10.f, 10.f + m_pBitmap->GetSize().width, 10.f + m_pBitmap->GetSize().height)),
		0.5f,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		D2D1::RectF(0.f, 0.f, m_pBitmap->GetSize().width, m_pBitmap->GetSize().height);*/

	// Sprite
	CAnimMgr::GetInst()->Render(m_pRenderTarget);
	/*UINT index = 0;
	for (; index < 4;)
	{
		m_sprite[index]->Draw(m_pRenderTarget);
		++index;
	}*/

	m_pRenderTarget->EndDraw();
}

void CApp::Run()
{
	Update();

	Render();
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
			Run();
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
