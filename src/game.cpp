#include <iostream>

#include "board.h"
#include "game.h"

static void PrintMenu(const Board& board) {
  std::cout << "***************************************************************" << std::endl
            << "Menu:" << std::endl
            << "   q - exit" << std::endl
            << "   p - print board" << std::endl;

  if (board.DrawPileIsEmpty()) {
    std::cout << "   d - reset draw pile" << std::endl;
  } else {
    std::cout << "   d - draw card" << std::endl;
  }
}

Game::Game() {

  Board board;
  char option;
  for(;;) {
    system("clear");
    board.PrintBoard();
    PrintMenu(board);

    std::cin >> option;
    switch (option) {
      case 'q':
        exit(0);
        break;
      case 'p':
        board.PrintBoard();
        break;
      case 'd':
        board.DrawCardOrResetDrawPile();
        break;
      default:
        break;
    }
  }
}
