#include "CD2DCore.h"

// ======== Direct2D ========
#include <d2d1.h>
#include <dwrite.h>
#include <wincodec.h>
// ==========================
#include <Windows.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "windowscodecs.lib") // WIC Lib

#include <string>
using std::wstring;

CD2DCore::CD2DCore()
	: m_pD2D1Factory(nullptr)
	, m_pDWriteFactory(nullptr)
	, m_pWICFactory(nullptr)
	, m_pDWriteTextFormat(nullptr)
	, m_pBitmap(nullptr)
	, m_pRenderTarget(nullptr)
	, m_hWnd(0)
{}

CD2DCore::~CD2DCore()
{}

HRESULT CD2DCore::Init(HWND _hWnd)
{
	HRESULT hr = S_OK;

	m_hWnd = _hWnd;

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
	GetClientRect(m_hWnd, &rc);

	m_pD2D1Factory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(m_hWnd,
			D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top)),
		&m_pRenderTarget);

	return S_OK;
}

void CD2DCore::Release()
{
	if (m_pD2D1Factory) { m_pD2D1Factory->Release(); m_pD2D1Factory = nullptr; }
	if (m_pDWriteFactory) { m_pDWriteFactory->Release(); m_pDWriteFactory = nullptr; }
	if (m_pWICFactory) { m_pWICFactory->Release(); m_pWICFactory = nullptr; }
	if (m_pDWriteTextFormat) { m_pDWriteTextFormat->Release(); m_pDWriteTextFormat = nullptr; }
	if (m_pBitmap) { m_pBitmap->Release(); m_pBitmap = nullptr; }
	if (m_pRenderTarget) { m_pRenderTarget->Release(); m_pRenderTarget = nullptr; }
}

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

ID2D1Bitmap** CD2DCore::CreateMyD2D1Bitmap(const wstring& _wsFileName)
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
	if (FAILED(hr)) return nullptr;

	// 2. 0번 프레임을 열기
	hr = pDecoder->GetFrame(0, &pFrame); // 0번 프레임만 쓰니까 (영상이면 프레임 여럿)
	if (FAILED(hr)) return nullptr;

	// 3. 컨버터 설정
	hr = m_pWICFactory->CreateFormatConverter(&pConverter);
	if (FAILED(hr)) return nullptr;

	hr = pConverter->Initialize(pFrame,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		NULL,
		0.f,
		WICBitmapPaletteTypeCustom);
	if (FAILED(hr)) return nullptr;

	// 4. WIC 비트맵으로부터 -> D2D비트맵 만들기
	hr = m_pRenderTarget->CreateBitmapFromWicBitmap(pConverter, NULL, &m_pBitmap);
	if (FAILED(hr)) return nullptr;

	// 5. 쓰고 난 뒤, 모두 해제 필수
	if (pConverter) { pConverter->Release(); pConverter = nullptr; }
	if (pFrame) { pFrame->Release(); pFrame = nullptr; }
	if (pDecoder) { pDecoder->Release(); pDecoder = nullptr; }

	return &m_pBitmap;
}

