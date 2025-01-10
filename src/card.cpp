#include "card.h"

Card::Card(char suit, char face) {
  this->suit = suit;
  this->face = face;
}

char Card::GetFace() const { return face; }
char Card::GetSuit() const { return suit; }

std::ostream &operator<<(std::ostream &os, const Card &card) {
  os << card.GetFace() << " of " << card.GetSuit();
  return os;
}
