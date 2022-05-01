#pragma once

#include <Windows.h>
#include "CSprite.h"

#define SPRITE_SIZE 16
#define FRAME_SIZE 64
#define READ_SIZE 80

class CResourceMgr
{
private:
	CSprite				m_cArrSprites[SPRITE_SIZE];
	HDC					m_hBmpDC;

	HBITMAP				m_hBitmap;
	LPDWORD				m_lpDIBits;
	BITMAPINFO*			m_pBitmapInfo;

private:
	static CResourceMgr*		m_instance;

private:
	CResourceMgr();
	~CResourceMgr();

public:
	static CResourceMgr* GetInst()
	{
		if (nullptr == m_instance)
			m_instance = new CResourceMgr();

		return m_instance;
	}
	void ReleaseInst()
	{
		if (nullptr != m_instance)
			delete m_instance;
	}

public:
	bool Init();
	void Update(); // no used
	void Render(HDC _memDC);

	void Load(HDC _hDC, const WCHAR* _filename);
	void Destroy();

public:
	HDC GetBmpDC() {return m_hBmpDC; }
	CSprite* GetSprites() { return m_cArrSprites; }
};

