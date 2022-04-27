#pragma once

#include <Windows.h>
#include "CSprite.h"

#define MAX_SIZE 100 // 10 * 10
#define FRAME_SIZE 70

class CBitmap
{
private:
	CSprite				m_cArrSprites[MAX_SIZE];
	HDC					m_hBmpDC;

	HBITMAP				m_hBitmap;
	LPDWORD				m_lpDIBits;
	BITMAPINFO*			m_pBitmapInfo;

public:
	CBitmap();
	~CBitmap();

	bool Init();
	void Update(); // Shuffle? no used
	void Render(HDC _memDC);

	void Load(HDC _hDC, const WCHAR* _filename);
	void Destroy();

public:
	HDC GetBmpDC() {return m_hBmpDC; }
};

