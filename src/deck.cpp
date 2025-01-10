#include <algorithm>

#include "deck.h"

Deck::Deck() {
  cards.reserve(52);
  std::for_each(Suits.begin(), Suits.end(), [&](char s) {
    std::for_each(Faces.begin(), Faces.end(), [&](char f) {
        cards.emplace_back(s, f);
    });
  });
}

void Deck::PrintDeck() {
    int index = 0;
    std::for_each(cards.begin(), cards.end(), [&](Card c){
        std::cout << "[" << index++ << "]: " << c << std::endl;
    });
}
