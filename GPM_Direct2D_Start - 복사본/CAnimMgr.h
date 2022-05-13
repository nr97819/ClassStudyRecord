#pragma once

#include "CAnimation.h"
#include <d2d1.h>
#include "CSprite.h"

enum class ANIM_INDEX
{
	Background_Midnight, // 0
	Character_Move_Left, // 1
	//Character_Move_Right,

	LAST_INDEX
};

class CAnimation;

class CAnimMgr
{
private:
	static CAnimMgr*		m_inst;

private:
	CAnimation*				m_animArr[(int)ANIM_INDEX::LAST_INDEX];
	/*CAnimation*			m_character_moveLeft;
	CAnimation*				m_character_moveRight;*/

	double					m_dTimeAcc;

private:
	CAnimMgr();
	~CAnimMgr();

public:
	static CAnimMgr* GetInst()
	{
		if (nullptr == m_inst)
			m_inst = new CAnimMgr();

		return m_inst;
	}

	void ReleaseInst()
	{
		for (UINT i = 0; i < (UINT)ANIM_INDEX::LAST_INDEX; ++i)
		{
			if(nullptr != m_animArr[i])
				delete m_animArr[i];
		}
	}

	void Init();
	void Update();
	void Render(ID2D1HwndRenderTarget* _pRenderTarget);
	//void Render(ID2D1HwndRenderTarget* _pRenderTarget, float _fStartX, float _fStartY);

public:
	CAnimation* GetAnimMidnight() { return m_animArr[(int)ANIM_INDEX::Background_Midnight]; }
	CAnimation* GetMoveLeft() { return m_animArr[(int)ANIM_INDEX::Character_Move_Left]; }
	//CAnimation* GetMoveRight() { return m_animArr[(int)ANIM_INDEX::Character_Move_Right]; }

	/*void SetAnimation(WCHAR* _wsFileName, ID2D1HwndRenderTarget* _pRenderTarget, 
		UINT _iMaxClip, double _dInterval, CSprite* _pSprites, float _fStartX, float _fStartY);*/
};
/*
: m_bitmap(nullptr)
	, m_iMaxClip(0)
	, m_iActiveClip(0)
	, m_dInterval(0.)
	, m_dTimeAcc(0.)
	, m_pClipBuffer(nullptr)
	, m_fStartX(0.f)
	, m_fStartY(0.f)
*/

