#include <vector>

#include "card.h"

class Deck {
public:
  Deck();

  void PrintDeck();

private:
  std::vector<Card> cards;
};
