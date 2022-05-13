#include "CSprite.h"


CSprite::CSprite()
	: m_pBitmap(nullptr)
	, m_rectSource{}
	, m_sizeX(0.f)
	, m_sizeY(0.f)
{}

// 784, 320
CSprite::CSprite(ID2D1Bitmap* _pBitmap, FLOAT _ltX, FLOAT _ltY, FLOAT _rbX, FLOAT _rbY)
	: m_pBitmap(nullptr)
	, m_rectSource{}
	, m_sizeX(0.f)
	, m_sizeY(0.f)

{
	m_pBitmap = _pBitmap;
	m_rectSource = { _ltX, _ltY, _rbX, _rbY };
	m_sizeX = _rbX - _ltX;
	m_sizeY = _rbY - _ltY;
}

CSprite::CSprite(ID2D1Bitmap* _pBitmap, const D2D1_RECT_F& _targetRect)
	: m_pBitmap(nullptr)
	, m_rectSource{}
	, m_sizeX(0.f)
	, m_sizeY(0.f)

{
	m_pBitmap = _pBitmap;
	m_rectSource = { _targetRect.left, _targetRect.top, _targetRect.right, _targetRect.bottom };
	m_sizeX = _targetRect.right - _targetRect.left;
	m_sizeY = _targetRect.bottom - _targetRect.top;
}

CSprite::~CSprite()
{

}
