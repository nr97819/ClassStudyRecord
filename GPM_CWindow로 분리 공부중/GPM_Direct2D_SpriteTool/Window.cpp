#include "Window.h"

#include "D2DCore.h"

CWindow::CWindow()
	: m_pMyBitmap(nullptr)
	, m_pMainRT(nullptr)
	, m_hWnd(nullptr)
{
}

CWindow::~CWindow()
{
}

HWND CWindow::Create(HINSTANCE _hInstance, int _nCmdShow)
{
	HRESULT hr = S_OK;

	hr = Init(_hInstance, _nCmdShow);

	if (FAILED(hr))
		return NULL;
	else
		return m_hWnd;
}

HRESULT CWindow::Init(HINSTANCE _hInstance, int _nCmdShow)
{
	HRESULT hr = S_OK;

	wcscpy_s(m_wsMainWndClassName, ARRAYSIZE(L"MainApp"), L"MainApp");
	wcscpy_s(m_wsMainWndTitle, ARRAYSIZE(L"Main Application"), L"Main Application");

	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = MainProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = sizeof(LONG_PTR);
	wcex.hInstance = _hInstance;
	wcex.hIcon = LoadIcon(_hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = m_wsMainWndClassName;
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			L"Call to RegisterClassEx failed!",
			L"Windows Desktop Guided Tour",
			NULL);

		return E_FAIL;
	}

	m_hWnd = CreateWindow(
		m_wsMainWndClassName,
		m_wsMainWndTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		700, 700,
		NULL,
		NULL,
		_hInstance,
		this);

	if (!m_hWnd)
	{
		MessageBox(NULL,
			L"Call to CreateWindow failed!",
			L"Windows Desktop Guided Tour",
			NULL);

		return E_FAIL;
	}

	ShowWindow(m_hWnd, _nCmdShow);
	UpdateWindow(m_hWnd);

	// D2D1
	hr = InitD2D();
	if (FAILED(hr)) return E_FAIL;

	return S_OK;
}

HRESULT CWindow::InitD2D()
{
	HRESULT hr = S_OK;

	hr = CD2DCore::GetInst()->Init(m_hWnd);
	if (FAILED(hr)) return E_FAIL;

	m_pMyBitmap = new CBitmap();
	hr = m_pMyBitmap->Create(L"woman.png");
	if (FAILED(hr)) return E_FAIL;

	//CD2DCore::GetInst()->CreateMyTextFormat(L"Gabriola", 50);
	/*CD2DCore::GetInst()->GetD2D1Factory();
	CD2DCore::GetInst()->GetDWriteFactory();
	CD2DCore::GetInst()->GetWICImagingFactory();*/
	m_pMainRT = CD2DCore::GetInst()->GetMainRT();

	return S_OK;
}

LRESULT CALLBACK CWindow::MainProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
	CWindow* window = nullptr;
	if (_message == WM_NCCREATE)
	{
		LPCREATESTRUCT pCS = (LPCREATESTRUCT)_lParam;
		SetLastError(0); // 이전 오류값 지우기
		window = reinterpret_cast<CWindow*>(pCS->lpCreateParams);
		if (!SetWindowLongPtr(_hWnd, GWLP_USERDATA, (LONG_PTR)window))
		{
			if (GetLastError() != NULL)
				return E_FAIL;
		}
	}
	else
	{
		window = reinterpret_cast<CWindow*>(GetWindowLongPtr(_hWnd, GWLP_USERDATA));
	}

	if (window)
	{
		return window->MainMsgProc(_hWnd, _message, _wParam, _lParam);
	}

	return DefWindowProc(_hWnd, _message, _wParam, _lParam);

}
LRESULT CALLBACK CWindow::MainMsgProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	int width = 0;
	int height = 0;

	switch (_message)
	{
	case WM_CREATE:
		break;

	case WM_PAINT:
		hdc = BeginPaint(_hWnd, &ps);
		EndPaint(_hWnd, &ps);
		break;

		// ======================================================
	case WM_LBUTTONDOWN:
	{
		// D2D1
		Update();
		Render();
	}
	case WM_MOUSEMOVE:
	{
		WORD x = HIWORD(_lParam);
		WORD y = LOWORD(_lParam);

		hdc = GetDC(_hWnd);

		COLORREF color = GetPixel(hdc, x, y);
		wchar_t str[100];
		wsprintf(str, L"(%d, %d) COLOR : %x", x, y, color);
		TextOut(hdc, 10, 10, str, wcslen(str));

		ReleaseDC(_hWnd, hdc);
	}
	break;
	// ======================================================

	case WM_SIZE:
	{
		width = LOWORD(_lParam);
		height = HIWORD(_lParam);

		if (CD2DCore::GetInst()->GetMainRT())
			CD2DCore::GetInst()->GetMainRT()->Resize({ (UINT32)width, (UINT32)height });
	}
	break;

	case WM_COMMAND:
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

void CWindow::Update()
{

}

void CWindow::Render()
{
	ID2D1HwndRenderTarget* pMainRT = CD2DCore::GetInst()->GetMainRT();
	ID2D1Bitmap* pD2DBitmap = CD2DCore::GetInst()->GetMainD2D1Bitmap();

	pMainRT->BeginDraw();
	D2D1_SIZE_F rtSize = pMainRT->GetSize();

	// clear
	pMainRT->Clear(D2D1::ColorF(D2D1::ColorF::White));

	pMainRT->DrawBitmap(
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
	pMainRT->EndDraw();
}

void CWindow::Release()
{
	if (m_pMyBitmap) { m_pMyBitmap->Release(); m_pMyBitmap = nullptr; }
}