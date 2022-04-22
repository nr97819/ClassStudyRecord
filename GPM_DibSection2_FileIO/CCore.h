#pragma once

#include <windows.h>
#include <stdexcept>
#include <stdlib.h>

#include <string.h>
#include <wchar.h>

#include <time.h>

#define WIDTH	1000
#define HEIGHT	1000

class CCore
{
private:
	static CCore*		m_core;
	//===================================
	WCHAR				szWindowClass[50];
	WCHAR				szTitle[50];
	//===================================
	HINSTANCE			hInst;
	BITMAPINFO			bmpInfo;
	BITMAPINFO*			pBitmapInfo;
	LPDWORD				lpPixel;
	//===================================
	HDC					m_hDC;
	HDC					m_hMemDC;
	//===================================
	HBITMAP				hBitmap24;
	HBITMAP				hBitmap32;
	BITMAP				bitmap;
	//===================================
	LPDWORD				lpDIBits;
	LPDWORD				lpDIBits32;
	//===================================
	LPBYTE				lpResultTemp;
	int					tempReadSize;

public:
	CCore();
	~CCore();

	static CCore* GetInst()
	{
		if (nullptr == m_core)
			m_core = new CCore();

		return m_core;
	}
	bool Init(HINSTANCE hInstance, int nCmdShow);

	void Progress(_Out_ MSG& msg);
	void Play();

	void ReleaseInst();

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK MyProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void Convert_24to32()
	{
		int cnt = 0;
		LPBYTE lpByteTemp = (LPBYTE)lpDIBits;
		LPBYTE lpByteTemp32 = (LPBYTE)lpDIBits32;
		for (int i = 0; i < tempReadSize; ++i)
		{
			if ((i + 1) % 3 == 0)
			{
				lpByteTemp32[cnt++] = lpByteTemp[i];
				lpByteTemp32[cnt++] = 0xff;
			}
			else
			{
				lpByteTemp32[cnt++] = lpByteTemp[i];
			}
		}
	}

	void Do_24(HANDLE _file, BITMAPINFO* _bitmapInfo, DWORD& _readBytes)
	{
		hBitmap24 = CreateDIBSection(m_hDC, _bitmapInfo, DIB_RGB_COLORS, (void**)&lpDIBits, NULL, 0);   // 24 bit dib 

		if (false == ReadFile(_file, lpDIBits, _bitmapInfo->bmiHeader.biSizeImage, &_readBytes, NULL))
			throw std::runtime_error("File Error");

		tempReadSize = _readBytes;

		m_hMemDC = CreateCompatibleDC(m_hDC);
		SelectObject(m_hMemDC, hBitmap24);
	}

	void Do_32(HANDLE _file, BITMAPINFO* _bitmapInfo, DWORD& _readBytes)
	{
		hBitmap24 = CreateDIBSection(m_hDC, _bitmapInfo, DIB_RGB_COLORS, (void**)&lpDIBits, NULL, 0);   // 24 bit dib 

		/*GetObject(hBitmap24, sizeof(BITMAP), &bitmap);
		bitmap.bmWidthBytes = bitmap.bmWidth * 3;*/

		if (false == ReadFile(_file, lpDIBits, _bitmapInfo->bmiHeader.biSizeImage, &_readBytes, NULL))
			throw std::runtime_error("File Error");

		tempReadSize = _readBytes;

		m_hMemDC = CreateCompatibleDC(m_hDC);
		SelectObject(m_hMemDC, hBitmap24);

		_bitmapInfo->bmiHeader.biBitCount = 32;
		hBitmap32 = CreateDIBSection(m_hDC, _bitmapInfo, DIB_RGB_COLORS, (void**)&lpDIBits32, NULL, 0);   // 32 bit dib  width * height * 4  memory -> ARGB를 기억하고자 하는 메모리

		Convert_24to32();

		SelectObject(m_hMemDC, hBitmap32);
	}

	void InputBitmapFile(HWND _hWnd, const WCHAR* _filename)
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
		pBitmapInfo = (BITMAPINFO*) new BYTE[iBitmapInfoSize]; // 메모리 해제 필요
		if (false == ReadFile(hFile, (LPVOID)pBitmapInfo, iBitmapInfoSize, &dwReadBytes, NULL))
			throw std::runtime_error("File Error");

		// ==============================================
		Do_24(hFile, pBitmapInfo, dwReadBytes);
		// ==============================================

		if (hFile)
			CloseHandle(hFile);
	}
};

