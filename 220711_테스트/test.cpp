#include <iostream>

#include <Windows.h>
#include <vector>

//#define MAX_SIZE 9
#define NEW_MAX_SIZE 19

//int map[MAX_SIZE][MAX_SIZE] =
//{
//	{1, 1, 1, 1, 1, 1, 1, 1, 1},
//	{1, 0, 0, 0, 1, 0, 0, 0, 1},
//	{1, 0, 0, 0, 1, 0, 0, 0, 1},
//	{1, 0, 0, 1, 0, 0, 0, 0, 1},
//	{1, 1, 1, 0, 0, 0, 1, 1, 1},
//	{1, 0, 0, 0, 0, 1, 0, 0, 1},
//	{1, 0, 0, 0, 1, 0, 0, 0, 1},
//	{1, 0, 0, 1, 1, 0, 0, 0, 1},
//	{1, 1, 1, 1, 1, 1, 1, 1, 1},
//};

int map2[NEW_MAX_SIZE][NEW_MAX_SIZE] =
{
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

struct POS
{
	int m_x = 0;
	int m_y = 0;

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

	// const 쓰는 것에 주의 (안쓰니 explicit으로 선언되었다고 경고 뜸 !)
	POS(const POS& _other)
	{
		m_x = _other.m_x;
		m_y = _other.m_y;
	}

	bool operator==(const POS& _other)
	{
		if (m_x == _other.m_x && m_y == _other.m_y)
			return true;
		else
			return false;
	}

	/*void operator=(POS& _other)
	{
		this->m_x = _other.m_x;
		this->m_y = _other.m_y;
	}*/

	bool IsEmptyPos()
	{
		if (map2[m_x][m_y] == 0)
			return true;
		else
			return false;
	}
};

std::vector<POS> g_vecStack;

enum class TILE_TYPE
{
	EMPTY = 0,
	WALL = 1,
	PASSED = 2
};

enum class DIR
{
	UP = 0,
	RIGHT = 1,
	DOWN = 2,
	LEFT = 3
};

int DIR_X[4] = { 0, 1, 0, -1 };
int DIR_Y[4] = { -1, 0, 1, 0 };

POS nowPosition(4, 4);
int nowDir = (int)DIR::UP;

bool LookAroundAndMove()
{
	bool bIsFirst = true;

	int tempX = -1;
	int tempY = -1;

	// 첫 시작을 위한 코드
	/*if (map[nowPosition.m_x][nowPosition.m_y] != (int)TILE_TYPE::PASSED)
	{
		map[nowPosition.m_x][nowPosition.m_y] = (int)TILE_TYPE::PASSED;
	}*/

	// 모든 방향 확인
	for (int iDir = (int)DIR::UP; iDir <= (int)DIR::LEFT; ++iDir)
	{
		if ((int)TILE_TYPE::EMPTY == map2[nowPosition.m_y + DIR_Y[iDir]][nowPosition.m_x + DIR_X[iDir]])
		{
			if (bIsFirst)
			{
				tempX = nowPosition.m_x + DIR_X[iDir];
				tempY = nowPosition.m_y + DIR_Y[iDir];

				g_vecStack.push_back(POS(nowPosition.m_y + DIR_Y[iDir], nowPosition.m_x + DIR_X[iDir]));

				bIsFirst = false;
			}
			else
			{
				g_vecStack.push_back(POS(nowPosition.m_y + DIR_Y[iDir], nowPosition.m_x + DIR_X[iDir]));
			}
		}
	}

	bIsFirst = true;

	// 갈 방향이 없다면
	if (tempX < 0 && tempY < 0)
	{
		nowDir = (int)DIR::UP;

		tempX = -1;
		tempY = -1;

		while (true)
		{
			if (g_vecStack.size() > 0)
			{
				nowPosition = g_vecStack.back();
				g_vecStack.pop_back();

				/*if (map2[nowPosition.m_y][nowPosition.m_x] == (int)TILE_TYPE::PASSED)
					continue;*/

				return true;
			}
			else
				return false;
		}
	}

	nowPosition.m_x = tempX;
	nowPosition.m_y = tempY;

	map2[nowPosition.m_y][nowPosition.m_x] = (int)TILE_TYPE::PASSED;

	return true;
}

void PrintMap()
{
	for (int _y = 0; _y < NEW_MAX_SIZE; ++_y)
	{
		for (int _x = 0; _x < NEW_MAX_SIZE; ++_x)
		{
			if (map2[_y][_x] == (int)TILE_TYPE::EMPTY)
				std::cout << "□";
			else if (map2[_y][_x] == (int)TILE_TYPE::WALL)
				std::cout << "■";
			else if (map2[_y][_x] == (int)TILE_TYPE::PASSED)
				std::cout << "▩";
		}
		std::cout << std::endl;
	}
}

int main()
{
	// ============ Start ============

	bool bResult = true;
	while (bResult)
	{
		//COORD posXY = { 0, 0 };
		//SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), posXY);
		//PrintMap();

		bResult = LookAroundAndMove();
	}

	PrintMap();

	std::cout << "프로그램이 종료되었습니다 !" << std::endl;

	return 0;
}