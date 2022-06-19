#pragma once

#include "Wnd.h"

class CToolView : public CWnd
{
private:


public:
	virtual LRESULT WndMsgProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam) override;

};