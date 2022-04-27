#include <Windows.h>

#include "CGame.h"
//#include "CApp.h"
#include "CInputProc.h"

CGame* CGame::m_game = nullptr;

CGame::CGame()
	: m_bitmap{}
{}

CGame::~CGame()
{}

void CGame::ReleaseInst()
{
	if (nullptr != m_game)
		delete m_game;
}

bool CGame::Init()
{
	m_bitmap.Init();

	return false;
}

void CGame::Update()
{

}

void CGame::Render(HDC _memDC, POINT _pResolution)
{
	// Draw Axis
	UINT delta = 70; // padding 5¾¿
	for (UINT i = 0; i < 10; ++i)
	{
		MoveToEx(_memDC, i * delta, 0, NULL);
		LineTo(_memDC, i * delta, _pResolution.y);
	}
	for (UINT i = 0; i < 10; ++i)
	{
		MoveToEx(_memDC, 0, i * delta, NULL);
		LineTo(_memDC, _pResolution.x, i * delta);
	}

	
	// Bitmap Render
	m_bitmap.Render(_memDC);


	// Click Test (Mouse UP)
	if (true == CInputProc::GetInst()->IsMouseUp())
	{
		POINT pPos = CInputProc::GetInst()->GetMousePos();
		Rectangle(_memDC, pPos.x, pPos.y, pPos.x + 100, pPos.y + 100);
	}
}
