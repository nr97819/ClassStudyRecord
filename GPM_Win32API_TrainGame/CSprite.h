#pragma once

#include <Windows.h>

class CSprite
{
private:
	POINT			pFramePos;
	UINT			iFrameSize;

public:
	CSprite();
	CSprite(POINT _framePos, UINT _frameSize);
	~CSprite();

public:
	POINT GetFramePos() { return pFramePos; }
	UINT GetFrameSize() { return iFrameSize; }
};

