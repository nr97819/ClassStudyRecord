#pragma once

#include <d2d1.h>
#include <wincodec.h>
#include <dwrite.h>

class CBitmap
{
private:
	ID2D1Bitmap*				m_pBitmap;

	IDWriteFactory*				m_pDwriteFactory; // COM 인터페이스를 사용하는 출발점
	IDWriteTextFormat*			m_pDWTextFormat;
	IWICImagingFactory*			m_pWICFactory;

	ID2D1SolidColorBrush*		m_pBlackBrush;
	ID2D1SolidColorBrush*		m_pYellowBrush;
	ID2D1SolidColorBrush*		m_pGrayBrush;

	WCHAR						m_sourceFileName[64];

public:
	CBitmap();
	~CBitmap();

public:
	HRESULT Init(ID2D1HwndRenderTarget* _pRenderTarget, WCHAR* _srcName);

public:
	ID2D1Bitmap* GetBitmap() { return m_pBitmap; }

public:
	HRESULT LoadBitmapFromFile(PCWSTR _wcFileName, ID2D1Bitmap** _ppBitmap, ID2D1HwndRenderTarget* _pRenderTarget);
};

