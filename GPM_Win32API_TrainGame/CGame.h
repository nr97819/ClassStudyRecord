#pragma once

#include <Windows.h>
#include "CBitmap.h"

class CGame
{
private:
	static CGame*			m_game;
	CBitmap					m_bitmap;

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
	bool Init();
	void Update();
	void Render(HDC _memDC, POINT _pResolution);
};

