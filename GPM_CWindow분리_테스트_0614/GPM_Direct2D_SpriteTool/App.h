#include <Windows.h>

#include "Bitmap.h"
#include "Window.h"


class CApp
{
private:
	HINSTANCE				m_hInstance;

	CWindow*				m_pMainWindow;
	HWND					m_hMainWnd;

	CWindow*				m_pToolWindow;
	HWND					m_hToolWnd;

	// [Tool ������]

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
	HRESULT CreateWindows(HINSTANCE _hInstance, int _nCmdShow);
	//HRESULT InitD2D();

public:
	//void Update(); // �� wnd�� ���⼭ �ϰ� update
	//void Render(); // �� wnd�� ���⼭ �ϰ� render

public:
	int Run();
	void Release();
};