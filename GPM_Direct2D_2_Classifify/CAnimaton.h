#pragma once

#include <windows.h>

// ======== Direct2D ========
#include <d2d1.h>
#include <dwrite.h>
#include <wincodec.h>
// ==========================

#include "CSprite.h"

#define MAX_FRAME_COUNT 10

class CAnimation
{
private:
	ID2D1Bitmap*			m_d2d1Bitmap;
	CSprite*				m_ArrSprite[MAX_FRAME_COUNT];

private:
	UINT					m_iTimes;
	FLOAT					m_startX;
	FLOAT					m_startY;
	FLOAT					m_deltaX;
	FLOAT					m_deltaY;
	
	FLOAT					m_width;
	FLOAT					m_height;
	UINT					m_rows;
	UINT					m_columns;

	double					m_dInterval;
	double					m_dAccTime;
	UINT					m_iCurFrame;

public:
	CAnimation();
	~CAnimation();

public:
	HRESULT Init(
		ID2D1Bitmap* _bitmap, UINT _times,
		FLOAT _startX, FLOAT _startY,
		FLOAT _deltaX, FLOAT _deltaY,
		FLOAT _width, FLOAT _height,
		UINT _rows, UINT _columns, FLOAT _interval);
	void Release();

	void Draw(FLOAT _startPosX, FLOAT _startPosY, FLOAT _alpha);
};

