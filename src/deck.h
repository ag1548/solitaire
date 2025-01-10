#pragma once

#include <vector>

#include "card.h"

class Deck {
public:
    Deck();

    void Shuffle();

    Card DrawCard();

    bool isEmpty() const;
    void PrintDeck() const;

private:
    std::vector<Card> cards;
};
