#pragma once

// ======== Direct2D ========
#include <d2d1.h>
#include <dwrite.h>
#include <wincodec.h>
// ==========================

class CSprite
{
private:
	ID2D1Bitmap*			m_d2d1Bitmap;
	FLOAT					m_sizeX;
	FLOAT					m_sizeY;
	D2D1_RECT_F				m_rectSource;
	D2D1_RECT_F				m_rectTarget;


public:
	CSprite();
	~CSprite();

public:
	HRESULT Init(ID2D1Bitmap* _d2d1Bitmap, D2D1_RECT_F* _d2d1Rect);
	HRESULT Init(ID2D1Bitmap* _d2d1Bitmap, FLOAT _left, FLOAT _top, FLOAT _right, FLOAT _bottom);
	void Release();

public:
	void Draw(FLOAT _tX, FLOAT _tY, FLOAT _alpha);
};

