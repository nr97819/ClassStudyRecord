#pragma once

#include "E_PlayerColor.h"

#include <string.h>
#include <wchar.h>

class CPlayer
{
private:
	wchar_t* m_name;
	int m_color; // 1. 검정, 2. 하양

public:
	CPlayer() : m_name{}, m_color(1)
	{
		m_name = new wchar_t[20];
		wmemset(m_name, L'\0', 20);
	}
	
	CPlayer(const wchar_t* _name, int _color) : m_color(_color)
	{
		m_name = new wchar_t[20];
		//wcscpy_s(m_name, wcslen(_name), _name);
		wcscpy_s(m_name, 20, _name);
	}

	~CPlayer()
	{
		delete[] m_name;
	}
};

