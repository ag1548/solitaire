#include <iostream>

#include "board.h"
#include "game.h"

static void PrintMenu(const Board &board) {
    std::cout << "***************************************************************" << std::endl
              << "Menu:" << std::endl
              << "   q - exit" << std::endl
              << "   d - [reset] draw pile" << std::endl
              << "   0-7 - Promote to foundation ('0' is the discard pile)" << std::endl
              << "   m - Move a card (or stack of cards)" << std::endl;
}

Game::Game() {

    Board board;
    char  option;

    for (;;) {
        board.PrintBoard();
        PrintMenu(board);

        std::cout << ">>> ";
        std::cin >> option;
        switch (option) {
            case 'q':
                exit(0);
            case 'd':
                board.DrawCardOrResetDrawPile();
                break;
            case 'm':
                board.MoveColumn();
                break;
            default:
                if (option >= '0' and option <= '7') {
                    board.PromoteToFoundation(option);
                }
                break;
        }

        std::cout << "***************************************************************" << std::endl;
        if (board.CheckWinCondition()) {
            board.PrintBoard();
            break;
        }
    }

    std::cout << "************ YOU WIN! ************" << std::endl;
}
