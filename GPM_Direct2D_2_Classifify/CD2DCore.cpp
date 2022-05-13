#include "CD2DCore.h"

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "windowscodecs.lib") // WIC Lib

CD2DCore::CD2DCore()
	: m_pD2DFactory(nullptr)
	, m_pDWriteFactory(nullptr)
	, m_pWICFactory(nullptr)
{

}

CD2DCore::~CD2DCore()
{

}

HRESULT CD2DCore::Init()
{
	// RenderTarget 생성
	/*if (FAILED(
		m_pD2DFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(
				m_hWnd, D2D1::SizeU(
					m_rtWndSize.right - m_rtWndSize.left,
					m_rtWndSize.bottom - m_rtWndSize.top)),
			&m_pRenderTarget)))
		return E_FAIL;*/

	HRESULT hr = S_OK;

	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2DFactory);
	if (FAILED(hr)) return hr;

	hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory),
		reinterpret_cast<IUnknown**>(&m_pDWriteFactory));
	if (FAILED(hr)) return hr;

	hr = CoCreateInstance(CLSID_WICImagingFactory, NULL,
		CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_pWICFactory));
	if (FAILED(hr)) return hr;




	IWICFormatConverter* pConverter = nullptr;
	hr = m_pWICFactory->CreateFormatConverter(&pConverter);
	if (FAILED(hr))
		return E_FAIL;
	
	return S_OK;

	/*
	HRESULT hr = S_OK;
	IWICBitmapDecoder* pDecoder = nullptr;

	hr = CoCreateInstance(CLSID_WICImagingFactory, NULL,
		CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_pWICFactory));

	if (FAILED(hr))
		return E_FAIL;

	// 1. Load Bitmap
	hr = m_pWICFactory->CreateDecoderFromFilename(
		_wcFileName,	// Image File Name
		NULL,
		GENERIC_READ,	//desired read access to the file
		WICDecodeMetadataCacheOnLoad, // cache metadata when needed
		&pDecoder);

	if (FAILED(hr))
		return E_FAIL;

	// 2. 0번 프레임을 열기
	IWICBitmapFrameDecode* pFrame = nullptr;
	hr = pDecoder->GetFrame(0, &pFrame);

	if (FAILED(hr))
		return E_FAIL;

	// 3. 컨버터 설정
	IWICFormatConverter* pConverter = nullptr;
	hr = m_pWICFactory->CreateFormatConverter(&pConverter);

	if (FAILED(hr))
		return E_FAIL;

	hr = pConverter->Initialize(pFrame,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		NULL,
		0.f,
		WICBitmapPaletteTypeCustom);

	if (FAILED(hr))
		return E_FAIL;

	// Create a Direct2D bitmap from the WIC bitmap
	hr = _pRenderTarget->CreateBitmapFromWicBitmap(
		pConverter,
		NULL,
		_ppBitmap);

	if (FAILED(hr))
		return hr;

	if (pConverter)
	{
		pConverter->Release();
		pConverter = nullptr;
	}
	if (pFrame)
	{
		pFrame->Release();
		pFrame = nullptr;
	}
	if (pDecoder)
	{
		pDecoder->Release();
		pDecoder = nullptr;
	}

	return S_OK;
	*/
}
