#pragma once

#include <Windows.h>

// ======== Direct2D ========
#include <d2d1.h>
#include <dwrite.h>
#include <wincodec.h>
// ==========================

#include <string>
using std::wstring;

class CD2DCore
{
private:
	ID2D1Factory*				m_pD2D1Factory;
	IDWriteFactory*				m_pDWriteFactory;
	IWICImagingFactory*			m_pWICFactory;

	IDWriteTextFormat*			m_pDWriteTextFormat;
	ID2D1HwndRenderTarget*		m_pRenderTarget;

	ID2D1Bitmap*				m_pBitmap;
	HWND						m_hWnd;

public:
	static CD2DCore* GetInst()
	{
		static CD2DCore* m_inst = new CD2DCore;

		return m_inst;
	}

private:
	CD2DCore();
	~CD2DCore();

public:
	HRESULT Init(HWND m_hWnd);
	void Release();

public:
	ID2D1Factory** CreateMyD2D1Factory() { return &m_pD2D1Factory; }
	IDWriteFactory** CreateMyDWriteFactory() { return &m_pDWriteFactory; }
	IWICImagingFactory** CreateMyWICImagingFactory() { return &m_pWICFactory; }
	ID2D1HwndRenderTarget** CreateMyRenderTarget() { return &m_pRenderTarget; }

	IDWriteTextFormat** CreateMyTextFormat(const WCHAR* _fontName, FLOAT _fontSize);
	ID2D1Bitmap** CreateMyD2D1Bitmap(const wstring& _wsFileName);

public:
	HWND GetHWnd() { return m_hWnd; }
};