#pragma once

#include <windows.h>
#include <stdexcept>
#include <stdlib.h>

#include <string.h>
#include <wchar.h>

#include <time.h>
#include "CGame.h"

class CApp
{
private:
	static CApp*		m_app;
	HWND				m_hWnd;

	WCHAR				m_szWindowClass[50];
	WCHAR				m_szTitle[50];

	HDC					m_hDC;
	HDC					m_hMemDC;
	HINSTANCE			m_hInst;
	HBITMAP				m_hBitmap;
	POINT				m_pResolution;

private:
	CApp();
	~CApp();

public:
	static CApp* GetInst()
	{
		if (nullptr == m_app)
			m_app = new CApp();

		return m_app;
	}
	void ReleaseInst();

	bool InitAPI(HINSTANCE hInstance, int nCmdShow);
	void RunLoop(MSG& _msg);
	void Progress();

public:
	bool Init(HINSTANCE hInstance, int nCmdShow, POINT _pResolution);
	void Update();
	void Render();

public:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK MyProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	HWND GetMainHwnd() { return m_hWnd; }
	POINT GetResolution() { return m_pResolution; }
};

