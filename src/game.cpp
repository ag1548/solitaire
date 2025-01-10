#include <iostream>

#include "deck.h"
#include "game.h"

static void PrintMenu() {
  std::cout << "***************************************************************" << std::endl
            << "Menu:" << std::endl
            << "   q - exit" << std::endl
            << "   p - print deck" << std::endl
            << "   s - shuffle" << std::endl
            << "   d - draw card" << std::endl;
}

Game::Game() {

  Deck deck;

  char option;
  for(;;) {
    PrintMenu();

    std::cin >> option;

    switch (option) {
      case 'q':
        exit(0);
        break;
      case 'p':
        deck.PrintDeck();
        break;
      case 's':
        deck.Shuffle();
        deck.PrintDeck();
        break;
      case 'd':
        deck.DrawCard();
        break;
      default:
        break;
    }
  }
}
