#pragma once

#include <windows.h>
#include <stdexcept>
#include <stdlib.h>

#include <string.h>
#include <wchar.h>

#include <time.h>

#include "CBitmap.h"
#include "CGame.h"

class CApp
{
private:
	static CApp*		m_app;
	HWND				m_hWnd;
	CBitmap				m_bitmap;

	WCHAR				m_szWindowClass[50];
	WCHAR				m_szTitle[50];

	HBITMAP				m_hBitmap;

	HDC					m_hDC;
	HDC					m_hMemDC;
	HINSTANCE			m_hInst;

	POINT				m_pResolution;

	// test
	HDC					m_hBmpDC = 0;

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
};

