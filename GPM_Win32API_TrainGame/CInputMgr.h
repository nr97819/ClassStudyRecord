#pragma once

#include <Windows.h>

enum class MOUSE_STATE
{
	DOWN,
	UP,
	HOLD, // NOT USED
	NEVER,

	LAST_INDEX
};

class CInputMgr
{
private:
	static CInputMgr*	m_InputProc;
	POINT				m_pMousePos;

	bool				m_iArrState[(UINT)MOUSE_STATE::LAST_INDEX];
	bool				m_bPrevState;

private:
	CInputMgr();
	~CInputMgr();

public:
	static CInputMgr* GetInst()
	{
		if (nullptr == m_InputProc)
			m_InputProc = new CInputMgr();

		return m_InputProc;
	}

	void ReleaseInst()
	{
		if (nullptr != m_InputProc)
			delete m_InputProc;
	}

public:
	bool Init();
	void Update();

public:
	POINT GetMousePos() { return m_pMousePos; }
	bool GetPrevState() { return m_bPrevState; }
	
	// Get Mouse State (func)
	bool IsMouseDown() { return m_iArrState[(UINT)MOUSE_STATE::DOWN]; }
	bool IsMouseUp() { return m_iArrState[(UINT)MOUSE_STATE::UP]; }
};

