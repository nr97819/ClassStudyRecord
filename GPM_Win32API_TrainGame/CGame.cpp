#include <Windows.h>

#include "CGame.h"
//#include "CApp.h"
#include "CInputMgr.h"
#include "CResourceMgr.h"

CGame* CGame::m_game = nullptr;

CGame::CGame()
{}

CGame::~CGame()
{}

void CGame::ReleaseInst()
{
	if (nullptr != m_game)
		delete m_game;
}

bool CGame::Init(HDC _hDC)
{
	// Bitmap
	CResourceMgr::GetInst()->Init();
	CResourceMgr::GetInst()->Load(_hDC, L"Road.bmp");
	CInputMgr::GetInst()->Init();

	return false;
}

void CGame::Update()
{
	// Mouse UP
	if (true == CInputMgr::GetInst()->IsMouseUp())
	{
		POINT pPos = CInputMgr::GetInst()->GetMousePos();
		//Rectangle(_memDC, pPos.x, pPos.y, pPos.x + 100, pPos.y + 100);

		POINT pDotPos{};
		pDotPos.x = (int)(pPos.x / 64.f);
		pDotPos.y = (int)(pPos.y / 64.f);
		int index = pDotPos.y * 10 + pDotPos.x;

		m_tilemap.AddRail(index);
	}
}

void CGame::Render(HDC _memDC, POINT _pResolution)
{
	// Draw Axis
	for (UINT i = 0; i < 10; ++i)
	{
		MoveToEx(_memDC, i * FRAME_SIZE, 0, NULL);
		LineTo(_memDC, i * FRAME_SIZE, 640);
	}
	for (UINT i = 0; i < 10; ++i)
	{
		MoveToEx(_memDC, 0, i * FRAME_SIZE, NULL);
		LineTo(_memDC, 640, i * FRAME_SIZE);
	}


	// Bitmap Render
	m_tilemap.Render(_memDC);


	// Draw Axis Overlapped
	HPEN hPen = CreatePen(PS_DOT, 1, RGB(0, 255, 0));
	HPEN hOldPen = (HPEN)SelectObject(_memDC, hPen);
	for (UINT i = 0; i < 10; ++i)
	{
		MoveToEx(_memDC, i * FRAME_SIZE, 0, NULL);
		LineTo(_memDC, i * FRAME_SIZE, 640);
	}
	for (UINT i = 0; i < 10; ++i)
	{
		MoveToEx(_memDC, 0, i * FRAME_SIZE, NULL);
		LineTo(_memDC, 640, i * FRAME_SIZE);
	}
	SelectObject(_memDC, hOldPen);
	DeleteObject(hPen);

	// bitmap을 render하는건 진짜 bitmap이미지를 렌더할때
}
