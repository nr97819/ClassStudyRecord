#include "ToolView.h"

LRESULT CToolView::WndMsgProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	int width = 0;
	int height = 0;

	switch (_message)
	{
	case WM_CREATE:
		break;

	case WM_PAINT:
		hdc = BeginPaint(_hWnd, &ps);
		EndPaint(_hWnd, &ps);
		break;

	case WM_LBUTTONDOWN:
	{
		// D2D1
		Update();
		Render();
	}
	break;

	case WM_MOUSEMOVE:
	{
		WORD x = LOWORD(_lParam);
		WORD y = HIWORD(_lParam);
		wchar_t str[100];

		hdc = GetDC(_hWnd);

		// 마우스 위치의 pixel값 스포이드
		//COLORREF color = GetPixel(hdc, x, y);
		UINT width = m_pMyBitmap->GetD2DBitmap()->GetSize().width;
		UINT height = m_pMyBitmap->GetD2DBitmap()->GetSize().height;

		DWORD hex_color = m_pMyWICBitmap->GetPixelColor(x, y, width, height);
		//hex_color = 0x12345678;
		BYTE a_value = (hex_color & 0xff000000) >> (8 * 3);
		BYTE r_value = (hex_color & 0x00ff0000) >> (8 * 2);
		BYTE g_value = (hex_color & 0x0000ff00) >> (8 * 1);
		BYTE b_value = (hex_color & 0x000000ff) >> (8 * 0);
		hex_color = (hex_color | b_value) << (8);
		hex_color = (hex_color | g_value) << (8);
		hex_color = (hex_color | r_value) << (8);
		hex_color = (hex_color | a_value);

		wsprintf(str, L"(%.3d, %.3d) COLOR : %.8x", x, y, hex_color);
		TextOut(hdc, 10, 10, str, wcslen(str));

		HPEN hNewPen = CreatePen(PS_SOLID, 1, RGB(0xff, 0xff, 0xff));
		HPEN hOldPen = (HPEN)SelectObject(hdc, hNewPen);

		HBRUSH hNewBrush = CreateSolidBrush(RGB(r_value, g_value, b_value));
		HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hNewBrush);

		POINT rtSize = { 50, 50 };
		Rectangle(hdc, 900, 20, 900 + rtSize.x, 20 + rtSize.y);

		SelectObject(hdc, hOldPen);
		SelectObject(hdc, hOldBrush);

		DeleteObject(hNewPen);
		DeleteObject(hNewBrush);

		ReleaseDC(_hWnd, hdc);
	}
	break;

	case WM_SIZE:
	{
		width = LOWORD(_lParam);
		height = HIWORD(_lParam);

		if (m_pRenderTarget)
			m_pRenderTarget->Resize({ (UINT32)width, (UINT32)height });
	}
	break;

	case WM_COMMAND:
		switch (LOWORD(_wParam))
		{
		case ID_FILE_LOAD:
		{
			WCHAR wsFileName[32] = {};
			OPENFILENAME ofn; // = {};
			memset(&ofn, 0, sizeof(OPENFILENAME));
			ofn.lStructSize = sizeof(OPENFILENAME);
			ofn.hwndOwner = m_hWnd;
			ofn.lpstrFilter = L"All Files(*.*)\0*.*\0";
			ofn.lpstrFile = wsFileName;
			ofn.nMaxFile = sizeof(wsFileName);;
			GetOpenFileName(&ofn);

			if ('\0' != wsFileName[0])
				MessageBox(m_hWnd, L"Successfully Load File", L"Load File", MB_OK);
		}
		break;

		case ID_FILE_SAVE:
		{
			MessageBox(m_hWnd, L"File Save", L"File Save Event", MB_OKCANCEL);
		}
		break;
		/*case ID_FILE_MENU2:
			MessageBox(m_hWnd, L"MENU1", L"TEST MENU1", MB_OK);
			break;
		case ID_FILE_EXIT:
			PostQuitMessage(0);
			break;
		*/
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(_hWnd, _message, _wParam, _lParam);
		break;
	}
	return 0;
}