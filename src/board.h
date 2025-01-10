#pragma once

#include <stack>

#include "deck.h"

class Board
{
public:
    Board();

    void PrintBoard() const;
private:
    Deck deck;

    std::stack<Card> drawPile;
    std::stack<Card> discardPile;
    
    std::stack<Card> foundation_S;
    std::stack<Card> foundation_C;
    std::stack<Card> foundation_D;
    std::stack<Card> foundation_H;

    std::stack<Card> boardStack_0;
    std::stack<Card> boardStack_1;
    std::stack<Card> boardStack_2;
    std::stack<Card> boardStack_3;
    std::stack<Card> boardStack_4;
    std::stack<Card> boardStack_5;
    std::stack<Card> boardStack_6;
};