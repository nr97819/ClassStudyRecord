#pragma once

#include "Wnd.h"

class CImgView : public CWnd
{
private:


public:
	virtual LRESULT WndMsgProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam) override;

};

