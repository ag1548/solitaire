#include <algorithm>
#include <iomanip>

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

Card Deck::DrawCard()
{
    Card result = cards.back();

    cards.pop_back();

    return result;
}

void Deck::PrintDeck() const {
    int index = 0;
    std::for_each(cards.begin(), cards.end(), [&](const Card& c){
        std::cout << "[" << std::setw(2) << index++ << "]: " << c;

        // Print a new line after the 13th card
        if (index % 13 == 0)
            std::cout << std::endl;
        else
            // Only print the comma if we are not at the end of the line
            if (index != cards.size())
                std::cout << ", ";
    });

    // Remove the last comma that is printing
    if (index % 13 != 0)
        std::cout << std::endl;
}
