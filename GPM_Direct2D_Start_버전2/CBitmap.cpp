#include "CBitmap.h"

#include "CApp.h"

#include <d2d1.h>
#include <wincodec.h>
#include <dwrite.h>
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "windowscodecs.lib")


CBitmap::CBitmap()
	: m_pBitmap(nullptr)
	, m_pDwriteFactory(nullptr)
	, m_pDWTextFormat(nullptr)
	, m_pWICFactory(nullptr)
	, m_pBlackBrush(nullptr)
	, m_pYellowBrush(nullptr)
	, m_pGrayBrush(nullptr)
	, m_sourceFileName{}
{}

CBitmap::~CBitmap()
{}

HRESULT CBitmap::Init(ID2D1HwndRenderTarget* _pRenderTarget, WCHAR* _srcName)
{
	//WCHAR wstrName[50] = L"midnight.png";
	//WCHAR wstrName[50] = _srcName;
	LoadBitmapFromFile(_srcName, &m_pBitmap, _pRenderTarget);

	_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &m_pBlackBrush);
	_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Yellow), &m_pYellowBrush);
	_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Gray), &m_pGrayBrush);

	return S_OK;
}

HRESULT CBitmap::LoadBitmapFromFile(PCWSTR _wcFileName, ID2D1Bitmap** _ppBitmap, ID2D1HwndRenderTarget* _pRenderTarget)
{
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
}
