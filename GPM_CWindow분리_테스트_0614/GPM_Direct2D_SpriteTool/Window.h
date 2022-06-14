#pragma once

#include <Windows.h>

#include "Bitmap.h"

class CWindow
{
private:
	wstring					m_wClassName = {};
	wstring					m_wTitleName = {};

	CBitmap*				m_pMyBitmap;
	ID2D1HwndRenderTarget*	m_pRenderTarget;
	HWND					m_hWnd;

	HINSTANCE				m_hInstance;
	int						m_nCmdShow;

public:
	CWindow();
	~CWindow();

public:
	HWND Create(HINSTANCE _hInstance, int _nCmdShow, const wstring& _wClassName, const wstring& _wTitleName);
	HRESULT LinkRenderTarget();
	void _ShowWindow();
	void Adjust(const POINT& _ptResolution, const POINT& _ptPos);

public:
	static LRESULT CALLBACK MainProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam);
	LRESULT CALLBACK MainMsgProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam);

	static LRESULT CALLBACK ToolProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam);
	LRESULT CALLBACK ToolMsgProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam);

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

