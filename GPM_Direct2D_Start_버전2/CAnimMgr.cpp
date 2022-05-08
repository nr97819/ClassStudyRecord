#include "CAnimation.h"

#include "CTimeMgr.h"
#include "CAnimMgr.h"

//#include "CBitmap.h"
#include "CApp.h"
#include <d2d1.h>

CAnimMgr* CAnimMgr::m_inst = nullptr;

CAnimMgr::CAnimMgr()
	: m_animArr{}
	, m_dTimeAcc(0.)
{

}

CAnimMgr::~CAnimMgr()
{
	if (nullptr != m_inst)
		delete m_inst;
}

//void SetAnimation(WCHAR* _wsFileName, ID2D1HwndRenderTarget* _pRenderTarget, UINT _iMaxClip, double _dInterval, CSprite* _pSprites, float _fStartX, float _fStartY)
//{
//	CBitmap* bitmap = new CBitmap();
//	//WCHAR srcName_woman[64] = L"stardewvalley_woman.png";
//	bitmap->Init(_pRenderTarget, _wsFileName);
//
//	UINT index_woman = 0;
//	m_pSprites_woman = new CSprite[iMAxClip_woman]{};
//	D2D1_RECT_F dRectF_woman = {};
//	for (UINT y = 0; y < 1; ++y)
//	{
//		for (UINT x = 0; x < 4; ++x)
//		{
//			dRectF_woman = { 22.f + (16.f * (float)x),
//						148.f + (0.f * (float)y),
//						35.f + (16.f * (float)x),
//						173.f + (0.f * (float)y) };
//			m_pSprites_woman[index_woman] = new CSprite(m_bitmap_woman->GetBitmap(), dRectF_woman);
//			++index_woman;
//		}
//	}
//	CAnimMgr::GetInst()->GetMoveLeft()->SetMaxClip(iMAxClip_woman); // 4
//	CAnimMgr::GetInst()->GetMoveLeft()->SetInterval(0.15);
//	//CAnimMgr::GetInst()->GetMoveLeft()->SetTimeAcc(0.);
//	CAnimMgr::GetInst()->GetMoveLeft()->SetClipBuffer(m_pSprites_woman);
//	//CAnimMgr::GetInst()->GetMoveLeft()->SetActiveClip(0);
//	CAnimMgr::GetInst()->GetMoveLeft()->SetStartPos(50.f, 50.f);
//}

void CAnimMgr::Init()
{
	for (UINT i = 0; i < (UINT)ANIM_INDEX::LAST_INDEX; ++i)
	{
		m_animArr[i] = new CAnimation();
	}
}

void CAnimMgr::Update()
{
	for (UINT i = 0; i < (UINT)ANIM_INDEX::LAST_INDEX; ++i)
	{
		double dMaxTime = m_animArr[i]->GetInterval();
		CSprite* pClipBuff = m_animArr[i]->GetClipBuffer();
		UINT iActiveClip = m_animArr[i]->GetActiveClip();
		UINT iMaxClip = m_animArr[i]->GetMaxClip();

		m_animArr[i]->SetTimeAcc(m_animArr[i]->GetTimeAcc() + CTimeMgr::GetInst()->GetDT());
		//m_dTimeAcc += CTimeMgr::GetInst()->GetDT();
		if (m_animArr[i]->GetTimeAcc() >= dMaxTime)
		{
			iActiveClip = (iActiveClip + 1) % iMaxClip;
			m_animArr[i]->SetActiveClip(iActiveClip);

			m_animArr[i]->SetTimeAcc(0.);
			//m_dTimeAcc = 0.;
		}
	}
}

void CAnimMgr::Render(ID2D1HwndRenderTarget* _pRenderTarget)
{
	for (UINT i = 0; i < (UINT)ANIM_INDEX::LAST_INDEX; ++i)
	{
		UINT iActiveClip = m_animArr[i]->GetActiveClip();
		CSprite* pClipBuff = m_animArr[i]->GetClipBuffer();

		pClipBuff[iActiveClip].Draw(_pRenderTarget, 
									m_animArr[i]->GetStartX(), 
									m_animArr[i]->GetStartY());
	}
}

//void CAnimMgr::Render(ID2D1HwndRenderTarget* _pRenderTarget, float _fStartX, float _fStartY)
//{
//	for (UINT i = 0; i < (UINT)ANIM_INDEX::LAST_INDEX; ++i)
//	{
//		UINT iActiveClip = m_animArr[i]->GetActiveClip();
//		CSprite* pClipBuff = m_animArr[i]->GetClipBuffer();
//
//		pClipBuff[iActiveClip].Draw(_pRenderTarget, _fStartX, _fStartY);
//	}
//}
