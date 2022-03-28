#pragma once

#include <Windows.h>
#include "E_PlayerColor.h"

class CApp
{
private:
	WCHAR m_szWindowClass[50] = L"DesktopApp";
	WCHAR m_szTitle[50] = L"Windows Desktop Guided Tour Application";

private:
	int m_field[8][8];
	POINT m_pCurrentMousePos;
	POINT m_pCirclePos;
	POINT m_pCircleSize;
	bool m_bBlackTurn;

	HBRUSH m_whiteBrush;
	HBRUSH m_blackBrush;
	HBRUSH m_greenBrush;
	
	static CApp* m_app;

	// test
	int m_nowColor = PC_Black;

public:
	CApp();
	~CApp();

	bool Initialize(HINSTANCE hInstance, int nCmdShow);
	MSG RunLoop();

	static void CreateMyApp();
	static void DeleteMyApp();
	void OnRender(HDC hdc);
	
	bool ConvertPosToBlock(long &_beforePos, int &_afterBlock);

	LRESULT static CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK MyProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void DrawCircleAtBlock(HDC _hdc, HBRUSH _brush, int _yValue, int _xValue, int _delta);

	void FlipStones(POINT& _nowPos);
	// acrossXY, YX
	void FlipX(POINT& _nowPos);
	void FlipMinusX(POINT& _nowPos);
	void FlipY(POINT& _nowPos);
	void FlipMinusY(POINT& _nowPos);
};

//extern CApp g_App;
