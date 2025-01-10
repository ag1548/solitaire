#pragma once

#include <vector>

#include "deck.h"
#include "card.h"

class Board
{
public:
    explicit Board();

    void PromoteToFoundation(std::vector<Card>);

    void PrintBoard() const;
private:
    Deck deck;

    std::vector<Card> drawPile;
    std::vector<Card> discardPile;
    
    std::vector<Card>& GetFoundation(const Card&);
    std::vector<Card> foundation_S;
    std::vector<Card> foundation_C;
    std::vector<Card> foundation_D;
    std::vector<Card> foundation_H;

    std::vector<Card> boardStack_0;
    std::vector<Card> boardStack_1;
    std::vector<Card> boardStack_2;
    std::vector<Card> boardStack_3;
    std::vector<Card> boardStack_4;
    std::vector<Card> boardStack_5;
    std::vector<Card> boardStack_6;
};