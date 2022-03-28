#pragma once

#include "E_PlayerColor.h"

#include "Player.h"

class CGame
{
private:
	CPlayer* m_player1;
	CPlayer* m_player2;

public:
	CGame() : m_player1(nullptr), m_player2(nullptr)
	{
		// ERROR !!!!!!!!
		const wchar_t* p1_name = L"Black";
		const wchar_t* p2_name = L"White";
		m_player1 = new CPlayer(p1_name, PC_Black);
		m_player2 = new CPlayer(p2_name, PC_White);
	}

	~CGame()
	{
		delete m_player1;
		delete m_player2;
	}
};

