#pragma once

#include <Windows.h>

class CTimeMgr
{
private:
	static CTimeMgr*	m_inst;

	LARGE_INTEGER		m_llCurCount;
	LARGE_INTEGER		m_llPrevCount;
	LARGE_INTEGER		m_llFrequency;

	double				m_dDT;
	double				m_dAcc;
	UINT				m_iCallCount;
	UINT				m_iFPS;

private:
	CTimeMgr();
	~CTimeMgr();

public:
	static CTimeMgr* GetInst()
	{
		static CTimeMgr* m_inst = new CTimeMgr;

		return m_inst;
	}
	/*static CTimeMgr* GetInst()
	{
		if (nullptr == m_inst)
			m_inst = new CTimeMgr();

		return m_inst;
	}*/

	void ReleaseInst()
	{
		if (nullptr != m_inst)
			delete m_inst;
	}

	void Init();
	void Update();

public:
	double GetDT() { return m_dDT; }
};

