#include "Bitmap.h"

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "windowscodecs.lib") // WIC Lib

#include <wchar.h>
#include "D2DCore.h"


CBitmap::CBitmap()
	: m_pD2DBitmap(nullptr)
{}

CBitmap::~CBitmap()
{}

HRESULT CBitmap::Create(const wstring& _wsFileName, ID2D1HwndRenderTarget* _pRenderTarget)
{
	HRESULT hr = S_OK;

	CD2DCore::GetInst()->CreateD2D1Bitmap(_wsFileName, _pRenderTarget, &m_pD2DBitmap);

	return S_OK;
}

void CBitmap::Release()
{
	if (m_pD2DBitmap) 
	{ 
		m_pD2DBitmap->Release(); 
		m_pD2DBitmap = nullptr; 
	}
}
