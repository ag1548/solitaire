#include <iostream>

#include "deck.h"
#include "game.h"

static void PrintMenu() {
  std::cout << "Menu:" << std::endl
            << "   0 - exit" << std::endl
            << "   1 - shuffle" << std::endl;
}

Game::Game() {

  Deck deck;

  char option = 'z';

  while (option != '0') {
    PrintMenu();

    std::cin >> option;

    switch (option) {
    case '1':
      deck.Shuffle();
      deck.PrintDeck();
    default:
      break;
    }
  }
}
