#include "CSprite.h"

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "windowscodecs.lib") // WIC Lib

#include "CD2DCore.h"

CSprite::CSprite()
	: m_d2d1Bitmap(nullptr)
	, m_sizeX(0.f)
	, m_sizeY(0.f)
	, m_rectSource{}
	, m_rectTarget{}
{}

CSprite::~CSprite()
{}

HRESULT CSprite::Init(ID2D1Bitmap* _d2d1Bitmap, D2D1_RECT_F* _d2d1Rect)
{
	m_d2d1Bitmap = _d2d1Bitmap;

	m_sizeX = _d2d1Bitmap->GetSize().width;
	m_sizeY = _d2d1Bitmap->GetSize().height;

	m_rectSource = D2D1::RectF(0.f, 0.f, m_sizeX - 1, m_sizeY - 1);
	m_rectTarget = D2D1::RectF(0.f, 0.f, m_sizeX - 1, m_sizeY - 1);

	return S_OK;
}

HRESULT CSprite::Init(ID2D1Bitmap* _d2d1Bitmap, FLOAT _left, FLOAT _top, FLOAT _right, FLOAT _bottom)
{
	m_d2d1Bitmap = _d2d1Bitmap;

	m_sizeX = _right - _left;
	m_sizeY = _bottom - _top;

	m_rectSource = D2D1::RectF(_left, _top, _right - 1, _bottom - 1);
	m_rectTarget = D2D1::RectF(_left, _top, _right - 1, _bottom - 1);

	return S_OK;
}

void CSprite::Release()
{}

void CSprite::Draw(FLOAT _startX, FLOAT _startY, FLOAT _alpha)
{
	// RenderTarget을 받아오더라도, 여기에서 하는게 맞을 것 같아서... (여쭤보기)
	ID2D1RenderTarget* renderTarget = *(CD2DCore::GetInst()->CreateMyRenderTarget());

	renderTarget->DrawBitmap(
		m_d2d1Bitmap,
		D2D1::RectF(_startX, _startY, _startX + m_sizeX - 1, _startY + m_sizeY - 1),
		_alpha,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		m_rectSource);
}

