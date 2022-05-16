#include "CTimeMgr.h"

#include <Windows.h>
#include <wchar.h>

#include "CGameApp.h"
#include "CD2DCore.h"

CTimeMgr* CTimeMgr::m_inst = nullptr;

CTimeMgr::CTimeMgr()
	: m_llCurCount{}
	, m_llPrevCount{}
	, m_llFrequency{}
	, m_dDT(0.)
	, m_dAcc(0.)
	, m_iCallCount(0)
	, m_iFPS(0)
{}

CTimeMgr::~CTimeMgr()
{
	/*if (nullptr != m_inst)
		delete m_inst;*/
}

void CTimeMgr::Init()
{
	QueryPerformanceCounter(&m_llPrevCount);
	QueryPerformanceFrequency(&m_llFrequency);
}

void CTimeMgr::Update()
{
	QueryPerformanceCounter(&m_llCurCount);

	m_dDT = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart)
		/ (double)(m_llFrequency.QuadPart);

	m_llPrevCount = m_llCurCount;
	++m_iCallCount;
	m_dAcc += m_dDT;

	if (m_dAcc >= 1.)
	{
		m_iFPS = m_iCallCount;

		WCHAR wsBuf[64] = {};
		swprintf_s(wsBuf, L"FPS : %d", m_iFPS);
		SetWindowText(CD2DCore::GetInst()->GetHWnd(), wsBuf);

		m_dAcc = 0;
		m_iCallCount = 0;
	}


}
