#pragma once

#include <Windows.h>

#include "Bitmap.h"

class CWindow
{
private:
	WCHAR					m_wsMainWndClassName[64] = {};
	WCHAR					m_wsMainWndTitle[64] = {};

	CBitmap*				m_pMyBitmap;
	ID2D1HwndRenderTarget*	m_pMainRT;
	HWND					m_hWnd;

public:
	CWindow();
	~CWindow();

public:
	HWND Create(HINSTANCE _hInstance, int _nCmdShow);

private:
	HRESULT Init(HINSTANCE _hInstance, int _nCmdShow);
	HRESULT InitD2D();

public:
	static LRESULT CALLBACK MainProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam);
	LRESULT CALLBACK MainMsgProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam);

public:
	void Update();
	void Render();

public:
	void Release();

public:
	HWND GetHwnd() { return m_hWnd; }
};

