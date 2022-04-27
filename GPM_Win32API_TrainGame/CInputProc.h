#pragma once

enum class MOUSE_STATE
{
	DOWN,
	UP,
	HOLD, // NOT USED
	NEVER,

	LAST_INDEX
};

class CInputProc
{
private:
	static CInputProc*	m_InputProc;
	POINT				m_pMousePos;

	bool				m_iArrState[(UINT)MOUSE_STATE::LAST_INDEX];
	bool				m_bPrevState;

private:
	CInputProc();
	~CInputProc();

public:
	static CInputProc* GetInst()
	{
		if (nullptr == m_InputProc)
			m_InputProc = new CInputProc();

		return m_InputProc;
	}
	void ReleaseInst();

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

