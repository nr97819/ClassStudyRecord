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
	int m_bErrorMessage;

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
	int IsCurrentTurnWin(POINT& _p); // [1] �ϳ��� ���� 5�� ��������
	int GetGameOver() { return m_bGameOver; }
	void SetGameOver(int _status) { m_bGameOver = TRUE; }
	
	int IsDoubleThree(POINT& _p); // [2] �ֻ����� ����
	void EnableErrorMessage() { m_bErrorMessage = TRUE; }
	void DisableErrorMessage() { m_bErrorMessage = FALSE; }
	int GetBoolError() { return m_bErrorMessage; }
};

