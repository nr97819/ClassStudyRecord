#include <Windows.h>

#include "Bitmap.h"
#include "Window.h"


class CApp
{
private:
	HINSTANCE				m_hInstance;

	CWindow*				m_pWindow;
	HWND					m_hMainWnd;

	//CBitmap*				m_pMyBitmap;
	//ID2D1HwndRenderTarget*	m_pMainRT;

	//ID2D1Factory*			m_pD2D1Factory;
	//IDWriteFactory*			m_pDWriteFactory;
	//IDWriteTextFormat*		m_pDWriteTextFormat;

public:
	CApp();
	~CApp();

public:
	HRESULT Init(HINSTANCE _hInstance, int _nCmdShow);
	//HRESULT InitD2D();

public:
	//void Update(); // 각 wnd들 여기서 일괄 update
	//void Render(); // 각 wnd들 여기서 일괄 render

public:
	int Run();
	void Release();
};