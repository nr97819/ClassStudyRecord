#include "CSprite.h"

CSprite::CSprite()
	: pFramePos{}
	, iFrameSize(70)
{}

CSprite::CSprite(POINT _framePos, UINT _frameSize)
	: pFramePos{ _framePos }
	, iFrameSize(_frameSize)
{}

CSprite::~CSprite()
{}
