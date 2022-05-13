#pragma once

#include <Windows.h>

#include <d2d1.h>
#include <dwrite.h>
#include <wincodec.h>

class CD2DCore
{
private:
	ID2D1Factory* m_pD2DFactory;
	IDWriteFactory* m_pDWriteFactory;
	IWICImagingFactory* m_pWICFactory;

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
	HRESULT Init();

public:
	ID2D1Factory** GetD2D1Factory() { return &m_pD2DFactory; }
	IDWriteFactory** GetDWriteFactory() { return &m_pDWriteFactory; }
	IWICImagingFactory** GetWICImagingFactory() { return &m_pWICFactory; }
};

