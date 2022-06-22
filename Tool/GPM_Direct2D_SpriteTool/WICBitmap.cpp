#include "WICBitmap.h"

#include "D2DCore.h"

CWICBitmap::CWICBitmap()
	: m_pWICBitmap(nullptr)
{
}

CWICBitmap::~CWICBitmap()
{
}

HRESULT CWICBitmap::Create(const wstring& _wsFileName, ID2D1HwndRenderTarget* _pRenderTarget)
{
	HRESULT hr = S_OK;

	m_pWICBitmap = *(CD2DCore::GetInst()->GetWICBitmap());

	return S_OK;
}

void CWICBitmap::Release()
{
	if (m_pWICBitmap)
	{
		m_pWICBitmap->Release();
		m_pWICBitmap = nullptr;
	}
}

DWORD CWICBitmap::GetPixelColor(UINT _x, UINT _y, UINT _width, UINT _height)
{
	HRESULT hr = S_OK;

	// 크기 초과 예외 처리
	if (_y >= _height)	return 0;
	if (_x >= _width)	return 0;

	int uiWidth = _width;
	int uiHeight = _height;

	DWORD dwResult = 0x00'00'00'00;

	IWICBitmapLock* pILock = NULL;
	WICRect rcLock = { 0, 0, uiWidth, uiHeight };

	// 5. IWICBitmap의 지정된 사각형에 대한 IWICBitmapLock을 가져온다
	if (SUCCEEDED(hr))
	{
		// Obtain a bitmap lock for exclusive write.
		// The lock is for a 10x10 rectangle starting at the top left of the bitmap.
		hr = m_pWICBitmap->Lock(&rcLock, WICBitmapLockWrite, &pILock);
	}

	// 6. 이제 IWICBitmapLock 개체에 의해 잠긴 픽셀 데이터를 처리합니다.
	if (SUCCEEDED(hr))
	{
		UINT cbBufferSize = 0;
		BYTE* pv = NULL;

		if (SUCCEEDED(hr))
		{
			hr = pILock->GetDataPointer(&cbBufferSize, &pv);
		}

		DWORD* temp = (DWORD*)pv;
		temp = temp + (_y * _width) + _x;
		dwResult = *temp;

		//SafeRelease(pILock);
		pILock->Release();

		// IWICBitmap의 잠금을 해제하려면 IWICBitmap과 연결된 
		//		모든 IWICBitmapLock 개체에서 IUnknown::Release를 호출합니다.
	}

	return dwResult;
}
