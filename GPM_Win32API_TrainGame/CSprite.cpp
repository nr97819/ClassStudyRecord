#include "CSprite.h"

CSprite::CSprite()
	: pFramePos{}
	, uId(0)
	, wDir(0x0000)
{}

CSprite::CSprite(POINT _framePos, UINT _frameSize, UINT _uId, WORD _wDir)
	: pFramePos{ _framePos }
	, uId(_uId)
	, wDir(_wDir)
{}

CSprite::~CSprite()
{}
