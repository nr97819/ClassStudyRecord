#include "App.h"
#include "Game.h"

#include <vector>

CApp* CApp::m_app = nullptr;

CApp::CApp()
{
	m_game = new CGame();

	m_greenBrush = CreateSolidBrush(RGB(140, 255, 140));
}

CApp::~CApp()
{
	if(m_game)
		delete m_game;

	DeleteObject(m_greenBrush);
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

	case WM_LBUTTONUP:
	{
		/*long mouseY = HIWORD(lParam) - 50;
		long mouseX = LOWORD(lParam) - 50;

		m_game->SetCurrentMousePosY(mouseY);
		m_game->SetCurrentMousePosX(mouseX);

		if (mouseY < 0 || mouseY >= 400) break;
		if (mouseX < 0 || mouseX >= 400) break;*/

		//if (!m_game->IsGameOver())
		//{
		//	POINT p;
		//	p.y = HIWORD(lParam);
		//	p.x = LOWORD(lParam);

		//	if (m_game->PutStone(p)) // 돌 두기
		//	{
		//		m_game->IsCurrentTurnWin(p);
		//		if(!m_game->IsGameOver())
		//			m_game->ChangeTurn(); // 턴 교체
		//	}
		//}
		
		POINT p;
		p.y = HIWORD(lParam);
		p.x = LOWORD(lParam);

		if (!m_game->GetGameOver())
		{
			if (!m_game->PutStone(p)) // 돌 두기
			{
				InvalidateRgn(hWnd, NULL, TRUE);
				break;
			}

			if (m_game->IsCurrentTurnWin(p))
			{
				m_game->SetGameOver(TRUE);
				InvalidateRgn(hWnd, NULL, TRUE);
				break;
			}

			m_game->ChangeTurn(); // 턴 교체
			InvalidateRgn(hWnd, NULL, TRUE);
		}

	}
		break;

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
		650, 650,
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

void CApp::OnRender(HDC _hdc)
{
	m_game->Render(_hdc);

	//WCHAR text[50] = {};
	//WCHAR winner[30] = {};

	//int totalStoneCount = m_game->GetBlackCount() + m_game->GetWhiteCount();
	//if (totalStoneCount == 64)
	//{
	//	if (m_game->GetBlackCount() > m_game->GetWhiteCount())
	//		swprintf_s(winner, L"Winner! [Black]");
	//	else if (m_game->GetBlackCount() < m_game->GetWhiteCount())
	//		swprintf_s(winner, L"Winner! [White]");
	//	else
	//		swprintf_s(winner, L"DRAW...");
	//	
	//	TextOut(_hdc, 200, 200, winner, wcslen(winner));
	//}
	//else
	//{
	//	for (int y = 50; y <= 450; y += 50)
	//	{
	//		MoveToEx(_hdc, 50, y, NULL);
	//		LineTo(_hdc, 450, y);
	//	}

	//	for (int x = 50; x <= 450; x += 50)
	//	{
	//		MoveToEx(_hdc, x, 50, NULL);
	//		LineTo(_hdc, x, 450);
	//	}

	//	int a1 = 75;
	//	int delta = 50; // 50이 꽉차는 크기임
	//	int** field = *(m_game->GetField());
	//	for (int yValue = a1; yValue <= 425; yValue += delta)
	//	{
	//		for (int xValue = a1; xValue <= 425; xValue += delta)
	//		{
	//			int cy = (yValue - a1) / 50;
	//			int cx = (xValue - a1) / 50;

	//			POINT p;
	//			p.y = cy;
	//			p.x = cx;

	//			if (field[cy][cx] == PC_Black)
	//				DrawCircleAtBlock(_hdc, m_blackBrush, yValue, xValue, delta);
	//			else if (field[cy][cx] == PC_White)
	//				DrawCircleAtBlock(_hdc, m_whiteBrush, yValue, xValue, delta);				
	//			else
	//				continue;
	//			/*else if (field[cy][cx] == PC_None)
	//			{
	//			if (m_game->FlipStones(p))
	//				DrawCircleAtBlock(_hdc, m_greenBrush, yValue, xValue, delta);
	//			}*/
	//		}
	//	}
	//}

	//swprintf_s(text, L"CURSOR : ( %d, %d )", m_game->GetCurrentMousePos().x, m_game->GetCurrentMousePos().y);
	//TextOut(_hdc, 0, 0, text, wcslen(text));

	//swprintf_s(text, L"BlackCount : ( %d ) WhiteCount : ( %d)", m_game->GetBlackCount(), m_game->GetWhiteCount());
	//TextOut(_hdc, 0, 16, text, wcslen(text));
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

//bool CApp::ConvertPosToBlock(long _beforePos, int& _afterBlock)
//{
//	if (_beforePos > 0)
//	{
//		if (_beforePos < 50)
//			_afterBlock = 0;
//		else if (_beforePos < 100)
//			_afterBlock = 1;
//		else if (_beforePos < 150)
//			_afterBlock = 2;
//		else if (_beforePos < 200)
//			_afterBlock = 3;
//		else if (_beforePos < 250)
//			_afterBlock = 4;
//		else if (_beforePos < 300)
//			_afterBlock = 5;
//		else if (_beforePos < 350)
//			_afterBlock = 6;
//		else if (_beforePos < 400)
//			_afterBlock = 7;
//		else
//			return false;
//	}
//	else
//		return false;
//
//	return true;
//}

