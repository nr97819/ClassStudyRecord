#pragma once

#include "E_PlayerColor.h"
#include <Windows.h> // 이거 없어서 에러났던건데.. 왜 에러 안알려주지..
#include "Player.h"

class CGame
{
private:
	CPlayer* m_playerBlack;
	CPlayer* m_playerWhite;

	int** m_field;
	POINT m_pCurrentMousePos;
	POINT m_pCirclePos;
	POINT m_pCircleSize;

	int m_nowColor;

	int m_blackCnt;
	int m_whiteCnt;

public:
	CGame();
	~CGame();

	int*** GetField() { return &(m_field); }
	POINT GetCurrentMousePos() { return m_pCurrentMousePos; }
	int GetNowColor() { return m_nowColor; }
	int GetBlackCount() { return m_blackCnt; }
	int GetWhiteCount() { return m_whiteCnt; }

	void SetCurrentMousePosX(int _x) { m_pCurrentMousePos.x = _x; }
	void SetCurrentMousePosY(int _y) { m_pCurrentMousePos.y = _y; }
	void SetNowColor(int _color) { m_nowColor = _color; }

	void IncreaseBlackCount() { ++m_blackCnt; }
	void IncreaseWhiteCount() { ++m_whiteCnt; }
	void DecreaseBlackCount() { --m_whiteCnt; }
	void DecreaseWhiteCount() { --m_whiteCnt; }

	void FlipStones(POINT& _nowPos);

	void FlipX(POINT& _nowPos);
	void FlipMinusX(POINT& _nowPos);
	void FlipY(POINT& _nowPos);
	void FlipMinusY(POINT& _nowPos);

	void FlipAcross1(POINT& _nowPos);
	void FlipAcross2(POINT& _nowPos);
	void FlipAcross3(POINT& _nowPos);
	void FlipAcross4(POINT& _nowPos);

	// test
	void TEST_FlipX(POINT& _nowPos);
};

