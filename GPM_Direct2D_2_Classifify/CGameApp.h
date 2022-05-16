#pragma once

// ======== Direct2D ========
#include <d2d1.h>
#include <dwrite.h>
#include <wincodec.h>
// ==========================

#define MAX_ANIM_POSSESS 10

class CBitmap;
class CSprite;
class CAnimation;

enum class ANIM_INDEX
{
	MIDNIGHT,
	CHARACTER_WOMAN,

	_LAST_INDEX_
};

class CGameApp
{
private:
	HWND						m_hWnd;
	HINSTANCE					m_hInstance;
	WCHAR						m_szWindowClass[32];
	WCHAR						m_szTitle[64];

	ID2D1Factory*				m_pD2D1Factory;
	IDWriteFactory*				m_pDWriteFactory;

	IDWriteTextFormat*			m_pDWriteTextFormat;
	ID2D1HwndRenderTarget*		m_pRenderTarget;

	CBitmap*					m_pMyBitmap;
	ID2D1Bitmap*				m_pBitmap;
	ID2D1SolidColorBrush*		m_pBlackBrush;

private:
	CSprite*					m_sprite_sample;
	CAnimation*					m_pArrAnims[MAX_ANIM_POSSESS];

public:
	CGameApp();
	~CGameApp();

public:
	HRESULT Init(HINSTANCE hInstance, int nCmdShow);
	void Release();
	void Update();
	void Render();

public:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	HRESULT InitAPI(HINSTANCE hInstance, int nCmdShow);
	int RunLoop();
};

