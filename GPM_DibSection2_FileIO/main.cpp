
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

#include <time.h>
#include <wchar.h>
#include <stdexcept>

static TCHAR szWindowClass[] = _T("DesktopApp");
static TCHAR szTitle[] = _T("Windows Desktop Guided Tour Application");

#define WIDTH	1000
#define HEIGHT	1000
HINSTANCE		hInst;
BITMAPINFO		bmpInfo;
LPDWORD			lpPixel;
HBITMAP			hBitmap;
HDC				hMemDC;

LPDWORD			lpDIBits;
LPBYTE			lpResultTemp;
int				tempReadSize;

void Convert_24to32()
{
	lpResultTemp = new BYTE[(tempReadSize / 3) * 4];

	int cnt = 0;
	LPBYTE lpByteTemp = (LPBYTE)lpDIBits;
	for (int i = 0; i < tempReadSize; i++)
	{
		if ((i + 1) % 3 == 0)
		{
			lpResultTemp[cnt++] = lpByteTemp[i];
			lpResultTemp[cnt++] = 0xff;
		}
		else
		{
			lpResultTemp[cnt++] = lpByteTemp[i];
		}
	}
}

void InputBitmapFile(HWND _hWnd, const WCHAR* _filename)
{
	HANDLE hFile;
	hFile = CreateFile(_filename, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		throw std::runtime_error("File Error");

	BITMAPFILEHEADER bmFileHeader;
	DWORD dwReadBytes;
	if (false == ReadFile(hFile, &bmFileHeader, sizeof(BITMAPFILEHEADER), &dwReadBytes, NULL))
		throw std::runtime_error("File Error");

	int iBitmapInfoSize = bmFileHeader.bfOffBits - sizeof(BITMAPFILEHEADER);
	BITMAPINFO* pBitmapInfo = (BITMAPINFO*) new BYTE[iBitmapInfoSize];
	if (false == ReadFile(hFile, (LPVOID)pBitmapInfo, iBitmapInfoSize, &dwReadBytes, NULL))
		throw std::runtime_error("File Error");

	pBitmapInfo->bmiHeader.biBitCount = 32;
	//pBitmapInfo->bmiHeader = bmpInfo.bmiHeader;
	//pBitmapInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	//pBitmapInfo->bmiHeader.biWidth = WIDTH;
	//pBitmapInfo->bmiHeader.biHeight = HEIGHT;
	//pBitmapInfo->bmiHeader.biPlanes = 1;
	//pBitmapInfo->bmiHeader.biCompression = BI_RGB;

	HDC hdc = GetDC(_hWnd);
	hBitmap = CreateDIBSection(hdc, pBitmapInfo, DIB_RGB_COLORS, (void**)&lpDIBits, NULL, 0);
	hMemDC = CreateCompatibleDC(hdc);
	SelectObject(hMemDC, hBitmap);
	if (false == ReadFile(hFile, lpDIBits, pBitmapInfo->bmiHeader.biSizeImage, &dwReadBytes, NULL))
		throw std::runtime_error("File Error");

	tempReadSize = dwReadBytes;
	Convert_24to32();
	
	ReleaseDC(_hWnd, hdc);
	if (hFile)
		CloseHandle(hFile);
}

void DestroyDib()
{
	DeleteDC(hMemDC);
	DeleteObject(hBitmap);
}

void Play()
{

}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow
)
{
	srand((unsigned int(time(NULL))));
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Windows Desktop Guided Tour"),
			NULL);

		return 1;
	}

	hInst = hInstance;

	HWND hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		700, 500,
		NULL,
		NULL,
		hInstance,
		NULL);

	if (!hWnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("Windows Desktop Guided Tour"),
			NULL);

		return 1;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Play();
		}
	}

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_CREATE:
		SetTimer(hWnd, 1, 1, NULL);
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		BitBlt(hdc, 0, 0, WIDTH, HEIGHT, hMemDC, 0, 0, SRCCOPY);
		EndPaint(hWnd, &ps);
		break;

	case WM_MBUTTONDOWN:
		InputBitmapFile(hWnd, L"sample.bmp");
		//InputBitmapFile(hWnd, L"bigImage.bmp");

		InvalidateRgn(hWnd, NULL, false);
		break;

	case WM_LBUTTONDOWN:
		break;

	case WM_RBUTTONDOWN:
	{
		LPDWORD lpDwBuffer = (LPDWORD)lpResultTemp;
		for (int i = 0; i < tempReadSize / 4; i++)
		{
			lpDIBits[i] = lpDwBuffer[i];
		}

		InvalidateRgn(hWnd, NULL, false);
	}
		break;

	case WM_DESTROY:
		//KillTimer(hWnd, 1);
		DestroyDib();
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
	return 0;
}