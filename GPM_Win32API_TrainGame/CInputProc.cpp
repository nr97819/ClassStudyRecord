#include <Windows.h>

#include "CInputProc.h"
#include "CApp.h"

CInputProc* CInputProc::m_InputProc = nullptr;

CInputProc::CInputProc()
	: m_pMousePos{}
	, m_bPrevState(false)
{}

CInputProc::~CInputProc()
{}

void CInputProc::ReleaseInst()
{
	if (nullptr != m_InputProc)
		delete m_InputProc;
}

bool CInputProc::Init()
{
	return false;
}

void CInputProc::Update()
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
			swprintf_s(wStrBuff, L"X : %d, Y : %d", m_pMousePos.x, m_pMousePos.y);
			SetWindowText(CApp::GetInst()->GetMainHwnd(), wStrBuff);
		}
		else
		{
			// Set State
			m_iArrState[(UINT)MOUSE_STATE::DOWN] = true;

			GetCursorPos(&m_pMousePos);
			ScreenToClient(CApp::GetInst()->GetMainHwnd(), &m_pMousePos);

			wchar_t wStrBuff[255] = {};
			swprintf_s(wStrBuff, L"X : %d, Y : %d", m_pMousePos.x, m_pMousePos.y);
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
		}
		m_iArrState[(UINT)MOUSE_STATE::DOWN] = false;
		m_bPrevState = false;
	}
}