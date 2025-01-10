#include <algorithm>

#include "deck.h"

Deck::Deck() {
  rng = std::default_random_engine {};

  cards.reserve(52);
  std::for_each(Suits.begin(), Suits.end(), [&](char s) {
    std::for_each(Faces.begin(), Faces.end(), [&](char f) {
        cards.emplace_back(s, f);
    });
  });
}

void Deck::Shuffle() {
    std::ranges::shuffle(cards, rng);
}

void Deck::PrintDeck() const {
    int index = 0;
    std::for_each(cards.begin(), cards.end(), [&](const Card& c){
        std::cout << "[" << index++ << "]: " << c << std::endl;
    });
}
