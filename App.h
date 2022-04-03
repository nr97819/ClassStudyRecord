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

	HBRUSH m_greenBrush;

private:
	CApp();
	~CApp();

public:
	static CApp* GetInstance()
	{
		if (m_app == nullptr) m_app = new CApp();

		return m_app;
	}
	static void DeleteInstance()
	{
		if (m_app) {
			delete m_app;
			m_app = nullptr;
		}
	}

	bool Initialize(HINSTANCE hInstance, int nCmdShow);
	MSG RunLoop();

	//static void CreateMyApp();
	//static void DeleteMyApp();
	void OnRender(HDC hdc);
	
	LRESULT static CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK MyProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void DrawCircleAtBlock(HDC _hdc, HBRUSH _brush, int _yValue, int _xValue, int _delta);
	//bool ConvertPosToBlock(long _beforePos, int& _afterBlock);
};

//extern CApp g_App;
