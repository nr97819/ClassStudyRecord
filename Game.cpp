#include "Game.h"

#include <Windows.h>
#include <iostream>
#include <vector>

CGame::CGame()
{
	for (int i = 0; i < MAX; i++)
		for (int j = 0; j < MAX; j++)
			m_field[i][j] = 0;

	m_pCurrentMousePos = {};
	m_pCirclePos = { 0, 0 };
	m_pCircleSize = { 50, 50 };

	m_turn = PC_Black;
	m_bGameOver = FALSE;

	m_stoneBrush[1] = CreateSolidBrush(RGB(255, 255, 255));
	m_stoneBrush[0] = CreateSolidBrush(RGB(0, 0, 0));
	m_redBrush = CreateSolidBrush(RGB(255, 0, 0));
}

CGame::~CGame()
{
	DeleteObject(m_stoneBrush[1]);
	DeleteObject(m_stoneBrush[0]);
	DeleteObject(m_redBrush);
}

int CGame::PutStone(POINT& _p)
{
	// 수정해야 함
	if (_p.x >= 570)
		_p.x = 570;
	if (_p.y >= 570)
		_p.y = 570;
	if (_p.x < 0)
		_p.x = 0;
	if (_p.y < 0)
		_p.y = 0;

	int cellX = _p.x / 30;
	int cellY = _p.y / 30;

	if (m_field[cellY][cellX] != PC_None)
		return FALSE;

	m_field[cellY][cellX] = m_turn;

	return TRUE;
}

void CGame::isCurrentTurnWin(POINT& _p)
{
	POINT p = {};
	p.x = _p.x / 30;
	p.y = _p.y / 30;

	int totalCnt = 0;
	int cnt = 0;
	// ====== 수평 ======
	// X축
	for (int i = 1; p.x + i < 19; i++)
	{
		if (m_field[p.y][p.x + i] == m_turn)
		{
			cnt++;
		}
		else
		{
			totalCnt += cnt;
			break;
		}

		if (cnt >= 4)
		{
			m_bGameOver = TRUE;
			return; // 바로 게임 오버
		}
	}

	cnt = 0;
	// -X축	
	for (int i = 1; p.x - i < 19; i++)
	{
		if (m_field[p.y][p.x - i] == m_turn)
		{
			cnt++;
		}
		else
		{
			totalCnt += cnt;
			break;
		}

		if (cnt >= 4)
		{
			m_bGameOver = TRUE;
			return; // 바로 게임 오버
		}
	}

	if (totalCnt >= 4)
	{
		m_bGameOver = TRUE;
		return;
	}

	totalCnt = 0;
	// ====== 수직 ======
	// Y축
	for (int i = 1; p.y + i < 19; i++)
	{
		if (m_field[p.y + i][p.x] != m_turn)
			break;

		if (i >= 4)
		{
			totalCnt += i; // 누적 (중요)
			m_bGameOver = TRUE;
		}
	}

	// -Y축
	for (int i = 1; p.y - i < 19; i++)
	{
		if (m_field[p.y - i][p.x] != m_turn)
			break;

		if (i >= 4)
		{
			totalCnt += i; // 누적 (중요)
			m_bGameOver = TRUE;
		}
	}

	// ====== 대각선 ====== 
	// 우측상단
	for (int i = 1; 
			p.y + i < 19 && p.x + i < 19; 
			i++)
	{
		if (m_field[p.y + i][p.x + i] != m_turn)
			break;

		if (i >= 4)
		{
			totalCnt += i; // 누적 (중요)
			m_bGameOver = TRUE;
		}
	}

	// 좌측상단
	for (int i = 1;
		p.y + i < 19 && p.x - i < 19;
		i++)
	{
		if (m_field[p.y + i][p.x - i] != m_turn)
			break;

		if (i >= 4)
		{
			totalCnt += i; // 누적 (중요)
			m_bGameOver = TRUE;
		}
	}

	// 좌측하단
	for (int i = 1;
		p.y - i < 19 && p.x - i < 19;
		i++)
	{
		if (m_field[p.y - i][p.x - i] != m_turn)
			break;

		if (i >= 4)
		{
			totalCnt += i; // 누적 (중요)
			m_bGameOver = TRUE;
		}
	}

	// 우측하단
	for (int i = 1;
		p.y - i < 19 && p.x + i < 19;
		i++)
	{
		if (m_field[p.y - i][p.x + i] != m_turn)
			break;

		if (i >= 4)
		{
			totalCnt += i; // 누적 (중요)
			m_bGameOver = TRUE;
		}
	}
}

void CGame::Render(HDC _hdc)
{
	int size = 30;
	int m = 15;

	for (int x = 0; x <= MAX; x++)
	{
		MoveToEx(_hdc, x * size + m, m, NULL);
		LineTo(_hdc, x * size + m, MAX * size + m);
	}

	for (int y = 0; y <= MAX; y++)
	{
		MoveToEx(_hdc, m, y * size + m, NULL);
		LineTo(_hdc, MAX * size + m, y * size + m);
	}

	for (int y = 0; y < MAX; y++)
	{
		for (int x = 0; x < MAX; x++)
		{
			if (m_field[y][x] != 0)
			{
				SelectObject(_hdc, m_stoneBrush[m_field[y][x] - 1]);
				Ellipse(_hdc, x * size, y * size, x * size + 30, y * size + 30);
			}
		}
	}

	// 게임 종료 시, 덮어씌워 출력
	if (m_bGameOver)
	{
		WCHAR winner[30] = {};
		if (m_turn == PC_Black)
			swprintf_s(winner, L"Winner! [Black]");
		else if (m_turn == PC_White)
			swprintf_s(winner, L"Winner! [White]");
		else
			swprintf_s(winner, L"DRAW...");
		
		TextOut(_hdc, 200, 200, winner, wcslen(winner));
	}

	//for (int y = 50; y <= 450; y += 50)
	//{
	//	MoveToEx(_hdc, 50, y, NULL);
	//	LineTo(_hdc, 450, y);
	//}

	//for (int x = 50; x <= 450; x += 50)
	//{
	//	MoveToEx(_hdc, x, 50, NULL);
	//	LineTo(_hdc, x, 450);
	//}

	//int a1 = 75;
	//int delta = 50; // 50이 꽉차는 크기임
	//int** field = *(m_game->GetField());
	//for (int yValue = a1; yValue <= 425; yValue += delta)
	//{
	//	for (int xValue = a1; xValue <= 425; xValue += delta)
	//	{
	//		int cy = (yValue - a1) / 50;
	//		int cx = (xValue - a1) / 50;

	//		POINT p;
	//		p.y = cy;
	//		p.x = cx;

	//		if (field[cy][cx] == PC_Black)
	//			DrawCircleAtBlock(_hdc, m_blackBrush, yValue, xValue, delta);
	//		else if (field[cy][cx] == PC_White)
	//			DrawCircleAtBlock(_hdc, m_whiteBrush, yValue, xValue, delta);
	//		else
	//			continue;
	//		/*else if (field[cy][cx] == PC_None)
	//		{
	//		if (m_game->FlipStones(p))
	//			DrawCircleAtBlock(_hdc, m_greenBrush, yValue, xValue, delta);
	//		}*/
	//	}
	//}
}
