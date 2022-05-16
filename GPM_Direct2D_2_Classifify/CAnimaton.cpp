#include "CAnimaton.h"

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "windowscodecs.lib") // WIC Lib

#include "CSprite.h"
#include "CTimeMgr.h"
//#include "CAnimMgr.h"
//#include "CD2DCore.h"

CAnimation::CAnimation()
	: m_d2d1Bitmap(nullptr)
	, m_iTimes(0)
	, m_startX(0.f)
	, m_startY(0.f)
	, m_deltaX(0.f)
	, m_deltaY(0.f)
	, m_width(0.f)
	, m_height(0.f)
	, m_rows(0)
	, m_columns(0)
	, m_dInterval(0.)
	, m_ArrSprite{}
	, m_iCurFrame(0)
	, m_dAccTime(0.)
{}

CAnimation::~CAnimation()
{}

void CAnimation::Release()
{
	for (UINT i = 0; i < m_iTimes; ++i)
	{
		if (nullptr != m_ArrSprite[i])
			delete m_ArrSprite[i];
	}

	if (nullptr != this) // 이거 맞나...?
		delete this;
}

HRESULT CAnimation::Init(
	ID2D1Bitmap* _bitmap, UINT _iTimes,
	FLOAT _startX, FLOAT _startY,
	FLOAT _deltaX, FLOAT _deltaY,
	FLOAT _width, FLOAT _height,
	UINT _rows, UINT _columns, FLOAT _dInterval)
{
	m_d2d1Bitmap = _bitmap; m_iTimes = _iTimes;
	m_startX = _startX; m_startY = _startY;
	m_deltaX = _deltaX; m_deltaY = _deltaY;
	m_width = _width; m_height = _height;
	m_rows = _rows; m_columns = _columns; m_dInterval = _dInterval;

	int index = 0;
	for (UINT y = 0; y < _rows; ++y)
	{
		for (UINT x = 0; x < _columns; ++x)
		{
			CSprite* sprite = new CSprite();
			sprite->Init(
				m_d2d1Bitmap,
				_startX + (x* _deltaX),
				_startY + (y* _deltaY),
				_startX + (x * _deltaX) + m_width,
				_startY + (y * _deltaY) + m_height);
			m_ArrSprite[index] = sprite;
			++index;
		}
	}

	return S_OK;
}

void CAnimation::Draw(FLOAT _startPosX, FLOAT _startPosY, FLOAT _alpha)
{
	m_dAccTime += CTimeMgr::GetInst()->GetDT();

	if (m_dAccTime >= m_dInterval)
	{
		m_iCurFrame = (m_iCurFrame + 1) % m_iTimes;
		m_dAccTime = 0.;
	}

	m_ArrSprite[m_iCurFrame]->Draw(_startPosX, _startPosY, _alpha);
}