#include "CAnimation.h"

#include <d2d1.h>
//#include <wincodec.h>
//#include <dwrite.h>
#pragma comment(lib, "d2d1.lib")
//#pragma comment(lib, "dwrite.lib")
//#pragma comment(lib, "windowscodecs.lib")

CAnimation::CAnimation()
	: m_bitmap(nullptr)
	, m_iMaxClip(0)
	, m_iActiveClip(0)
	, m_dInterval(0.)
	, m_dTimeAcc(0.)
	, m_pClipBuffer(nullptr)
	, m_fStartX(0.f)
	, m_fStartY(0.f)
{

}

CAnimation::~CAnimation()
{

}
