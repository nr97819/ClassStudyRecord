#pragma once

#include <Windows.h>

class CSprite
{
private:
	POINT			pFramePos;

	UINT			uId;
	WORD			wDir;

public:
	CSprite();
	CSprite(POINT _framePos, UINT _frameSize, UINT _uId, WORD _wDir);
	~CSprite();

public:
	POINT GetFramePos() { return pFramePos; }
	WORD GetDir() { return wDir; }
	UINT GetID() { return uId; }
};

