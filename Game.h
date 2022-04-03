#pragma once

#include "E_PlayerColor.h"
#include <Windows.h>

#define MAX 19

class CGame
{
private:
	int m_field[MAX][MAX];
	POINT m_pCurrentMousePos;
	POINT m_pCirclePos;
	POINT m_pCircleSize;

	int m_turn; // Player�� ����ϵ��� ����
	int m_bGameOver;

	HBRUSH m_stoneBrush[2];

	//HBRUSH m_whiteBrush;
	//HBRUSH m_blackBrush;
	HBRUSH m_redBrush;

public:
	CGame();
	~CGame();

	void Render(HDC _hdc); // Game�� Render()

	POINT GetCurrentMousePos() { return m_pCurrentMousePos; }

	void SetCurrentMousePosX(int _x) { m_pCurrentMousePos.x = _x; }
	void SetCurrentMousePosY(int _y) { m_pCurrentMousePos.y = _y; }

	int PutStone(POINT& _p);
	void ChangeTurn() { m_turn = (m_turn % 2) + 1; }
	int GetTurn() { return m_turn; }

	// New (Omok �ڵ� �߰�)
	void isCurrentTurnWin(POINT& _p); // isCurrentTurnWin()
	int isGameOver() { return m_bGameOver; }
};

