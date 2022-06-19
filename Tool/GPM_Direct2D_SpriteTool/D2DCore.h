#pragma once

// ======== Direct2D ========
#include <d2d1.h>
#include <dwrite.h>
#include <wincodec.h>
// ==========================

#include <Windows.h>
#include <string>
using std::wstring;

#include <stdexcept>
#include <limits>

template<typename T>
UINT SafeRelease(T*& pUnk)
{
	UINT ret = 0;
	::IUnknown* pUnknown = nullptr;

	if (pUnk == nullptr)
	{
		return 0;
	}

	pUnknown = dynamic_cast<::IUnknown*>(pUnk);

	if (pUnknown == nullptr)
	{
		//throw std::InvalidAccessException(L"Is not derived from IUnknown");
		throw std::invalid_argument("Is not derived from IUnknown");
	}

	ret = pUnknown->Release();
	pUnknown = nullptr;

	return ret;
}

class CD2DCore
{
private:
	ID2D1Factory*				m_pD2D1Factory;
	IDWriteFactory*				m_pDWriteFactory;
	IWICImagingFactory*			m_pIWICFactory;

	IWICBitmap*					m_pIWICBitmap;
	//IDWriteTextFormat*		m_pDWriteTextFormat;
	
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
	HRESULT InitFactory();
	HRESULT InitRenderTarget(HWND _hWnd, ID2D1HwndRenderTarget** _pRenderTarget);
	void Release();

public:
	ID2D1Factory* GetD2D1Factory() { return m_pD2D1Factory; }
	IDWriteFactory* GetDWriteFactory() { return m_pDWriteFactory; }
	IWICImagingFactory* GetWICImagingFactory() { return m_pIWICFactory; }

	HRESULT CreateD2D1Bitmap(const wstring& _wsFileName, ID2D1HwndRenderTarget* _pRenderTarget, ID2D1Bitmap** _pD2D1Bitmap);
	//IDWriteTextFormat** CreateMyTextFormat(const WCHAR* _fontName, FLOAT _fontSize);

	IWICBitmap** GetWICBitmap() { return &m_pIWICBitmap; }

public:
	void Test()
	{
		// 1. IWICImagingFactory 개체를 만들어 WIC(Windows Imaging Component) 개체를 만듭니다.
		// (D2DCore->Init()에서 이미 존재)

		// 2. CreateDecoderFromFilename 메서드를 사용하여 이미지 파일에서 IWICBitmapDecoder를 만든다
		HRESULT hr = S_OK;

		IWICBitmapDecoder* pIDecoder = NULL;
		IWICBitmapFrameDecode* pIDecoderFrame = NULL;

		// Make "Decoder" from "Image File"
		hr = m_pIWICFactory->CreateDecoderFromFilename(
			L"images\\woman.png",					// Image to be decoded
			NULL,							// Do not prefer a particular vendor
			GENERIC_READ,					// Desired read access to the file
			WICDecodeMetadataCacheOnDemand,	// Cache metadata when needed
			&pIDecoder						// Pointer to the decoder
		);

		// 3. 이미지의 첫 번째 IWICBitmapFrameDecode 를 가져온다.
		if (SUCCEEDED(hr))
		{
			hr = pIDecoder->GetFrame(0, &pIDecoderFrame);
		}

		IWICBitmap* pIBitmap = NULL;
		IWICBitmapLock* pILock = NULL;

		int uiWidth = 10;
		int uiHeight = 10;

		WICRect rcLock = { 0, 0, uiWidth, uiHeight };

		// 4. 이전에 가져온 이미지 프레임에서 IWICBitmap 을 만든다
		if (SUCCEEDED(hr))
		{
			hr = m_pIWICFactory->CreateBitmapFromSource(
				pIDecoderFrame,			// Create a bitmap from the image frame
				WICBitmapCacheOnDemand,	// Cache bitmap pixels on first access
				&pIBitmap);				// Pointer to the bitmap
		}

		// 5. IWICBitmap의 지정된 사각형에 대한 IWICBitmapLock을 가져온다
		if (SUCCEEDED(hr))
		{
			// Obtain a bitmap lock for exclusive write.
			// The lock is for a 10x10 rectangle starting at the top left of the bitmap.
			hr = pIBitmap->Lock(&rcLock, WICBitmapLockWrite, &pILock);
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

			// Pixel manipulation using the image data pointer pv.
			// ...
			// Release the bitmap lock.
			
			//SafeRelease(pILock);
			pILock->Release();

			// IWICBitmap의 잠금을 해제하려면 IWICBitmap과 연결된 
			//		모든 IWICBitmapLock 개체에서 IUnknown::Release를 호출합니다.
		}

		// 7. 만든 개체를 정리합니다.
		::SafeRelease(pIBitmap);
		::SafeRelease(pIDecoder);
		::SafeRelease(pIDecoderFrame);
		/*pIBitmap->Release();
		pIDecoder->Release();
		pIDecoderFrame->Release();*/
	}

	/*HWND GetMainHwnd() { return m_hMainWnd; }
	ID2D1HwndRenderTarget* GetMainRT() { return m_pMainRT; }
	ID2D1Bitmap* GetMainD2D1Bitmap() { return m_pD2DMainBitmap; }*/
	
	/*
	HWND GetToolHwnd() { return m_hToolWnd; }
	ID2D1HwndRenderTarget* GetToolRT() { return m_pToolRT; }
	ID2D1Bitmap* GetToolD2D1Bitmap() { return m_pD2DToolBitmap; }*/
};