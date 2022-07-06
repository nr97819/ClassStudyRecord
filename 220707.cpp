#include <iostream>

#include <vector>

#define MAX_SIZE 9

int map[MAX_SIZE][MAX_SIZE] = {
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
};

enum DIR
{
	DOWN,
	LEFT,
	UP,
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

	return 0;
}


// Flood Fill 
void StartFill()
{
	POS nowPos(4, 4);
	int nowDir = (int)DOWN;

	while (true)
	{
		// 모든 방향 확인
		for (int i = 0; i < 4; ++i)
		{
			nowPos.m_x += DIR_X[nowDir];
			nowPos.m_y += DIR_X[nowDir];

			if (map[nowPos.m_x][nowPos.m_y] == 0)
			{
				g_vecStack.push_back(POS(nowPos.m_x, nowPos.m_y));
			}
			else // != 0
			{

			}

			nowDir = ((int)nowDir + 1) % 4;
		}

		g_vecStack;

		if (map[nowPos.m_x][nowPos.m_y] != 0)
		{
			// 방향 전환
			nowDir = ((int)nowDir + 1) % 4;
		}
		else
		{
			map[nowPos.m_x][nowPos.m_y] = 2;
		}
	}


}
