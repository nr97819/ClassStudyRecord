#pragma once

#include <d2d1.h>

class CSprite
{
private:
	ID2D1Bitmap*	m_pBitmap;
	D2D1_RECT_F		m_rectSource;
	FLOAT			m_sizeX;
	FLOAT			m_sizeY;

public:
	CSprite();
	CSprite(ID2D1Bitmap* _pBitmap, FLOAT _ltX, FLOAT _ltY, FLOAT _rbX, FLOAT _rbY);
	CSprite(ID2D1Bitmap* _pBitmap, const D2D1_RECT_F& _targetRect);
	~CSprite();

	CSprite* operator=(const CSprite* _sprite)
	{
		m_pBitmap = _sprite->m_pBitmap;
		m_rectSource = _sprite->m_rectSource;
		m_sizeX = _sprite->m_sizeX;
		m_sizeY = _sprite->m_sizeY;

		return this;
	}

	void Draw(ID2D1HwndRenderTarget* _pRenderTarget)
	{
		_pRenderTarget->DrawBitmap(m_pBitmap,
				D2D1::RectF(0.f, 0.f, m_sizeX, m_sizeY),
				1.f,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				m_rectSource );
			//D2D1::RectF(0.f, 0.f, m_sizeX, m_sizeY);
	}
	void Draw(ID2D1HwndRenderTarget* _pRenderTarget, const D2D1_RECT_F& _targetRect)
	{
		_pRenderTarget->DrawBitmap(m_pBitmap,
			_targetRect,
			1.f,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			m_rectSource);
		//D2D1::RectF(0.f, 0.f, m_sizeX, m_sizeY);
	}
	void Draw(ID2D1HwndRenderTarget* _pRenderTarget, FLOAT _tx, FLOAT _ty)
	{
		_pRenderTarget->DrawBitmap(m_pBitmap,
			D2D1::RectF(_tx, _ty, m_sizeX + _tx, m_sizeY + _ty),
			1.f,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			m_rectSource);
	}
	// void Draw(rt, { 0.0f , 0.0f , 128.0f 340.0f });
};

