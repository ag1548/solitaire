#include "card.h"

Card::Card(char suit, char face)
: suit(suit)
, face(face)
, revealed(false)
{
}

char Card::GetFace() const { return face; }

void Card::Reveal() {
  revealed = true;
}

bool Card::isRevealed() const { return revealed; }

bool Card::operator==(const Card &other)
{
    if (other.face == face and other.suit == suit) return true;
    return false;
}
char Card::GetSuit() const { return suit; }

std::ostream &operator<<(std::ostream &os, const Card &card) {
  if (card.GetSuit() == 'D' or card.GetSuit() == 'H') {
    os << "\033[7m" << card.GetFace() << " of " << card.GetSuit() << "\033[0m";
  } else {
    os << card.GetFace() << " of " << card.GetSuit();
  }
  return os;
}

int GetIndexOfSuit(char s) {
  auto it = std::find(Suits.begin(), Suits.end(), s);
  if (it == Suits.end()) {
    return -1;
  }

  return std::distance(Suits.begin(), it);
}

int GetIndexOfFace(char f) {
  auto it = std::find(Faces.begin(), Faces.end(), f);
  if (it == Faces.end()) {
    return -1;
  }

  return std::distance(Faces.begin(), it);
}
