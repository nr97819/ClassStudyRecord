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
	
	/*HWND						m_hMainWnd;
	ID2D1HwndRenderTarget*		m_pMainRT;
	ID2D1Bitmap*				m_pD2DMainBitmap;*/

	/*
	HWND						m_hToolWnd;
	ID2D1HwndRenderTarget*		m_pToolRT;
	ID2D1Bitmap*				m_pD2DToolBitmap;*/

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
	HRESULT Init(HWND _hWnd, ID2D1HwndRenderTarget** _pRenderTarget);
	//HRESULT InitTool(HWND _hWnd);
	void Release();

public:
	ID2D1Factory* GetD2D1Factory() { return m_pD2D1Factory; }
	IDWriteFactory* GetDWriteFactory() { return m_pDWriteFactory; }
	IWICImagingFactory* GetWICImagingFactory() { return m_pWICFactory; }


	HRESULT CreateD2D1Bitmap(const wstring& _wsFileName, ID2D1HwndRenderTarget* _pRenderTarget, ID2D1Bitmap** _pD2D1Bitmap);
	//IDWriteTextFormat** CreateMyTextFormat(const WCHAR* _fontName, FLOAT _fontSize);

public:
	/*HWND GetMainHwnd() { return m_hMainWnd; }
	ID2D1HwndRenderTarget* GetMainRT() { return m_pMainRT; }
	ID2D1Bitmap* GetMainD2D1Bitmap() { return m_pD2DMainBitmap; }*/
	
	/*
	HWND GetToolHwnd() { return m_hToolWnd; }
	ID2D1HwndRenderTarget* GetToolRT() { return m_pToolRT; }
	ID2D1Bitmap* GetToolD2D1Bitmap() { return m_pD2DToolBitmap; }*/
};