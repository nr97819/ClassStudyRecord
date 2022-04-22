#include "CCore.h"

#include <time.h>

CCore* CCore::m_core = nullptr;

CCore::CCore()
	: hInst(0)
	, bmpInfo{}
	, pBitmapInfo(nullptr)
	, lpPixel(nullptr)
	, m_hDC(0)
	, m_hMemDC(0)
	, hBitmap24(0)
	, hBitmap32(0)
	, bitmap{}
	, lpDIBits(nullptr)
	, lpDIBits32(nullptr)
	, lpResultTemp(nullptr)
	, tempReadSize(0)
{
	wcscpy_s(szWindowClass, L"DesktopApp");
	wcscpy_s(szTitle, L"Windows Desktop Guided Tour Application");
}

CCore::~CCore()
{
	if (nullptr != pBitmapInfo)
		delete pBitmapInfo;
}

void CCore::ReleaseInst()
{
	if (nullptr != m_core)
		delete m_core;

	if (nullptr != m_hDC)
		DeleteDC(m_hDC);

	if (nullptr != m_hMemDC)
		DeleteDC(m_hMemDC);

	if (nullptr != hBitmap24)
		DeleteObject(hBitmap24);

	if (nullptr != hBitmap32)
		DeleteObject(hBitmap32);
}

LRESULT CALLBACK CCore::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return m_core->MyProc(hWnd, message, wParam, lParam);
}

LRESULT CALLBACK CCore::MyProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (_message)
	{
	case WM_CREATE:
		SetTimer(_hWnd, 1, 1, NULL);
		break;

	case WM_PAINT:
		hdc = BeginPaint(_hWnd, &ps);

		BitBlt(hdc, 0, 0, WIDTH, HEIGHT, m_hMemDC, 0, 0, SRCCOPY);

		EndPaint(_hWnd, &ps);
		break;

	case WM_MBUTTONDOWN:
		// 추가된 코드
		m_hDC = GetDC(_hWnd);

		InputBitmapFile(_hWnd, L"sample.bmp");

		ReleaseDC(_hWnd, m_hDC);

		InvalidateRgn(_hWnd, NULL, false);
		break;

	case WM_LBUTTONDOWN:
		break;

	case WM_RBUTTONDOWN:
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

bool CCore::Init(HINSTANCE hInstance, int nCmdShow)
{
	srand((unsigned int(time(NULL))));
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
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			L"Call to RegisterClassEx failed!",
			L"Windows Desktop Guided Tour",
			NULL);

		return false;
	}

	hInst = hInstance;

	HWND hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		700, 500,
		NULL,
		NULL,
		hInstance,
		NULL);

	if (!hWnd)
	{
		MessageBox(NULL,
			L"Call to CreateWindow failed!",
			L"Windows Desktop Guided Tour",
			NULL);

		return false;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return true;
}

void CCore::Progress(_Out_ MSG &msg)
{
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Play();
		}
	}
}

void CCore::Play()
{
	// 실행될 코드들

}