#include "card.h"

Card::Card(char suit, char face) {
  this->suit = suit;
  this->face = face;
}

char Card::GetFace() const { return face; }

bool Card::operator==(const Card &other)
{
    if (other.face == face and other.suit == suit) return true;
    return false;
}
char Card::GetSuit() const { return suit; }

std::ostream &operator<<(std::ostream &os, const Card &card) {
  os << card.GetFace() << " of " << card.GetSuit();
  return os;
}
