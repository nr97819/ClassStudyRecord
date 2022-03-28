#include "App.h"
#include "Game.h"

#include <vector>

CApp* CApp::m_app = nullptr;

CApp::CApp()
{
	memset(m_field, 0, sizeof(int) * 64);
	m_field[3][3] = 1;
	m_field[4][4] = 1;
	m_field[3][4] = 2;
	m_field[4][3] = 2;

	m_pCurrentMousePos = {};
	m_pCirclePos = { 0,0 };
	m_pCircleSize = { 50, 50 };
	m_bBlackTurn = true;

	m_whiteBrush = CreateSolidBrush(RGB(255, 255, 255));
	m_blackBrush = CreateSolidBrush(RGB(0, 0, 0));
	m_greenBrush = CreateSolidBrush(RGB(0, 255, 0));
}

CApp::~CApp()
{

}

LRESULT CALLBACK CApp::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return m_app->MyProc(hWnd, message, wParam, lParam);
}

LRESULT CALLBACK CApp::MyProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_CREATE:
		break;

	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		OnRender(hdc);
		EndPaint(hWnd, &ps);
	}
	break;

	case WM_TIMER:
		InvalidateRgn(hWnd, NULL, TRUE);
		break;

	case WM_LBUTTONDOWN:
	{
		m_pCurrentMousePos.x = LOWORD(lParam) - 50;
		m_pCurrentMousePos.y = HIWORD(lParam) - 50;

		bool bValidBlock = true;
		int cx = 0, cy = 0;
		if (!ConvertPosToBlock(m_pCurrentMousePos.x, cx)) bValidBlock = false;
		if (!ConvertPosToBlock(m_pCurrentMousePos.y, cy)) bValidBlock = false;

		if (bValidBlock)
		{
			if (m_field[cy][cx] == PC_None)
			{
				if (m_bBlackTurn)
				{
					m_field[cy][cx] = PC_Black;
					m_bBlackTurn = false;
				}
				else
				{
					m_field[cy][cx] = PC_White;
					m_bBlackTurn = true;
				}

				// @@@@@@@@@@@@@@@@@@@@@@@@ TEST @@@@@@@@@@@@@@@@@@@@@@@@@
				POINT p;
				p.y = cy;
				p.x = cx;
				FlipStones(p);

				if (m_nowColor == PC_Black)
					m_nowColor = PC_White;
				else if (m_nowColor == PC_White)
					m_nowColor = PC_Black;
				// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			}
			else { /*이미 놓인 자리 (놓을 수 없는 자리)*/ }
		}

		InvalidateRgn(hWnd, NULL, TRUE);
	}
	break;

	/*
	case WM_LBUTTONUP:
		//InvalidateRgn(hWnd, NULL, TRUE);
		break;

	case WM_MOUSEMOVE:
	{
		m_pCurrentMousePos.x = LOWORD(lParam);
		m_pCurrentMousePos.y = HIWORD(lParam);
		//InvalidateRgn(hWnd, NULL, TRUE);
		break;
	}
	*/

	case WM_DESTROY:
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}

bool CApp::ConvertPosToBlock(long& _beforePos, int& _afterBlock)
{
	if (_beforePos > 0)
	{
		if (_beforePos < 50)
			_afterBlock = 0;
		else if (_beforePos < 100)
			_afterBlock = 1;
		else if (_beforePos < 150)
			_afterBlock = 2;
		else if (_beforePos < 200)
			_afterBlock = 3;
		else if (_beforePos < 250)
			_afterBlock = 4;
		else if (_beforePos < 300)
			_afterBlock = 5;
		else if (_beforePos < 350)
			_afterBlock = 6;
		else if (_beforePos < 400)
			_afterBlock = 7;
		else
			return false;
	}
	else
		return false;

	return true;
}


void CApp::DrawCircleAtBlock(HDC _hdc, HBRUSH _brush, int _yValue, int _xValue, int _delta)
{
	HBRUSH oldBrush = (HBRUSH)SelectObject(_hdc, _brush);
	Ellipse(_hdc,
		int(_xValue - (float)_delta / 2),
		int(_yValue - (float)_delta / 2),
		int(_xValue + (float)_delta / 2),
		int(_yValue + (float)_delta / 2));
	SelectObject(_hdc, oldBrush);
}

bool CApp::Initialize(HINSTANCE hInstance, int nCmdShow)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = CApp::WndProc; // ?
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	//wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.hbrBackground = m_greenBrush;
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = m_szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL, L"Call to RegisterClassEx failed!", L"Windows Desktop Guided Tour", NULL);
		return false;
	}

	HWND hWnd = CreateWindow(
		m_szWindowClass, // 클래스 이름
		m_szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		550, 550,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (!hWnd)
	{
		MessageBox(NULL, L"Call to CreateWindow failed", L"Windows Desktop Guided Tour", NULL);
		return false;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return true;
}

MSG CApp::RunLoop()
{
	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg;
}

void CApp::CreateMyApp()
{
	if(!m_app)
		m_app = new CApp();
}

void CApp::DeleteMyApp()
{
	if (m_app)
	{
		delete m_app;
		m_app = nullptr;
	}
}

void CApp::OnRender(HDC _hdc)
{
	WCHAR mousePos[50] = {};
	swprintf_s(mousePos, L"CURSOR : ( %d, %d )", m_pCurrentMousePos.x, m_pCurrentMousePos.y);
	TextOut(_hdc, 0, 0, mousePos, wcslen(mousePos));

	for (int y = 50; y <= 450; y += 50)
	{
		MoveToEx(_hdc, 50, y, NULL);
		LineTo(_hdc, 450, y);
	}

	for (int x = 50; x <= 450; x += 50)
	{
		MoveToEx(_hdc, x, 50, NULL);
		LineTo(_hdc, x, 450);
	}

	int a1 = 75;
	int delta = 50;
	for (int yValue = a1; yValue <= 425; yValue += delta)
	{
		for (int xValue = a1; xValue <= 425; xValue += delta)
		{
			int cy = (yValue - a1) / 50;
			int cx = (xValue - a1) / 50;

			if (m_field[cy][cx] == PC_Black)
				DrawCircleAtBlock(_hdc, m_blackBrush, yValue, xValue, delta);
			else if (m_field[cy][cx] == PC_White)
				DrawCircleAtBlock(_hdc, m_whiteBrush, yValue, xValue, delta);
			else
				continue;
		}
	}
}

void CApp::FlipStones(POINT& _nowPos)
{
	FlipX(_nowPos);
	FlipMinusX(_nowPos);

	FlipY(_nowPos);
	FlipMinusY(_nowPos);

	// across
}

void CApp::FlipX(POINT& _nowPos)
{
	// test
	int reverseColor = 0;
	if (m_nowColor == PC_Black)
		reverseColor = PC_White;
	else if (m_nowColor == PC_White)
		reverseColor = PC_Black;

	std::vector<POINT> v;
	POINT p{};

	if (m_field[_nowPos.y][_nowPos.x + 1] == reverseColor)
	{
		p.y = _nowPos.y;
		p.x = _nowPos.x + 1;
		v.push_back(p);

		for (int i = 2; i < 8; ++i)
		{
			if (_nowPos.x + i >= 8)
				break;

			if (m_field[_nowPos.y][_nowPos.x + i] == reverseColor)
			{
				p.y = _nowPos.y;
				p.x = _nowPos.x + i;
				v.push_back(p);
			}

			if (m_field[_nowPos.y][_nowPos.x + i] == m_nowColor)
			{
				for (std::vector<POINT>::iterator it = v.begin(); it != v.end(); ++it)
				{
					m_field[(*it).y][(*it).x] = m_nowColor;
				}
			}

			// vector가 아니라, 그냥 for문으로 x=3 ~ x=7까지 다 뒤집기 이런식으로 하는게 맞을듯?
		}
	}
}

void CApp::FlipMinusX(POINT& _nowPos)
{

}

void CApp::FlipY(POINT& _nowPos)
{

}

void CApp::FlipMinusY(POINT& _nowPos)
{

}