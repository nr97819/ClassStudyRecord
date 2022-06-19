#include "D2DCore.h"

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "windowscodecs.lib")


CD2DCore::CD2DCore()
	: m_pD2D1Factory(nullptr)
	, m_pDWriteFactory(nullptr)
	, m_pIWICFactory(nullptr)

	, m_pIWICBitmap(nullptr)
	//, m_pDWriteTextFormat(nullptr)

	/*, m_pD2DMainBitmap(nullptr)
	, m_pMainRT(nullptr)
	, m_hMainWnd(0)*/

	/*
	, m_pD2DToolBitmap(nullptr)
	, m_pToolRT(nullptr)
	, m_hToolWnd(0)*/
{}

CD2DCore::~CD2DCore()
{}

HRESULT CD2DCore::InitFactory()
{
	HRESULT hr = S_OK;

	// Factory 1
	hr = CoCreateInstance(
		CLSID_WICImagingFactory,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&m_pIWICFactory)
	);
	if (FAILED(hr)) return hr;

	// Factory 2
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2D1Factory);
	if (FAILED(hr)) return hr;

	// Factory 3
	hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory),
		reinterpret_cast<IUnknown**>(&m_pDWriteFactory));
	if (FAILED(hr)) return hr;
	
	return S_OK;
}

HRESULT CD2DCore::InitRenderTarget(HWND _hWnd, ID2D1HwndRenderTarget** _pRenderTarget)
{
	RECT rc;
	GetClientRect(_hWnd, &rc);

	m_pD2D1Factory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(_hWnd,
			D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top)), _pRenderTarget);

	return S_OK;
}

void CD2DCore::Release()
{
	if (m_pD2D1Factory) { m_pD2D1Factory->Release(); m_pD2D1Factory = nullptr; }
	if (m_pDWriteFactory) { m_pDWriteFactory->Release(); m_pDWriteFactory = nullptr; }
	if (m_pIWICFactory) { m_pIWICFactory->Release(); m_pIWICFactory = nullptr; }
	//if (m_pDWriteTextFormat) { m_pDWriteTextFormat->Release(); m_pDWriteTextFormat = nullptr; }

	::SafeRelease(m_pIWICBitmap);
}

/*
IDWriteTextFormat** CD2DCore::CreateMyTextFormat(const WCHAR* _fontName, FLOAT _fontSize)
{
	m_pDWriteFactory->CreateTextFormat(
		_fontName, NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		_fontSize, L"en-us", &m_pDWriteTextFormat);

	return &m_pDWriteTextFormat;
}
*/

HRESULT CD2DCore::CreateD2D1Bitmap(const wstring& _wsFileName, ID2D1HwndRenderTarget* _pRenderTarget, ID2D1Bitmap** _pD2D1Bitmap)
{
	HRESULT hr = S_OK;

	IWICBitmapDecoder*			pIDecoder = nullptr;
	IWICBitmapFrameDecode*		pIDecoderFrame = nullptr;
	IWICFormatConverter*		pIConverter = nullptr;
	//IWICBitmap*					pIBitmap = nullptr;

	// 1. Load Bitmap
	hr = m_pIWICFactory->CreateDecoderFromFilename(
		_wsFileName.c_str(),	// Image File Name
		NULL,
		GENERIC_READ,	//desired read access to the file
		WICDecodeMetadataCacheOnLoad, // cache metadata when needed
		&pIDecoder);
	if (FAILED(hr)) return hr;

	// 2. 0번 프레임을 열기
	hr = pIDecoder->GetFrame(0, &pIDecoderFrame); // 0번 프레임만 쓰니까 (영상이면 프레임 여럿)
	if (FAILED(hr)) return hr;

	// 3. 컨버터 설정
	hr = m_pIWICFactory->CreateFormatConverter(&pIConverter);
	if (FAILED(hr)) return hr;

	hr = pIConverter->Initialize(pIDecoderFrame,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		NULL,
		0.f,
		WICBitmapPaletteTypeCustom);
	if (FAILED(hr)) return hr;

	// 4. WIC 비트맵으로부터 -> D2D비트맵 만들기
	hr = _pRenderTarget->CreateBitmapFromWicBitmap(pIConverter, NULL, _pD2D1Bitmap);
	if (FAILED(hr)) return hr;

	// 4. 이전에 가져온 이미지 프레임에서 IWICBitmap 을 만든다
	if (SUCCEEDED(hr))
	{
		hr = m_pIWICFactory->CreateBitmapFromSource(
			pIDecoderFrame,			// Create a bitmap from the image frame
			WICBitmapCacheOnDemand,	// Cache bitmap pixels on first access
			&m_pIWICBitmap);				// Pointer to the bitmap
	}

	// 5. IWICBitmap의 지정된 사각형에 대한 IWICBitmapLock을 가져온다
	// 6. 이제 IWICBitmapLock 개체에 의해 잠긴 픽셀 데이터를 처리합니다.

	// 7. 만든 개체를 정리합니다.
	::SafeRelease(pIDecoder);
	::SafeRelease(pIDecoderFrame);

	return S_OK;
}
