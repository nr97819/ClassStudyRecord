#pragma once

#include <Windows.h>
#include "E_PlayerColor.h"
#include "Game.h"

class CApp
{
private:
	WCHAR m_szWindowClass[50] = L"DesktopApp";
	WCHAR m_szTitle[50] = L"Windows Desktop Guided Tour Application";

	static CApp* m_app;
	CGame* m_game;

	bool m_bBlackTurn;

	HBRUSH m_whiteBrush;
	HBRUSH m_blackBrush;
	HBRUSH m_greenBrush;

public:
	CApp();
	~CApp();

	bool Initialize(HINSTANCE hInstance, int nCmdShow);
	MSG RunLoop();

	static void CreateMyApp();
	static void DeleteMyApp();
	void OnRender(HDC hdc);
	
	LRESULT static CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK MyProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	bool ConvertPosToBlock(long _beforePos, int& _afterBlock);
	void DrawCircleAtBlock(HDC _hdc, HBRUSH _brush, int _yValue, int _xValue, int _delta);
};

//extern CApp g_App;
