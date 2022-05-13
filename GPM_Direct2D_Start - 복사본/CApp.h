#pragma once

#include <Windows.h>
#include <stdlib.h>
#include <string.h>

#include "CSprite.h"
#include "CBitmap.h"

#include <d2d1.h>
#include <dwrite.h>
#include <wincodec.h>

class CApp
{
private:
	static CApp*				m_app;
	WCHAR						m_szWindowClass[64];
	WCHAR						m_szTitle[64];
	POINT						m_ptResolution;
	RECT						m_rtWndSize;
	// =========================================
	HINSTANCE					m_hInst;
	HWND						m_hWnd;
	// =========================================
	ID2D1Factory*				m_pD2DFactory;
	ID2D1HwndRenderTarget*		m_pRenderTarget;
	// =========================================
	/*CSprite*					m_sprite[4];
	UINT						m_iAnimCount;
	double						m_dAnimAcc;*/
	CBitmap*					m_bitmap;
	CBitmap*					m_bitmap_woman;
	CSprite*					m_pSprites;
	CSprite*					m_pSprites_woman;


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

	HRESULT Init(HINSTANCE _hInstance, int _nCmdShow, POINT _ptResolution);
	HRESULT InitAPI(HINSTANCE _hInstance, int _nCmdShow);
	HRESULT InitD2D();

	void ReleaseInst();

	void Run();
	MSG RunLoop();

public:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	void Update();
	void Render();

public:
	HWND GetMainHwnd() { return m_hWnd; }
	POINT GetResolution() { return m_ptResolution; }
	RECT GetWndSize() { return m_rtWndSize; }

};

