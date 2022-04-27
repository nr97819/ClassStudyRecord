#include "CBitmap.h"

#include <Windows.h>
#include <stdexcept>

CBitmap::CBitmap()
	: m_hBitmap(0)
	, m_lpDIBits(nullptr)
	, m_pBitmapInfo(nullptr)
	, m_cArrSprites{}
	, m_hBmpDC(0)
{}

CBitmap::~CBitmap()
{
	if (nullptr != m_pBitmapInfo)
		delete m_pBitmapInfo;

	if (nullptr != m_hBitmap)
		DeleteObject(m_hBitmap);
}

bool CBitmap::Init()
{
	//UINT pX, pY;
	UINT iX, iY;
	UINT index = 0;
	for (iY = 0; iY < 10; ++iY)
	{
		for (iX = 0; iX < 10; ++iX)
		{
			m_cArrSprites[index] 
				= CSprite(POINT{ (int)iX * FRAME_SIZE, (int)iY * FRAME_SIZE }, FRAME_SIZE);

			index++;
		}
	}

	return false;
}

void CBitmap::Render(HDC _memDC)
{
	UINT spSize = FRAME_SIZE;

	for (UINT i = 0; i < MAX_SIZE; ++i)
	{
		/*BitBlt(_memDC, 0, 0
			, m_cArrSprites[i].GetFramePos().x
			, m_cArrSprites[i].GetFramePos().y
			, m_hBmpDC, 0, 0, SRCCOPY);*/

		BitBlt(_memDC, 0, 0, 100, 100
			, m_hBmpDC, 0, 0, SRCCOPY);
	}
}

void CBitmap::Load(HDC _hDC, const WCHAR* _filename)
{
	HANDLE hFile;
	hFile = CreateFile(_filename, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		throw std::runtime_error("File Error");

	BITMAPFILEHEADER bmFileHeader;
	DWORD dwReadBytes;
	if (false == ReadFile(hFile, &bmFileHeader, sizeof(BITMAPFILEHEADER), &dwReadBytes, NULL))
		throw std::runtime_error("File Error");

	int iBitmapInfoSize = bmFileHeader.bfOffBits - sizeof(BITMAPFILEHEADER);
	m_pBitmapInfo = (BITMAPINFO*) new BYTE[iBitmapInfoSize]; // 메모리 해제 필요
	if (false == ReadFile(hFile, (LPVOID)m_pBitmapInfo, iBitmapInfoSize, &dwReadBytes, NULL))
		throw std::runtime_error("File Error");

	m_hBitmap = CreateDIBSection(_hDC, m_pBitmapInfo, DIB_RGB_COLORS, (void**)&m_lpDIBits, NULL, 0);   // 24 bit dib 

	if (false == ReadFile(hFile, m_lpDIBits, m_pBitmapInfo->bmiHeader.biSizeImage, &dwReadBytes, NULL))
		throw std::runtime_error("File Error");

	m_hBmpDC = CreateCompatibleDC(_hDC);
	SelectObject(m_hBmpDC, m_hBitmap);

	if (hFile)
		CloseHandle(hFile);
}

void CBitmap::Destroy()
{

}

//void CBitmap::ReadBitmap(HDC& _hDC, HDC& _memDC, const WCHAR* _filename)
//{
//	HANDLE hFile;
//	hFile = CreateFile(_filename, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
//	if (hFile == INVALID_HANDLE_VALUE)
//		throw std::runtime_error("File Error");
//
//	BITMAPFILEHEADER bmFileHeader;
//	DWORD dwReadBytes;
//	if (false == ReadFile(hFile, &bmFileHeader, sizeof(BITMAPFILEHEADER), &dwReadBytes, NULL))
//		throw std::runtime_error("File Error");
//
//	int iBitmapInfoSize = bmFileHeader.bfOffBits - sizeof(BITMAPFILEHEADER);
//	m_pBitmapInfo = (BITMAPINFO*) new BYTE[iBitmapInfoSize]; // 메모리 해제 필요
//	if (false == ReadFile(hFile, (LPVOID)m_pBitmapInfo, iBitmapInfoSize, &dwReadBytes, NULL))
//		throw std::runtime_error("File Error");
//
//	m_hBitmap = CreateDIBSection(_hDC, m_pBitmapInfo, DIB_RGB_COLORS, (void**)&m_lpDIBits, NULL, 0);   // 24 bit dib 
//
//	if (false == ReadFile(hFile, m_lpDIBits, m_pBitmapInfo->bmiHeader.biSizeImage, &dwReadBytes, NULL))
//		throw std::runtime_error("File Error");
//
//	_memDC = CreateCompatibleDC(_hDC);
//	SelectObject(_memDC, m_hBitmap);
//
//	if (hFile)
//		CloseHandle(hFile);
//}