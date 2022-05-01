#include "CTileMap.h"

#include <Windows.h>

#include "CResourceMgr.h"

CTileMap::CTileMap()
	: iArrTilemap{}
{

}

CTileMap::~CTileMap()
{

}

void CTileMap::Render(HDC _memDC)
{
	CSprite* spArray = CResourceMgr::GetInst()->GetSprites();

	UINT index = 0;
	for (int ly = 0; ly < 10; ++ly)
	{
		for (int lx = 0; lx < 10; ++lx)
		{
			BitBlt(_memDC
				, lx * FRAME_SIZE
				, ly * FRAME_SIZE
				, FRAME_SIZE
				, FRAME_SIZE
				, CResourceMgr::GetInst()->GetBmpDC()
				, spArray[iArrTilemap[index]].GetFramePos().x
				, spArray[iArrTilemap[index]].GetFramePos().y
				, SRCCOPY);
			index++;
		}
	}
}

void CTileMap::AddRail(int _index)
{
	// All Print (for Test)
	/*for (int i = 0; i < 100; ++i)
	{
		m_iArrField[i] = (i % 16);
	}*/

	iArrTilemap[_index] = 0b0000;

	// ╩С
	if ((_index - 10 >= 0)
		&& (iArrTilemap[_index - 10] != 0))
	{
		iArrTilemap[_index - 10] |= 0b0100;
		iArrTilemap[_index] |= 0b1000;
	}

	// го
	if ((_index + 10 < 100)
		&& (iArrTilemap[_index + 10] != 0))
	{
		iArrTilemap[_index + 10] |= 0b1000;
		iArrTilemap[_index] |= 0b0100;
	}

	// аб
	if ((_index - 1 >= 0)
		&& (iArrTilemap[_index - 1] != 0))
	{
		iArrTilemap[_index - 1] |= 0b0001;
		iArrTilemap[_index] |= 0b0010;
	}

	// ©Л
	if ((_index + 1 < 100)
		&& (iArrTilemap[_index + 1] != 0))
	{
		iArrTilemap[_index + 1] |= 0b0010;
		iArrTilemap[_index] |= 0b0001;
	}

	// EXCEPT
	if (iArrTilemap[_index] == 0b0000)
		iArrTilemap[_index] = 0b1000;
}