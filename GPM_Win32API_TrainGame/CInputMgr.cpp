#include <Windows.h>

#include "CInputMgr.h"
#include "CApp.h"

CInputMgr* CInputMgr::m_InputProc = nullptr;

CInputMgr::CInputMgr()
	: m_pMousePos{}
	, m_bPrevState(false)
{}

CInputMgr::~CInputMgr()
{}

bool CInputMgr::Init()
{
	return false;
}

void CInputMgr::Update()
{
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (m_bPrevState == true)
		{
			// Set State
			m_iArrState[(UINT)MOUSE_STATE::DOWN] = true;
			//m_iArrState[(UINT)MOUSE_STATE::HOLD] = true;

			GetCursorPos(&m_pMousePos);
			ScreenToClient(CApp::GetInst()->GetMainHwnd(), &m_pMousePos);

			wchar_t wStrBuff[255] = {};
			swprintf_s(wStrBuff, L"X : %d, Y : %d, (%d, %d)", m_pMousePos.x, m_pMousePos.y, (int)(m_pMousePos.x / 70.f), (int)(m_pMousePos.y / 70.f));
			SetWindowText(CApp::GetInst()->GetMainHwnd(), wStrBuff);
		}
		else
		{
			// Set State
			m_iArrState[(UINT)MOUSE_STATE::DOWN] = true;

			GetCursorPos(&m_pMousePos);
			ScreenToClient(CApp::GetInst()->GetMainHwnd(), &m_pMousePos);

			wchar_t wStrBuff[255] = {};
			swprintf_s(wStrBuff, L"X : %d, Y : %d, (%d, %d)", m_pMousePos.x, m_pMousePos.y, (int)(m_pMousePos.x / 70.f), (int)(m_pMousePos.y / 70.f));
			SetWindowText(CApp::GetInst()->GetMainHwnd(), wStrBuff);
		}
		m_iArrState[(UINT)MOUSE_STATE::UP] = false;
		m_iArrState[(UINT)MOUSE_STATE::NEVER] = false;
		m_bPrevState = true;
	}
	else
	{
		if (m_bPrevState == true)
		{
			m_iArrState[(UINT)MOUSE_STATE::UP] = true;
		}
		else
		{
			m_iArrState[(UINT)MOUSE_STATE::NEVER] = true;
			m_iArrState[(UINT)MOUSE_STATE::UP] = false;
		}
		m_iArrState[(UINT)MOUSE_STATE::DOWN] = false;
		m_bPrevState = false;
	}
}