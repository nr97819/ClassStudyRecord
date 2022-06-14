#include "D2DCore.h"

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "windowscodecs.lib")


CD2DCore::CD2DCore()
	: m_pD2D1Factory(nullptr)
	, m_pDWriteFactory(nullptr)
	, m_pWICFactory(nullptr)
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

HRESULT CD2DCore::Init(HWND _hWnd, ID2D1HwndRenderTarget** _pRenderTarget)
{
	HRESULT hr = S_OK;

	//m_hMainWnd = _hWnd;

	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2D1Factory);
	if (FAILED(hr)) return hr;

	hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory),
		reinterpret_cast<IUnknown**>(&m_pDWriteFactory));
	if (FAILED(hr)) return hr;

	hr = CoCreateInstance(CLSID_WICImagingFactory, NULL,
		CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_pWICFactory));
	if (FAILED(hr)) return hr;

	// Render Target
	RECT rc;
	GetClientRect(_hWnd, &rc);

	m_pD2D1Factory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(_hWnd,
			D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top)),
		_pRenderTarget);

	return S_OK;
}

//HRESULT CD2DCore::InitTool(HWND _hWnd)
//{
//	HRESULT hr = S_OK;
//
//	m_hToolWnd = _hWnd;
//
//	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2D1Factory);
//	if (FAILED(hr)) return hr;
//
//	hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory),
//		reinterpret_cast<IUnknown**>(&m_pDWriteFactory));
//	if (FAILED(hr)) return hr;
//
//	hr = CoCreateInstance(CLSID_WICImagingFactory, NULL,
//		CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_pWICFactory));
//	if (FAILED(hr)) return hr;
//
//	// Render Target
//	RECT rcTool;
//	GetClientRect(m_hToolWnd, &rcTool);
//
//	m_pD2D1Factory->CreateHwndRenderTarget(
//		D2D1::RenderTargetProperties(),
//		D2D1::HwndRenderTargetProperties(m_hToolWnd,
//			D2D1::SizeU(rcTool.right - rcTool.left, rcTool.bottom - rcTool.top)),
//		&m_pToolRT);
//
//	return S_OK;
//}

void CD2DCore::Release()
{
	if (m_pD2D1Factory) { m_pD2D1Factory->Release(); m_pD2D1Factory = nullptr; }
	if (m_pDWriteFactory) { m_pDWriteFactory->Release(); m_pDWriteFactory = nullptr; }
	if (m_pWICFactory) { m_pWICFactory->Release(); m_pWICFactory = nullptr; }
	//if (m_pDWriteTextFormat) { m_pDWriteTextFormat->Release(); m_pDWriteTextFormat = nullptr; }

	// [ Main ]
	/*if (m_pD2DMainBitmap) { m_pD2DMainBitmap->Release(); m_pD2DMainBitmap = nullptr; }
	if (m_pMainRT) { m_pMainRT->Release(); m_pMainRT = nullptr; }*/

	// [ Tool ]
	/*if (m_pD2DToolBitmap) { m_pD2DToolBitmap->Release(); m_pD2DToolBitmap = nullptr; }
	if (m_pToolRT) { m_pToolRT->Release(); m_pToolRT = nullptr; }*/
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

	IWICBitmapDecoder* pDecoder = nullptr;
	IWICBitmapFrameDecode* pFrame = nullptr;
	IWICFormatConverter* pConverter = nullptr;

	// 1. Load Bitmap
	hr = m_pWICFactory->CreateDecoderFromFilename(
		_wsFileName.c_str(),	// Image File Name
		NULL,
		GENERIC_READ,	//desired read access to the file
		WICDecodeMetadataCacheOnLoad, // cache metadata when needed
		&pDecoder);
	if (FAILED(hr)) return hr;

	// 2. 0번 프레임을 열기
	hr = pDecoder->GetFrame(0, &pFrame); // 0번 프레임만 쓰니까 (영상이면 프레임 여럿)
	if (FAILED(hr)) return hr;

	// 3. 컨버터 설정
	hr = m_pWICFactory->CreateFormatConverter(&pConverter);
	if (FAILED(hr)) return hr;

	hr = pConverter->Initialize(pFrame,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		NULL,
		0.f,
		WICBitmapPaletteTypeCustom);
	if (FAILED(hr)) return hr;

	// 4. WIC 비트맵으로부터 -> D2D비트맵 만들기
	hr = _pRenderTarget->CreateBitmapFromWicBitmap(pConverter, NULL, _pD2D1Bitmap);
	if (FAILED(hr)) return hr;

	// 5. 쓰고 난 뒤, 모두 해제 필수
	if (pConverter) { pConverter->Release(); pConverter = nullptr; }
	if (pFrame) { pFrame->Release(); pFrame = nullptr; }
	if (pDecoder) { pDecoder->Release(); pDecoder = nullptr; }

	return S_OK;
}
