
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

// ======== Direct2D ========
#include "CD2DCore.h"
// ==========================

static TCHAR szWindowClass[] = _T("DesktopApp");
static TCHAR szTitle[] = _T("Windows Desktop Guided Tour Application");

HINSTANCE hInst;
HWND g_hWnd;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void Init();
void RunGameCode();

int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow
)
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
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Windows Desktop Guided Tour"),
			NULL);

		return 1;
	}

	hInst = hInstance;

	g_hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		800, 600,
		NULL,
		NULL,
		hInstance,
		NULL);

	if (!g_hWnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("Windows Desktop Guided Tour"),
			NULL);

		return 1;
	}

	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);

	Init();

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
			RunGameCode();
		}
	}

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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
	case WM_COMMAND:
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

ID2D1Factory* g_pD2D1Factory = nullptr;
IDWriteFactory* g_pDWriteFactory = nullptr;

ID2D1HwndRenderTarget* g_pRenderTarget = nullptr;
IDWriteTextFormat* g_pDWriteTextFormat = nullptr;
static const WCHAR fontName[] = L"Gabriola";
const FLOAT fontSize = 50.f;
WCHAR wcText[] = L"Hello World!";
ID2D1SolidColorBrush* g_pBlackBrush;
D2D1_SIZE_F rtSize;

void Init()
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	CD2DCore::GetInst()->Init();

	g_pD2D1Factory = *(CD2DCore::GetInst()->GetD2D1Factory());
	g_pDWriteFactory = *(CD2DCore::GetInst()->GetDWriteFactory());

	g_pD2D1Factory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(g_hWnd,
			D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top)),
		&g_pRenderTarget);

	rtSize = g_pRenderTarget->GetSize();

	g_pRenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Black), &g_pBlackBrush);

	g_pDWriteFactory->CreateTextFormat(
		fontName, NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		fontSize, L"en-us", &g_pDWriteTextFormat);
}

void RunGameCode()
{
	g_pRenderTarget->BeginDraw();
	// ======= Drawing =======

	g_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Blue));
	g_pRenderTarget->DrawTextW(wcText, ARRAYSIZE(wcText) - 1,
		g_pDWriteTextFormat, D2D1::RectF(0, 0, rtSize.width, rtSize.height),
		g_pBlackBrush);

	// =======================
	g_pRenderTarget->EndDraw();
}