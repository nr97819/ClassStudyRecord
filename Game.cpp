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
	m_bErrorMessage = FALSE;

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
		_p.x = 569;
	if (_p.y >= 570)
		_p.y = 569;
	if (_p.x < 0)
		_p.x = 0;
	if (_p.y < 0)
		_p.y = 0;

	int cellX = _p.x / 30;
	int cellY = _p.y / 30;

	if (m_field[cellY][cellX] != PC_None)
		return FALSE;

	if (IsDoubleThree(_p))
	{
		EnableErrorMessage();
		return FALSE;
	}
	else
	{
		if (GetBoolError())
			DisableErrorMessage();
	}

	m_field[cellY][cellX] = m_turn;

	return TRUE;
}

int CGame::IsCurrentTurnWin(POINT& _p)
{
	POINT p = {};
	p.x = _p.x / 30;
	p.y = _p.y / 30;

	// ============ X 축 ============
	int x_cnt = 1;
	for (int i = 1; i < 5; i++)
	{
		if (m_field[p.y][p.x + i] != m_turn)
			break;

		x_cnt++;
	}

	for (int i = 1; i < 5; i++)
	{
		if (m_field[p.y][p.x - i] != m_turn)
			break;

		x_cnt++;
	}

	if(x_cnt >= 5)
		return TRUE;

	// ============ Y 축 ============
	int y_cnt = 1;
	for (int i = 1; i < 5; i++)
	{
		if (m_field[p.y + i][p.x] != m_turn)
			break;

		y_cnt++;
	}

	for (int i = 1; i < 5; i++)
	{
		if (m_field[p.y - i][p.x] != m_turn)
			break;

		y_cnt++;
	}

	if (y_cnt >= 5)
		return TRUE;

	// ============ y=(+)x 축 ============
	int xy_cnt = 1;
	for (int i = 1; i < 5; i++)
	{
		if (m_field[p.y + i][p.x + i] != m_turn)
			break;

		xy_cnt++;
	}

	for (int i = 1; i < 5; i++)
	{
		if (m_field[p.y - i][p.x - i] != m_turn)
			break;

		xy_cnt++;
	}

	if (xy_cnt >= 5)
		return TRUE;

	// ============ y=(-)x 축 ============
	int yx_cnt = 1;
	for (int i = 1; i < 5; i++)
	{
		if (m_field[p.y + i][p.x - i] != m_turn)
			break;

		yx_cnt++;
	}

	for (int i = 1; i < 5; i++)
	{
		if (m_field[p.y - i][p.x + i] != m_turn)
			break;

		yx_cnt++;
	}

	if (yx_cnt >= 5)
		return TRUE;
	
	return FALSE;
}

int CGame::IsDoubleThree(POINT& _p)
{
	POINT p = {};
	p.x = _p.x / 30;
	p.y = _p.y / 30;

	int enemy = (m_turn % 2) + 1;
	int doubleThreeCnt = 0;

	// ============ X 축 ============
	int x_flag = TRUE;
	int x_cnt = 1;
	for (int i = 1; i <= 5; i++)
	{
		if (m_field[p.y][p.x + i] == PC_None)
			break;
		else if (m_field[p.y][p.x + i] == enemy)
		{
			x_flag = FALSE;
			break;
		}

		x_cnt++;
	}

	for (int i = 1; i <= 5; i++)
	{
		if (m_field[p.y][p.x - i] == PC_None)
			break;
		else if (m_field[p.y][p.x - i] == enemy)
		{
			x_flag = FALSE;
			break;
		}

		x_cnt++;
	}

	if ((x_cnt == 3) && x_flag)
		doubleThreeCnt++;

	// ============ Y 축 ============
	int y_flag = TRUE;
	int y_cnt = 1;
	for (int i = 1; i <= 5; i++)
	{
		if (m_field[p.y + i][p.x] == PC_None)
			break;
		else if (m_field[p.y + i][p.x] == enemy)
		{
			y_flag = FALSE;
			break;
		}

		y_cnt++;
	}

	for (int i = 1; i <= 5; i++)
	{
		if (m_field[p.y - i][p.x] == PC_None)
			break;
		else if (m_field[p.y - i][p.x] == enemy)
		{
			y_flag = FALSE;
			break;
		}

		y_cnt++;
	}

	if ((y_cnt == 3) && y_flag)
		doubleThreeCnt++;

	if (doubleThreeCnt >= 2)
		return TRUE;

	// ============ y=(+)x 축 ============
	int xy_flag = TRUE;
	int xy_cnt = 1;
	for (int i = 1; i <= 5; i++)
	{
		if (m_field[p.y + i][p.x + i] == PC_None)
			break;
		else if (m_field[p.y + i][p.x + i] == enemy)
		{
			xy_flag = FALSE;
			break;
		}

		xy_cnt++;
	}

	for (int i = 1; i <= 5; i++)
	{
		if (m_field[p.y - i][p.x - i] == PC_None)
			break;
		else if (m_field[p.y - i][p.x - i] == enemy)
		{
			xy_flag = FALSE;
			break;
		}

		xy_cnt++;
	}

	if ((xy_cnt == 3) && xy_flag)
		doubleThreeCnt++;

	if (doubleThreeCnt >= 2)
		return TRUE;

	// ============ y=(-)x 축 ============
	int yx_flag = TRUE;
	int yx_cnt = 1;
	for (int i = 1; i <= 5; i++)
	{
		if (m_field[p.y + i][p.x - i] == PC_None)
			break;
		else if (m_field[p.y + i][p.x - i] == enemy)
		{
			yx_flag = FALSE;
			break;
		}

		yx_cnt++;
	}

	for (int i = 1; i <= 5; i++)
	{
		if (m_field[p.y - i][p.x + i] == PC_None)
			break;
		else if (m_field[p.y - i][p.x + i] == enemy)
		{
			yx_flag = FALSE;
			break;
		}

		yx_cnt++;
	}

	if ((yx_cnt == 3) && yx_flag)
		doubleThreeCnt++;

	if (doubleThreeCnt >= 2)
		return TRUE;

	// 해당 없을 시, FALSE 반환
	return FALSE;
}

void CGame::Render(HDC _hdc)
{
	int size = 30;
	int m = 15;

	for (int x = 0; x < MAX; x++)
	{
		MoveToEx(_hdc, x * size + m, m, NULL);
		LineTo(_hdc, x * size + m, (MAX - 1) * size + m);
	}

	for (int y = 0; y < MAX; y++)
	{
		MoveToEx(_hdc, m, y * size + m, NULL);
		LineTo(_hdc, (MAX - 1) * size + m, y * size + m);
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
			swprintf_s(winner, L"검은 돌이 이겼습니다!!");
		else if (m_turn == PC_White)
			swprintf_s(winner, L"흰 돌이 이겼습니다!!");
		else
			swprintf_s(winner, L"error");
		TextOut(_hdc, 250, 250, winner, wcslen(winner));
	}

	if (m_bErrorMessage)
	{
		WCHAR errorMsg[30] = {};
		swprintf_s(errorMsg, L"[안내] 쌍삼은 둘 수 없습니다.");
		TextOut(_hdc, 250, 250, errorMsg, wcslen(errorMsg));
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
