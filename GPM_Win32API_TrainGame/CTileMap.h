#pragma once

#include <Windows.h>

#define MAP_SIZE 100
#define FRAME_SIZE 64

class CTileMap
{
private:
	int			iArrTilemap[MAP_SIZE];

public:
	CTileMap();
	~CTileMap();

public:
	void Render(HDC _memDC);

public:
	void AddRail(int _index);
};

