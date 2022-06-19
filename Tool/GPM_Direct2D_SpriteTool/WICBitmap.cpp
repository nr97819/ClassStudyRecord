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

	int uiWidth = _width;
	int uiHeight = _height;

	DWORD dwResult = 0x00'00'00'00;

	IWICBitmapLock* pILock = NULL;
	WICRect rcLock = { 0, 0, uiWidth, uiHeight };


	// 5. IWICBitmap�� ������ �簢���� ���� IWICBitmapLock�� �����´�
	if (SUCCEEDED(hr))
	{
		// Obtain a bitmap lock for exclusive write.
		// The lock is for a 10x10 rectangle starting at the top left of the bitmap.
		hr = m_pWICBitmap->Lock(&rcLock, WICBitmapLockWrite, &pILock);
	}
	// 6. ���� IWICBitmapLock ��ü�� ���� ��� �ȼ� �����͸� ó���մϴ�.
	if (SUCCEEDED(hr))
	{
		UINT cbBufferSize = 0;
		BYTE* pv = NULL;

		if (SUCCEEDED(hr))
		{
			hr = pILock->GetDataPointer(&cbBufferSize, &pv);
		}

// ########## Pixel manipulation using the image data pointer pv. ##########
		UINT BYTE_SIZE = 8;
		UINT RGB_BYTE_SIZE = 4;	
		UINT RGB_SIZE = (BYTE_SIZE * RGB_BYTE_SIZE);
		UINT offset = (_y * RGB_SIZE * _width) + _x * RGB_SIZE;

		/*for (UINT i = 0; i < cbBufferSize / RGB_SIZE; ++i)
		{
			BYTE value_1 = offset * (i + 0);
			BYTE value_2 = offset + (i + 1);
			BYTE value_3 = offset + (i + 2);
			offset += (i + 3);
		}*/

		//dwResult = (pv + offset + 0);
		//offset = 1;

		dwResult |= *(pv + offset / 2  + 0);
		dwResult = dwResult << 8;
		dwResult |= *(pv + offset / 2 + 1);
		dwResult = dwResult << 8;
		dwResult |= *(pv + offset / 2 + 2);
		dwResult = dwResult << 8;
		dwResult |= *(pv + offset / 2 + 3);
// ########## Release the bitmap lock. ##########

		//SafeRelease(pILock);
		pILock->Release();

		// IWICBitmap�� ����� �����Ϸ��� IWICBitmap�� ����� 
		//		��� IWICBitmapLock ��ü���� IUnknown::Release�� ȣ���մϴ�.
	}

	return dwResult;
}
