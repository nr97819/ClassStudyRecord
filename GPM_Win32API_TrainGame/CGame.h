#pragma once

#include <Windows.h>
#include "CTileMap.h"

class CGame
{
private:
	static CGame*			m_game;
	CTileMap				m_tilemap;

private:
	CGame();
	~CGame();

public:
	static CGame* GetInst()
	{
		if (nullptr == m_game)
			m_game = new CGame();

		return m_game;
	}
	void ReleaseInst();

public:
	bool Init(HDC _hDC);
	void Update();
	void Render(HDC _memDC, POINT _pResolution);
};

