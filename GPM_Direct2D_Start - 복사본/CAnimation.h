#pragma once

#include <Windows.h>
class ID2DBitmap;
class CSprite;

class CAnimation
{
private:
	ID2DBitmap*			m_bitmap;

	UINT				m_iMaxClip;
	double				m_dInterval;
	double				m_dTimeAcc;

	//CSprite*			m_pActiveClip;
	UINT				m_iActiveClip;
	CSprite**			m_pClipBuffer;

	float				m_fStartX;
	float				m_fStartY;

public:
	CAnimation();
	~CAnimation();

public:
	void SetActiveClip(UINT _pActiveClip) { m_iActiveClip = _pActiveClip; }
	void SetMaxClip(UINT _iMaxClip) { m_iMaxClip = _iMaxClip; }
	void SetClipBuffer(CSprite** _pClipBuffer) { m_pClipBuffer = _pClipBuffer; }
	void SetInterval(double _dInterval) { m_dInterval = _dInterval; }
	void SetTimeAcc(double _dTimeAcc) { m_dTimeAcc = _dTimeAcc; }
	void SetStartPos(float _fStartX, float _fStartY)
	{
		m_fStartX = _fStartX;
		m_fStartY = _fStartY;
	}
	
	UINT GetActiveClip() { return m_iActiveClip; }
	UINT GetMaxClip() { return m_iMaxClip; }
	CSprite* GetClipBuffer() { return m_pClipBuffer; }
	double GetInterval() { return m_dInterval; }
	double GetTimeAcc() { return m_dTimeAcc; }
	float GetStartX() { return m_fStartX; }
	float GetStartY() { return m_fStartY; }
};

