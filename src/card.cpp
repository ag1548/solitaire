#include "card.h"

Card::Card(char suit, char face)
    : suit(suit),
      face(face),
      revealed(false) {
}

char Card::GetSuit() const {
    return suit;
}

char Card::GetFace() const {
    return face;
}

bool Card::IsDarkCard() const {
    return suit == SUIT_S or suit == SUIT_C;
}

void Card::Reveal() {
    revealed = true;
}

bool Card::isRevealed() const {
    return revealed;
}

bool Card::operator==(const Card &other) {
    return other.face == face and other.suit == suit;
}

std::ostream &operator<<(std::ostream &os, const Card &card) {
    // TODO: Removing these color control strings would allow
    //       ostream to `tee` to a file and keep a game history :)
    if (card.GetSuit() == SUIT_D or card.GetSuit() == SUIT_H) {
        os << "\033[7m" << card.GetFace() << " of " << card.GetSuit() << "\033[0m";
    } else {
        os << card.GetFace() << " of " << card.GetSuit();
    }
    return os;
}
