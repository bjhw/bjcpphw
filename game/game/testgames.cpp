//testgames.cpp
#include "Cardgame.h"
#include "stdafx.h"
int Cardgame::totalparticipants = 0;
int main()
{
    Cardgame *bridge = 0;
    Cardgame *blackjack = 0;
    Cardgame *solitaire = 0;
    Cardgame *poker = 0;

    try
    {
        bridge = new Cardgame(4);
        blackjack = new Cardgame(8);
        solitaire = new Cardgame(1);
        delete blackjack;
        delete bridge;
        poker = new Cardgame(5);
        delete solitaire;
        delete poker;
    }
    catch (...)
    {
        if (bridge) delete bridge;
        if (blackjack) delete blackjack;
        if (solitaire) delete solitaire;
        if (poker) delete poker;
    }

    return 0;
}