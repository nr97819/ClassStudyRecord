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
	// 해제 불가능한 이유를 모르겠다.
	
	//if (m_pD2DMainBitmap) { m_pD2DMainBitmap->Release(); m_pD2DMainBitmap = nullptr; }
	//if (m_pD2DToolBitmap) { m_pD2DToolBitmap->Release(); m_pD2DToolBitmap = nullptr; }

	if (nullptr != this)
		delete this;
}
