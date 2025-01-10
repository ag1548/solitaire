#include <array>
#include <iostream>

const std::array<char, 4> Suits = {
    'S',
    'C',
    'H',
    'D',
};

const std::array<char, 13> Faces = {
    'A', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'J', 'Q', 'K',
};

class Card {
public:
  Card(char, char);

  friend std::ostream &operator<<(std::ostream &os, const Card &card) {
    return os << card.face << " of " << card.suit;
  }

private:
  char suit;
  char face;
};
