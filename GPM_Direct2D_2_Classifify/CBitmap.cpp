#include "CBitmap.h"

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "windowscodecs.lib") // WIC Lib

#include <wchar.h>
#include "CD2DCore.h"


CBitmap::CBitmap()
	: m_pBitmap(nullptr)
{}

CBitmap::~CBitmap()
{}

HRESULT CBitmap::Create(const wstring& _wsFileName)
{
	HRESULT hr = S_OK;

	m_pBitmap = *(CD2DCore::GetInst()->CreateMyD2D1Bitmap(_wsFileName));

	return S_OK;
}

void CBitmap::Release()
{
	// 해제 불가능한 이유를 모르겠다.
	//if (m_pBitmap) { m_pBitmap->Release(); m_pBitmap = nullptr; }
	if (nullptr != this)
		delete this;
}
