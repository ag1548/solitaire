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

  std::cout << "   0-7 - Promote to foundation" << std::endl
            << "   m - Move a card (or stack of cards)" << std::endl;
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
      case 'm':
        board.MoveColumn();
        break;
      default:
        if (option >= '0' and option <= '9') {
          board.PromoteToFoundation(option);
        }
        break;
    }
  }
}
