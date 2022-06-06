#pragma once

// ======== Direct2D ========
#include <d2d1.h>
#include <dwrite.h>
#include <wincodec.h>
// ==========================

#include <Windows.h>
#include <string>
using std::wstring;


class CD2DCore
{
private:
	ID2D1Factory*				m_pD2D1Factory;
	IDWriteFactory*				m_pDWriteFactory;
	IWICImagingFactory*			m_pWICFactory;
	//IDWriteTextFormat*			m_pDWriteTextFormat;
	
	HWND						m_hMainWnd;
	ID2D1HwndRenderTarget*		m_pMainRT;
	ID2D1Bitmap*				m_pD2DMainBitmap;

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
	HRESULT Init(HWND m_hMainWnd);
	void Release();

public:
	ID2D1Factory* GetD2D1Factory() { return m_pD2D1Factory; }
	IDWriteFactory* GetDWriteFactory() { return m_pDWriteFactory; }
	IWICImagingFactory* GetWICImagingFactory() { return m_pWICFactory; }
	ID2D1Bitmap** CreateMainD2D1Bitmap(const wstring& _wsFileName);
	//IDWriteTextFormat** CreateMyTextFormat(const WCHAR* _fontName, FLOAT _fontSize);

public:
	ID2D1HwndRenderTarget* GetMainRT() { return m_pMainRT; }
	ID2D1Bitmap* GetMainD2D1Bitmap() { return m_pD2DMainBitmap; }
	HWND GetMainHwnd() { return m_hMainWnd; }
};