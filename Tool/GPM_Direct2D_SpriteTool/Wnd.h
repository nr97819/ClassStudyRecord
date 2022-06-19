#pragma once

#include <Windows.h>

#include "Bitmap.h"
#include "resource1.h"

#include "WICBitmap.h"

typedef LRESULT (CALLBACK *PROC_FPTR)(HWND, UINT, WPARAM, LPARAM);
typedef LRESULT (*PROC_MSG_FPTR)(HWND, UINT, WPARAM, LPARAM);

class CWnd
{
protected:
	HINSTANCE				m_hInstance;
	int						m_nCmdShow;

	wstring					m_wClassName = {};
	wstring					m_wTitleName = {};

	HWND					m_hWnd;
	ID2D1HwndRenderTarget*	m_pRenderTarget;

	CBitmap*				m_pMyBitmap;
	CWICBitmap*				m_pMyWICBitmap;

public:
	CWnd();
	virtual ~CWnd();

public:
	HWND Create(HINSTANCE _hInstance, int _nCmdShow, 
		const wstring& _wsClassName, const wstring& _wsTitleName, PROC_FPTR _fpProc, bool _bMenu);
	HRESULT InitTarget();
	HRESULT InitBitmap(const wstring& _wsImageFileName);
	void _ShowWindow();
	void Adjust(const POINT& _ptResolution, const POINT& _ptPos);

public:
	static LRESULT CALLBACK WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam);

	// 자식 Wnd에서 구현
	virtual LRESULT WndMsgProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam) = 0;

public:
	void Update();
	void Render();

public:
	void Release();

public:
	CBitmap* GetMyBitmap() { return m_pMyBitmap; }
	ID2D1HwndRenderTarget* GetRT() { return m_pRenderTarget; }
	HWND GetHwnd() { return m_hWnd; }
};

