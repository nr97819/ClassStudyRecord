#include "CResourceMgr.h"

#include <Windows.h>
#include <stdexcept>

#include "CApp.h"

CResourceMgr* CResourceMgr::m_instance = nullptr;

CResourceMgr::CResourceMgr()
	: m_hBitmap(0)
	, m_lpDIBits(nullptr)
	, m_pBitmapInfo(nullptr)
	, m_cArrSprites{}
	, m_hBmpDC(0)
{}

CResourceMgr::~CResourceMgr()
{
	if (nullptr != m_pBitmapInfo)
		delete m_pBitmapInfo;

	if (nullptr != m_hBitmap)
		DeleteObject(m_hBitmap);
}

bool CResourceMgr::Init()
{
	//UINT pX, pY;
	UINT iX, iY;
	UINT index = 0;
	for (iY = 0; iY < 4; ++iY)
	{
		for (iX = 0; iX < 4; ++iX)
		{
			m_cArrSprites[index]
				= CSprite(
					POINT{ (int)iX * READ_SIZE + 10, (int)iY * READ_SIZE + 12 }
					, READ_SIZE
					, index
					, 0x0000); // UP, DOWN, LEFT, RIGHT
			index++;
		}
	}

	/*
	0 -> 0x1111
	1 -> 0x0111
	2 -> 0x1110
	3 -> 0x0110

	4 -> 0x1011
	5 -> 0x0011
	6 -> 0x1010
	7 -> 0x0010

	8 -> 0x1101
	9 -> 0x0101
	10-> 0x1100
	11-> 0x0100

	12-> 0x1001
	13-> 0x0001
	14-> 0x1000
	15-> 0x0000
	*/

	CSprite spArrTemp[16] = {};
	spArrTemp[0] = m_cArrSprites[15];
	spArrTemp[1] = m_cArrSprites[13];
	spArrTemp[2] = m_cArrSprites[7];
	spArrTemp[3] = m_cArrSprites[5];
	spArrTemp[4] = m_cArrSprites[11];
	spArrTemp[5] = m_cArrSprites[9];
	spArrTemp[6] = m_cArrSprites[3];
	spArrTemp[7] = m_cArrSprites[1];
	spArrTemp[8] = m_cArrSprites[14];
	spArrTemp[9] = m_cArrSprites[12];
	spArrTemp[10] = m_cArrSprites[6];
	spArrTemp[11] = m_cArrSprites[4];
	spArrTemp[12] = m_cArrSprites[10];
	spArrTemp[13] = m_cArrSprites[8];
	spArrTemp[14] = m_cArrSprites[2];
	spArrTemp[15] = m_cArrSprites[0];
	for (int i = 0; i < 16; ++i)
	{
		m_cArrSprites[i] = spArrTemp[i];
	}

	//for (iY = 0; iY < 4; ++iY)
	//{
	//	for (iX = 0; iX < 4; ++iX)
	//	{
	//		static UINT ID_GENERATOR = 0;

	//		m_cArrSprites[index]
	//			= CSprite(
	//				POINT{ (int)iX * READ_SIZE + 8, (int)iY * READ_SIZE + 8 }
	//				, READ_SIZE
	//				, ID_GENERATOR++
	//				, 0x0000); // UP, DOWN, LEFT, RIGHT

	//		index++;
	//	}
	//}

	return false;
}

void CResourceMgr::Load(HDC _hDC, const WCHAR* _filename)
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

void CResourceMgr::Destroy()
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