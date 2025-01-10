#include <algorithm>
#include <iomanip>

#include "deck.h"

Deck::Deck() {
    cards.reserve(52);
    std::for_each(Suits.begin(), Suits.end(), [&](char s) {
        std::for_each(Faces.begin(), Faces.end(), [&](char f) {
            cards.emplace_back(s, f);
        });
    });
}

void Deck::Shuffle() {
    std::random_device rd;
    std::mt19937       gen{rd()};
    std::ranges::shuffle(cards, gen);
}

Card Deck::DrawCard() {
    Card result = cards.back();

    cards.pop_back();

    return result;
}

bool Deck::isEmpty() const {
    return cards.empty();
}

void Deck::PrintDeck() const {
    int index = 0;
    std::for_each(cards.begin(), cards.end(), [&](const Card &c) {
        std::cout << "[" << std::setw(2) << index++ << "]: " << c;

        if (index % 13 == 0) {
            std::cout << std::endl;
        } else if (index != cards.size()) {
            std::cout << ", ";
        }
    });

    if (index % 13 != 0) {
        std::cout << std::endl;
    }
}
