#include <iostream>

#include <vector>

#define MAX_SIZE 9

int map[MAX_SIZE][MAX_SIZE] = 
{
	{1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1, 0, 0, 0, 1},
	{1, 0, 0, 1, 0, 0, 0, 0, 1},
	{1, 1, 1, 0, 0, 0, 1, 1, 1},
	{1, 0, 0, 0, 0, 1, 0, 0, 1},
	{1, 0, 0, 0, 1, 0, 0, 0, 1},
	{1, 0, 0, 1, 1, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1},
};

std::vector<POS> g_vecStack;

struct POS
{
	int m_x;
	int m_y;

	POS()
	{
		m_x = 0;
		m_y = 0;
	}

	POS(int _x, int _y)
	{
		m_x = _x;
		m_y = _y;
	}

	POS(POS& _other)
	{
		m_x = _other.m_x;
		m_y = _other.m_y;
	}

	bool IsEmptyPos()
	{
		if (map[m_x][m_y] == 0)
			return true;
		else
			return false;
	}
};

enum class MAP_ELEMENT
{
	EMPTY,
	WALL,
	ALREADY
};

enum class DIR
{
	UP,
	LEFT,
	DOWN,
	RIGHT
};

int DIR_X[4] = { 0, -1, 0, 1 };
int DIR_Y[4] = { -1, 0, 1, 0 };

int main()
{
	/*for (int i = 0; i < MAX_SIZE; ++i)
	{
		map[0][i] = 1;
		map[i][0] = 1;
		map[MAX_SIZE - 1][i] = 1;
		map[i][MAX_SIZE - 1] = 1;
	}*/

	for (int _y = 0; _y < MAX_SIZE; ++_y)
	{
		for (int _x = 0; _x < MAX_SIZE; ++_x)
		{
			if (map[_y][_x] == 1)
				std::cout << "■";
			else
				std::cout << "□";
		}
		std::cout << std::endl;
	}

	// Start
	StartFill();

	return 0;
}


// Flood Fill 
void StartFill()
{
	POS nowPos(4, 4);
	int nowDir = (int)DIR::DOWN;

	while (true)
	{
		LookAroundAndMove(nowPos);


	}


}

void LookAroundAndMove(POS& _nowPos)
{
	bool bIsStuck = true;
	bool bIsAlreadyMove = false;

	// 모든 방향 확인
	for (int iDir = (int)DIR::UP; iDir <= (int)DIR::RIGHT; ++iDir)
	{
		int nowPosX = _nowPos.m_x + DIR_X[iDir];
		int nowPosY = _nowPos.m_y + DIR_X[iDir];

		if (map[nowPosX][nowPosY] == 0)
		{
			_nowPos.m_x = nowPosX;
			_nowPos.m_y = nowPosY;

			bIsStuck = false;
			bIsAlreadyMove = true;
		}
		else if (bIsAlreadyMove) // 1 or 2
		{
			g_vecStack.push_back(POS(nowPosX, nowPosY));
		}
		// -> 이 윗부분 전체적으로 코드 검증 필요

		// 갈 방향이 없다면
		if(bIsStuck) // true
		{
			while (g_vecStack.size() > 0) // size 기능 점검 필요 (헷갈림)
			{
				POS popedPos = g_vecStack.back();
				g_vecStack.pop_back();

				if (popedPos.IsEmptyPos())
				{
					_nowPos = popedPos; // 얕은 복사 (지역 변수이므로, 복사생성자를 통해서 복사로 안전)
					break;
				}
			}
		}
	}

	if (map[_nowPos.m_x][_nowPos.m_y] != 0)
	{
		// 방향 전환
		nowDir = ((int)nowDir + 1) % 4;
	}
	else
	{
		map[nowPos.m_x][nowPos.m_y] = (int)MAP_ELEMENT::ALREADY;
	}
}
