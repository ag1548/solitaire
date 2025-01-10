#include <iostream>

#include "deck.h"

int main() {
  Deck deck;

  deck.PrintDeck();
  deck.Shuffle();
  deck.PrintDeck();
  deck.Shuffle();
  deck.PrintDeck();

  return 0;
}
