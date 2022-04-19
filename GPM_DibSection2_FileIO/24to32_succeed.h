
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

#include <time.h>
#include <wchar.h>
#include <stdexcept>

static TCHAR szWindowClass[] = _T("DesktopApp");
static TCHAR szTitle[] = _T("Windows Desktop Guided Tour Application");

// DibSection [1] - Noise Print
HINSTANCE hInst;
#define WIDTH	1000
#define HEIGHT	1000
BITMAPINFO		bmpInfo;
LPDWORD			lpPixel;
HBITMAP			hBitmap;
HDC				hMemDC;

// 추가한 코드
LPDWORD			lpDIBits;
BYTE*			lpResultTemp;		// (@) 계속 작업하는 코드	!!!
int				tempReadSize;
//LPDWORD lpdwDIBits;

// DibSection [2] - File I/O
void InputBitmapFile(HWND _hWnd, const WCHAR* _filename)
{
	HANDLE hFile;
	hFile = CreateFile(_filename, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
/*
	HANDLE WINAPI CreateFileW(
		_In_ LPCWSTR lpFileName,
		_In_ DWORD dwDesiredAccess,
		_In_ DWORD dwShareMode,
		_In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes,
		_In_ DWORD dwCreationDisposition,
		_In_ DWORD dwFlagsAndAttributes,
		_In_opt_ HANDLE hTemplateFile
	);	
*/
	if (hFile == INVALID_HANDLE_VALUE)
		throw std::runtime_error("File Load Error");

	BITMAPFILEHEADER bmFileHeader;
	DWORD dwReadBytes;
/*
	typedef struct tagBITMAPFILEHEADER {
		WORD    bfType;
		DWORD   bfSize;
		WORD    bfReserved1;
		WORD    bfReserved2;
		DWORD   bfOffBits;
	} BITMAPFILEHEADER, FAR* LPBITMAPFILEHEADER, * PBITMAPFILEHEADER;
*/
	// 1. BITMAPFILEHEADER 구조체 만큼 파일에서 읽어서 bmFileHeader로 넣는다.
	if(false == ReadFile(hFile, &bmFileHeader, sizeof(BITMAPFILEHEADER), &dwReadBytes, NULL))
		throw std::runtime_error("File Load Error");
/*
	BOOL WINAPI ReadFile(
		_In_ HANDLE hFile,
		_Out_writes_bytes_to_opt_(nNumberOfBytesToRead, *lpNumberOfBytesRead) __out_data_source(FILE) LPVOID lpBuffer,
		_In_ DWORD nNumberOfBytesToRead,
		_Out_opt_ LPDWORD lpNumberOfBytesRead,
		_Inout_opt_ LPOVERLAPPED lpOverlapped
	);
*/
	// 2. DIB에 사용할 BITMAPINFO 구조체를 파일에서 읽어서 pBitmapInfo에 넣는다.
	// BITMAPINFO는 BITMAPINFOHEADER + RGBQUAD의 구조체
	int iBitmapInfoSize = bmFileHeader.bfOffBits - sizeof(BITMAPFILEHEADER);
	BITMAPINFO* pBitmapInfo = (BITMAPINFO*) new BYTE[iBitmapInfoSize];
/*
	typedef struct tagBITMAPINFO {
		BITMAPINFOHEADER    bmiHeader;
		RGBQUAD             bmiColors[1];
	} BITMAPINFO, FAR* LPBITMAPINFO, * PBITMAPINFO;
*/
/*
	typedef struct tagBITMAPINFOHEADER{
        DWORD      biSize;
        LONG       biWidth;
        LONG       biHeight;
        WORD       biPlanes;
        WORD       biBitCount;
        DWORD      biCompression;
        DWORD      biSizeImage;
        LONG       biXPelsPerMeter;
        LONG       biYPelsPerMeter;
        DWORD      biClrUsed;
        DWORD      biClrImportant;
	} BITMAPINFOHEADER, FAR *LPBITMAPINFOHEADER, *PBITMAPINFOHEADER;
*/
	if(false == ReadFile(hFile, (LPVOID)pBitmapInfo, iBitmapInfoSize, &dwReadBytes, NULL))
		throw std::runtime_error("File Load Error");

	// 3. Pixel Data를 받기 위한 메모리를 만들고 File에서 Pixel Data를 받아서 DIB에 복사한다.
	HDC hdc = GetDC(_hWnd);


	// ========== [*] 추가된 코드 ==========
	pBitmapInfo->bmiHeader.biBitCount = 32;
	//pBitmapInfo->bmiHeader = bmpInfo.bmiHeader;
	pBitmapInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	//pBitmapInfo->bmiHeader.biWidth = WIDTH;
	//pBitmapInfo->bmiHeader.biHeight = HEIGHT;
	pBitmapInfo->bmiHeader.biPlanes = 1;
	pBitmapInfo->bmiHeader.biCompression = BI_RGB; // BI_BITFIELDS
	// ====================================


	//HBITMAP hBitmap = CreateDIBSection(hdc, pBitmapInfo, DIB_RGB_COLORS, &lpDIBits, NULL, 0);
	hBitmap = CreateDIBSection(hdc, pBitmapInfo, DIB_RGB_COLORS, (void**)&lpDIBits, NULL, 0);
	hMemDC = CreateCompatibleDC(hdc);
	if(false == ReadFile(hFile, lpDIBits, pBitmapInfo->bmiHeader.biSizeImage, &dwReadBytes, NULL))
		throw std::runtime_error("File Load Error");

	// ========== [*] 추가된 코드 ==========
	tempReadSize = dwReadBytes;
	lpResultTemp = new BYTE[(dwReadBytes / 3) * 4];
	//LPDWORD lpDwTemp = new DWORD[dwReadBytes];

	LPBYTE lpByteTemp = (LPBYTE)lpDIBits;

	int _24BytesCnt = 0;
	int _32BytesCnt = 0;

	int cnt = 0;
	int cycleCnt = 1;
	for (int i = 0; i < dwReadBytes; i++)
	{
		_24BytesCnt++;

		if (cycleCnt == 3)
		{
			lpResultTemp[cnt++] = lpByteTemp[i];
			lpResultTemp[cnt++] = 0xff;
			cycleCnt = 0;
		}
		else
		{
			lpResultTemp[cnt++] = lpByteTemp[i];
		}
		cycleCnt++;
	}

	SelectObject(hMemDC, hBitmap);
	ReleaseDC(_hWnd, hdc);
	// 4. 반드시 파일을 열었으면 꼭 닫는다. (메모리 누수 주의)
	if (hFile)
		CloseHandle(hFile);
}

int InputFile(HWND _hWnd, const WCHAR* _filename)
{
	HDC hdc;
	HANDLE hFile;
	hdc = GetDC(_hWnd);
	hFile = CreateFile(_filename, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(_hWnd, TEXT("파일을 열 수 없습니다."), TEXT("에러"), MB_OK);
		//throw std::runtime_error("File Load Error");
		return -1;
	}
	MessageBox(_hWnd, TEXT("파일을 성공적으로 열었습니다."), TEXT("성공"), MB_OK);
	CloseHandle(hFile);
	ReleaseDC(_hWnd, hdc);
	return 0;
}

void OutputBitmapFile(HWND _hWnd)
{
	HDC hdc = GetDC(_hWnd);
	hMemDC = CreateCompatibleDC(hdc);
	hBitmap = CreateCompatibleBitmap(hdc, 0, 0);
	SelectObject(hMemDC, hBitmap);
	ReleaseDC(_hWnd, hdc);
}

void SetNewDib(HWND _hWnd)
{
	/*bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmpInfo.bmiHeader.biWidth = WIDTH;
	bmpInfo.bmiHeader.biHeight = HEIGHT;

	bmpInfo.bmiHeader.biPlanes = 1;
	bmpInfo.bmiHeader.biBitCount = 24;
	bmpInfo.bmiHeader.biCompression = BI_RGB;

	HDC hdc = GetDC(_hWnd);
	hBitmap = CreateDIBSection(hdc, &bmpInfo, DIB_RGB_COLORS, (void**)&lpPixel, NULL, 0);
	hMemDC = CreateCompatibleDC(hdc);
	SelectObject(hMemDC, hBitmap);
	ReleaseDC(_hWnd, hdc);*/
}

void SetDib(HWND _hWnd)
{
	bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmpInfo.bmiHeader.biWidth = WIDTH;
	bmpInfo.bmiHeader.biHeight = HEIGHT;

	bmpInfo.bmiHeader.biPlanes = 1;
	bmpInfo.bmiHeader.biBitCount = 32;
	bmpInfo.bmiHeader.biCompression = BI_RGB;

	HDC hdc = GetDC(_hWnd);
	hBitmap = CreateDIBSection(hdc, &bmpInfo, DIB_RGB_COLORS, (void**)&lpPixel, NULL, 0);
	hMemDC = CreateCompatibleDC(hdc);
	SelectObject(hMemDC, hBitmap);
	ReleaseDC(_hWnd, hdc);
}

void DestroyDib()
{
	DeleteDC(hMemDC);
	DeleteObject(hBitmap);
}

void DrawDib(int _pX, int _pY)
{
	for (int y = HEIGHT - 10; y > 300; y--)
	{
		for (int x = 0; x < 700; x++)
		{			                  // A R G B
			lpPixel[(y * WIDTH) + x] = 0xff00ff00;
		}
	}
}

void SetPixel(int _pX, int _pY, DWORD _color)
{
	_pY = HEIGHT - _pY;
	lpPixel[(_pY * WIDTH) + _pX] = _color;
	//lpdwDIBits[(_pY * WIDTH) + _pX] = _color;
}

void Play()
{

}

void DrawNoisePattern()
{
	int r, g, b;
	int color = 0;

	for (int y = HEIGHT - 1; y > 0; y--)
	{
		for (int x = 0; x < 800; x++)
		{
			color = 0xff000000;

			r = rand() % 256; // 2^8 = 1111 1111 b = 0xFF
			g = rand() % 256;
			b = rand() % 256;

			color |= r << 16;
			color |= g << 8;
			color |= b;

			lpPixel[(y * WIDTH) + x] = color;
		}
	}
}

void ClearScreen()
{
	for (int y = HEIGHT - 1; y > 0; y--)
	{
		for (int x = 0; x < WIDTH; x++)
		{			                  // A R G B
			lpPixel[(y * WIDTH) + x] = 0xff000000;
		}
	}
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
		1000, 1000,
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

	static int nowX = 0, nowY = 0;
	static bool bLBtnDown = false;

	switch (message)
	{
	case WM_CREATE:
		SetTimer(hWnd, 1, 1, NULL);
		SetNewDib(hWnd);
		//SetDib(hWnd);
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// . . .
		EndPaint(hWnd, &ps);
		break;

	case WM_MOUSEMOVE:
		if (bLBtnDown)
		{
			nowX = LOWORD(lParam);
			nowY = HIWORD(lParam);

			//DrawDib(pX, pY);
			//SetPixel(nowX, nowY, 0xff00ff00);
			//InvalidateRgn(hWnd, NULL, TRUE);
		}
		break;

	case WM_MBUTTONDOWN:
		//InputBitmapFile(hWnd, L"C:\\__win32api_fileIO_\\SuperMario.bmp");
		InputBitmapFile(hWnd, L"sample.bmp");
		//InputFile(hWnd, L"C:\\__win32api_fileIO_\\test.txt");
		//OutputBitmapFile(hWnd);
		break;

	case WM_LBUTTONDOWN:
		bLBtnDown = true;
		break;

	case WM_LBUTTONUP:
		bLBtnDown = false;
		break;

	case WM_RBUTTONDOWN:
	{
		LPDWORD lpDwBuffer = (LPDWORD)lpResultTemp;
		for (int i = 0; i < tempReadSize / 4; i++) // bitColorTempSize
		{
			lpDIBits[i] = lpDwBuffer[i];//lpTemp2[i];
		}
	}
		//lpDIBits = (LPDWORD)lpTemp;
		break;

	case WM_TIMER:
		//DrawDib();
		hdc = GetDC(hWnd);
		//DrawNoisePattern();
		BitBlt(hdc, 0, 0, WIDTH, HEIGHT, hMemDC, 0, 0, SRCCOPY);
		ReleaseDC(hWnd, hdc);
		//InvalidateRgn(hWnd, NULL, TRUE);
		break;

	case WM_DESTROY:
		DestroyDib();
		//KillTimer(hWnd, 1);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
	return 0;
}