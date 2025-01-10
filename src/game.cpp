#include <iostream>

#include "board.h"
#include "game.h"

static void PrintMenu() {
  std::cout << "***************************************************************" << std::endl
            << "Menu:" << std::endl
            << "   q - exit" << std::endl
            << "   p - print board" << std::endl;
            // << "   s - shuffle" << std::endl
            // << "   d - draw card" << std::endl;
}

Game::Game() {

  Board board;
  board.PrintBoard();

  char option;
  for(;;) {
    PrintMenu();

    std::cin >> option;

    switch (option) {
      case 'q':
        exit(0);
        break;
      case 'p':
        board.PrintBoard();
        break;
    //   case 's':
    //     deck.Shuffle();
    //     deck.PrintBoard();
    //     break;
    //   case 'd':
    //     board.DrawCard();
    //     break;
      default:
        break;
    }
  }
}
