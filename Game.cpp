#include "Game.h"

#include <Windows.h>
#include <vector>

CGame::CGame()
{
	m_playerBlack = new CPlayer();
	m_playerWhite = new CPlayer();

	m_field = new int*[8];

	for (int i = 0; i < 8; i++)
		m_field[i] = new int[8];

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			m_field[i][j] = 0;

	//memset(m_field, 0, sizeof(int) * 64);
	m_field[3][3] = 1;
	m_field[4][4] = 1;
	m_field[3][4] = 2;
	m_field[4][3] = 2;

	m_pCurrentMousePos = {};
	m_pCirclePos = { 0,0 };
	m_pCircleSize = { 50, 50 };

	m_nowColor = PC_Black;

	m_blackCnt = 2;
	m_whiteCnt = 2;
}

CGame::~CGame()
{
	delete m_playerBlack;
	delete m_playerWhite;
}

void CGame::FlipStones(POINT& _nowPos)
{
	// 수평
	FlipX(_nowPos);
	FlipMinusX(_nowPos);

	// 수직
	FlipY(_nowPos);
	FlipMinusY(_nowPos);

	// 대각선
	/*FlipAcross1(_nowPos);
	FlipAcross2(_nowPos);
	FlipAcross3(_nowPos);
	FlipAcross4(_nowPos);*/
}

// test : 단순 좌표 연산으로만 뒤집기 구현하기
void CGame::TEST_FlipX(POINT& _nowPos)
{
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
					if (m_field[(*it).y][(*it).x] == m_nowColor)
						continue;
					else if ((m_field[(*it).y][(*it).x] == reverseColor))
					{
						m_field[(*it).y][(*it).x] = m_nowColor;

						if (m_nowColor == PC_Black)
						{
							++m_blackCnt;
							--m_whiteCnt;
						}
						else if (m_nowColor == PC_White)
						{
							++m_whiteCnt;
							--m_blackCnt;
						}
					}
				}
			}
		}
	}
}

void CGame::FlipX(POINT& _nowPos)
{
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
					if (m_field[(*it).y][(*it).x] == m_nowColor)
						continue;
					else if ((m_field[(*it).y][(*it).x] == reverseColor))
					{
						m_field[(*it).y][(*it).x] = m_nowColor;

						if (m_nowColor == PC_Black)
						{
							++m_blackCnt;
							--m_whiteCnt;
						}
						else if (m_nowColor == PC_White)
						{
							++m_whiteCnt;
							--m_blackCnt;
						}
					}
				}
			}
		}
	}
}

void CGame::FlipMinusX(POINT& _nowPos)
{
	int reverseColor = 0;
	if (m_nowColor == PC_Black)
		reverseColor = PC_White;
	else if (m_nowColor == PC_White)
		reverseColor = PC_Black;

	std::vector<POINT> v;
	POINT p{};

	if (m_field[_nowPos.y][_nowPos.x - 1] == reverseColor)
	{
		p.y = _nowPos.y;
		p.x = _nowPos.x - 1;
		v.push_back(p);

		for (int i = 2; i < 8; ++i)
		{
			if (_nowPos.x - i < 0)
				break;

			if (m_field[_nowPos.y][_nowPos.x - i] == reverseColor)
			{
				p.y = _nowPos.y;
				p.x = _nowPos.x - i;
				v.push_back(p);
			}

			if (m_field[_nowPos.y][_nowPos.x - i] == m_nowColor)
			{
				for (std::vector<POINT>::iterator it = v.begin(); it != v.end(); ++it)
				{
					if (m_field[(*it).y][(*it).x] == m_nowColor)
						continue;
					else if ((m_field[(*it).y][(*it).x] == reverseColor))
					{
						m_field[(*it).y][(*it).x] = m_nowColor;

						if (m_nowColor == PC_Black)
						{
							++m_blackCnt;
							--m_whiteCnt;
						}
						else if (m_nowColor == PC_White)
						{
							++m_whiteCnt;
							--m_blackCnt;
						}
					}
				}
			}
		}
	}
}

void CGame::FlipY(POINT& _nowPos)
{
	int reverseColor = 0;
	if (m_nowColor == PC_Black)
		reverseColor = PC_White;
	else if (m_nowColor == PC_White)
		reverseColor = PC_Black;

	std::vector<POINT> v;
	POINT p{};

	if (_nowPos.y + 1 < 8)
	{
		if (m_field[_nowPos.y + 1][_nowPos.x] == reverseColor)
		{
			p.y = _nowPos.y + 1;
			p.x = _nowPos.x;
			v.push_back(p);

			for (int i = 2; i < 8; ++i)
			{
				if (_nowPos.y + i >= 8)
					break;

				if (m_field[_nowPos.y + i][_nowPos.x] == reverseColor)
				{
					p.y = _nowPos.y + i;
					p.x = _nowPos.x;
					v.push_back(p);
				}

				if (m_field[_nowPos.y + i][_nowPos.x] == m_nowColor)
				{
					for (std::vector<POINT>::iterator it = v.begin(); it != v.end(); ++it)
					{
						if (m_field[(*it).y][(*it).x] == m_nowColor)
							continue;
						else if ((m_field[(*it).y][(*it).x] == reverseColor))
						{
							m_field[(*it).y][(*it).x] = m_nowColor;

							if (m_nowColor == PC_Black)
							{
								++m_blackCnt;
								--m_whiteCnt;
							}
							else if (m_nowColor == PC_White)
							{
								++m_whiteCnt;
								--m_blackCnt;
							}
						}
					}
				}
			}
		}
	}
}

void CGame::FlipMinusY(POINT& _nowPos)
{
	int reverseColor = 0;
	if (m_nowColor == PC_Black)
		reverseColor = PC_White;
	else if (m_nowColor == PC_White)
		reverseColor = PC_Black;

	std::vector<POINT> v;
	POINT p{};

	if (_nowPos.y - 1 >= 0) // test
	{
		if (m_field[_nowPos.y - 1][_nowPos.x] == reverseColor)
		{
			p.y = _nowPos.y - 1;
			p.x = _nowPos.x;
			v.push_back(p);

			for (int i = 2; i < 8; ++i)
			{
				if (_nowPos.y - i < 0)
					break;
				
				if (m_field[_nowPos.y - i][_nowPos.x] == reverseColor)
				{
					p.y = _nowPos.y - i;
					p.x = _nowPos.x;
					v.push_back(p);
				}

				if (m_field[_nowPos.y - i][_nowPos.x] == m_nowColor)
				{
					for (std::vector<POINT>::iterator it = v.begin(); it != v.end(); ++it)
					{
						if (m_field[(*it).y][(*it).x] == m_nowColor)
							continue;
						else if ((m_field[(*it).y][(*it).x] == reverseColor))
						{
							m_field[(*it).y][(*it).x] = m_nowColor;

							if (m_nowColor == PC_Black)
							{
								++m_blackCnt;
								--m_whiteCnt;
							}
							else if (m_nowColor == PC_White)
							{
								++m_whiteCnt;
								--m_blackCnt;
							}
						}
					}
				}
			}
		}
	}
}

void CGame::FlipAcross1(POINT& _nowPos)
{
	int reverseColor = 0;
	if (m_nowColor == PC_Black)
		reverseColor = PC_White;
	else if (m_nowColor == PC_White)
		reverseColor = PC_Black;

	std::vector<POINT> v;
	POINT p{};

	if (m_field[_nowPos.y - 1][_nowPos.x + 1] == reverseColor)
	{
		p.y = _nowPos.y - 1;
		p.x = _nowPos.x + 1;
		v.push_back(p);

		for (int i = 2; i < 8; ++i)
		{
			if ((_nowPos.x + i) >= 8 || (_nowPos.y - i) < 0)
				break;

			if (m_field[_nowPos.y - i][_nowPos.x + i] == reverseColor)
			{
				p.y = _nowPos.y - i;
				p.x = _nowPos.x + i;
				v.push_back(p);
			}

			if (m_field[_nowPos.y - i][_nowPos.x + i] == m_nowColor)
			{
				for (std::vector<POINT>::iterator it = v.begin(); it != v.end(); ++it)
				{
					m_field[(*it).y][(*it).x] = m_nowColor;

					if (m_nowColor == PC_Black)
					{
						++m_blackCnt;
						--m_whiteCnt;
					}
					else if (m_nowColor == PC_White)
					{
						++m_whiteCnt;
						--m_blackCnt;
					}
				}
			}
		}
	}
}

void CGame::FlipAcross2(POINT& _nowPos)
{
	int reverseColor = 0;
	if (m_nowColor == PC_Black)
		reverseColor = PC_White;
	else if (m_nowColor == PC_White)
		reverseColor = PC_Black;

	std::vector<POINT> v;
	POINT p{};

	if (m_field[_nowPos.y - 1][_nowPos.x - 1] == reverseColor)
	{
		p.y = _nowPos.y - 1;
		p.x = _nowPos.x - 1;
		v.push_back(p);

		for (int i = 2; i < 8; ++i)
		{
			if ((_nowPos.y + i < 0) || (_nowPos.x + i < 0))
				break;

			if (m_field[_nowPos.y - i][_nowPos.x - i] == reverseColor)
			{
				p.y = _nowPos.y - i;
				p.x = _nowPos.x - i;
				v.push_back(p);
			}

			if (m_field[_nowPos.y - i][_nowPos.x - i] == m_nowColor)
			{
				for (std::vector<POINT>::iterator it = v.begin(); it != v.end(); ++it)
				{
					m_field[(*it).y][(*it).x] = m_nowColor;

					if (m_nowColor == PC_Black)
					{
						++m_blackCnt;
						--m_whiteCnt;
					}
					else if (m_nowColor == PC_White)
					{
						++m_whiteCnt;
						--m_blackCnt;
					}
				}
			}
		}
	}
}

void CGame::FlipAcross3(POINT& _nowPos)
{
	int reverseColor = 0;
	if (m_nowColor == PC_Black)
		reverseColor = PC_White;
	else if (m_nowColor == PC_White)
		reverseColor = PC_Black;

	std::vector<POINT> v;
	POINT p{};

	if (m_field[_nowPos.y + 1][_nowPos.x - 1] == reverseColor)
	{
		p.y = _nowPos.y + 1;
		p.x = _nowPos.x - 1;
		v.push_back(p);

		for (int i = 2; i < 8; ++i)
		{
			if ((_nowPos.x - i) > 0 || (_nowPos.y + i) >= 8)
				break;

			if (m_field[_nowPos.y + i][_nowPos.x - i] == reverseColor)
			{
				p.y = _nowPos.y + i;
				p.x = _nowPos.x - i;
				v.push_back(p);
			}

			if (m_field[_nowPos.y + i][_nowPos.x - i] == m_nowColor)
			{
				for (std::vector<POINT>::iterator it = v.begin(); it != v.end(); ++it)
				{
					m_field[(*it).y][(*it).x] = m_nowColor;

					if (m_nowColor == PC_Black)
					{
						++m_blackCnt;
						--m_whiteCnt;
					}
					else if (m_nowColor == PC_White)
					{
						++m_whiteCnt;
						--m_blackCnt;
					}
				}
			}
		}
	}
}

void CGame::FlipAcross4(POINT& _nowPos)
{
	int reverseColor = 0;
	if (m_nowColor == PC_Black)
		reverseColor = PC_White;
	else if (m_nowColor == PC_White)
		reverseColor = PC_Black;

	std::vector<POINT> v;
	POINT p{};

	if (m_field[_nowPos.y + 1][_nowPos.x + 1] == reverseColor)
	{
		p.y = _nowPos.y + 1;
		p.x = _nowPos.x + 1;
		v.push_back(p);

		for (int i = 2; i < 8; ++i)
		{
			if ((_nowPos.y + i >= 8) || (_nowPos.x + i >= 8))
				break;

			if (m_field[_nowPos.y + i][_nowPos.x + i] == reverseColor)
			{
				p.y = _nowPos.y + i;
				p.x = _nowPos.x + i;
				v.push_back(p);
			}

			if (m_field[_nowPos.y + i][_nowPos.x + i] == m_nowColor)
			{
				for (std::vector<POINT>::iterator it = v.begin(); it != v.end(); ++it)
				{
					m_field[(*it).y][(*it).x] = m_nowColor;

					if (m_nowColor == PC_Black)
					{
						++m_blackCnt;
						--m_whiteCnt;
					}
					else if (m_nowColor == PC_White)
					{
						++m_whiteCnt;
						--m_blackCnt;
					}
				}
			}
		}
	}
}