#pragma once

#include <Windows.h>
#include <stdlib.h>
#include <string.h>

#include <d2d1.h>
#pragma comment(lib, "d2d1.lib")
#include <dwrite.h>
#pragma comment(lib, "dwrite.lib")

class CApp
{
private:
	static CApp*			m_app;
	WCHAR					m_szWindowClass[64];
	WCHAR					m_szTitle[64];
	POINT					m_ptResolution;
	RECT					m_rtWndSize;

	HINSTANCE				m_hInst;
	HWND					m_hWnd;


	ID2D1Factory*			m_pD2DFactory;
	ID2D1HwndRenderTarget*	m_pRenderTarget;
	IDWriteFactory*			m_pDwriteFactory; // COM 인터페이스를 사용하는 출발점
	IDWriteTextFormat*		m_pDWTextFormat;

	ID2D1SolidColorBrush*	m_pBlackBrush;
	ID2D1SolidColorBrush*	m_pYellowBrush;
	ID2D1SolidColorBrush*	m_pGrayBrush;

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

	void ReleaseInst() 
	{
		if (nullptr != m_app)
			delete m_app;
	}
	MSG RunLoop();

public:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	void Update();
	void Render();

public:
	POINT GetResolution() { return m_ptResolution; }
	RECT GetWndSize() { return m_rtWndSize; }
};

