#pragma once

#include <vector>
#include <random>

#include "card.h"

class Deck {
public:
  Deck();

  void Shuffle();

  void PrintDeck() const;

private:
  std::minstd_rand0 rng;
  std::vector<Card> cards;
};
