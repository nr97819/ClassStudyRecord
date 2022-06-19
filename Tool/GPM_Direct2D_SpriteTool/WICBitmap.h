#pragma once

// ======== Direct2D ========
#include <d2d1.h>
#include <dwrite.h>
#include <wincodec.h>
// ==========================

#include <string>
using std::wstring;

class CWICBitmap
{
private:
	IWICBitmap* m_pWICBitmap;

public:
	CWICBitmap();
	~CWICBitmap();

public:
	HRESULT Create(const wstring& _wsFileName, ID2D1HwndRenderTarget* _pRenderTarget);
	void Release();

public:
	IWICBitmap* GetWICBitmap() { return m_pWICBitmap; }

public:
	DWORD GetPixelColor(UINT _x, UINT _y, UINT _width, UINT _height);
};

