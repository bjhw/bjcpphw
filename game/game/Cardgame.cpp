#include "StdAfx.h"
#include "Cardgame.h"

Cardgame::Cardgame(int p)
{
    players = p;
    totalparticipants += p;
}

Cardgame::~Cardgame(void)
{
	totalparticipants -= players;
}
