#pragma once

class CResMgr
{
private:
	static CResMgr* m_inst;

private:
	CResMgr();
	~CResMgr();

public:
	static CResMgr* GetInst()
	{
		if (nullptr == m_inst)
			m_inst = new CResMgr();

		return m_inst;
	}

	void Init();
	void Update();
};

