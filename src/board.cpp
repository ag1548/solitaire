#include <algorithm>
#include <iomanip>

#include "board.h"

Board::Board()
{
  // Shuffle the deck
  deck.Shuffle();

  // Populate the board stacks
  boardStack_0.push(deck.DrawCard());
  
  boardStack_1.push(deck.DrawCard());
  boardStack_1.push(deck.DrawCard());

  boardStack_2.push(deck.DrawCard());
  boardStack_2.push(deck.DrawCard());
  boardStack_2.push(deck.DrawCard());

  boardStack_3.push(deck.DrawCard());
  boardStack_3.push(deck.DrawCard());
  boardStack_3.push(deck.DrawCard());
  boardStack_3.push(deck.DrawCard());

  boardStack_4.push(deck.DrawCard());
  boardStack_4.push(deck.DrawCard());
  boardStack_4.push(deck.DrawCard());
  boardStack_4.push(deck.DrawCard());
  boardStack_4.push(deck.DrawCard());

  boardStack_5.push(deck.DrawCard());
  boardStack_5.push(deck.DrawCard());
  boardStack_5.push(deck.DrawCard());
  boardStack_5.push(deck.DrawCard());
  boardStack_5.push(deck.DrawCard());
  boardStack_5.push(deck.DrawCard());

  boardStack_6.push(deck.DrawCard());
  boardStack_6.push(deck.DrawCard());
  boardStack_6.push(deck.DrawCard());
  boardStack_6.push(deck.DrawCard());
  boardStack_6.push(deck.DrawCard());
  boardStack_6.push(deck.DrawCard());
  boardStack_6.push(deck.DrawCard());

  // Put a card in the discard pile
  discardPile.push(deck.DrawCard());

  // Put the rest in the draw pile
  while (!deck.isEmpty()) {
    drawPile.push(deck.DrawCard());
  }
}

void Board::PrintBoard() const
{

    // drawPile
    if (drawPile.size() > 0) {
        std::cout << "[" << std::setw(6) << '*' << "]";
    } else {
        std::cout << "[" << std::setw(6) << '-' << "]";
    }

    // discardPile
    if (discardPile.size() > 0) {
        std::cout << "[" << discardPile.top() << "]";
    } else {
        std::cout << "[" << std::setw(6) << '-' << "]";
    }
    
    std::cout << std::setw(8) << " ";

    // foundation_S
    if (foundation_S.size() > 0) {
        std::cout << "[" << foundation_S.top() << "]";
    } else {
        std::cout << "[" << std::setw(6) << '-' << "]";
    }

    // foundation_C
    if (foundation_C.size() > 0) {
        std::cout << "[" << foundation_C.top() << "]";
    } else {
        std::cout << "[" << std::setw(6) << '-' << "]";
    }
    
    // foundation_D
    if (foundation_D.size() > 0) {
        std::cout << "[" << foundation_D.top() << "]";
    } else {
        std::cout << "[" << std::setw(6) << '-' << "]";
    }
    // foundation_H
    if (foundation_H.size() > 0) {
        std::cout << "[" << foundation_H.top() << "]";
    } else {
        std::cout << "[" << std::setw(6) << '-' << "]";
    }

    std::cout << std::endl << std::endl;

    int index = 0;
    for (;;) {

        // boardStack_0
        if (boardStack_0.size() == 0) {
            std::cout << "[" << std::setw(6) << '-' << "]";
        } else if (index < boardStack_0.size() - 1) {
            std::cout << "[" << std::setw(6) << '*' << "]";
        } else if (index == boardStack_0.size() - 1) {
            std::cout << "[" << boardStack_0.top() << "]";
        } else {
            std::cout << " " << std::setw(6) << ' ' << " ";
        }

        // boardStack_1
        if (boardStack_1.size() == 0) {
            std::cout << "[" << std::setw(6) << '-' << "]";
        } else if (index < boardStack_1.size() - 1) {
            std::cout << "[" << std::setw(6) << '*' << "]";
        } else if (index == boardStack_1.size() - 1) {
            std::cout << "[" << boardStack_1.top() << "]";
        } else {
            std::cout << " " << std::setw(6) << ' ' << " ";
        }

        // boardStack_2
        if (boardStack_2.size() == 0) {
            std::cout << "[" << std::setw(6) << '-' << "]";
        } else if (index < boardStack_2.size() - 1) {
            std::cout << "[" << std::setw(6) << '*' << "]";
        } else if (index == boardStack_2.size() - 1) {
            std::cout << "[" << boardStack_2.top() << "]";
        } else {
            std::cout << " " << std::setw(6) << ' ' << " ";
        }

        // boardStack_3
        if (boardStack_3.size() == 0) {
            std::cout << "[" << std::setw(6) << '-' << "]";
        } else if (index < boardStack_3.size() - 1) {
            std::cout << "[" << std::setw(6) << '*' << "]";
        } else if (index == boardStack_3.size() - 1) {
            std::cout << "[" << boardStack_3.top() << "]";
        } else {
            std::cout << " " << std::setw(6) << ' ' << " ";
        }

        // boardStack_4
        if (boardStack_4.size() == 0) {
            std::cout << "[" << std::setw(6) << '-' << "]";
        } else if (index < boardStack_4.size() - 1) {
            std::cout << "[" << std::setw(6) << '*' << "]";
        } else if (index == boardStack_4.size() - 1) {
            std::cout << "[" << boardStack_4.top() << "]";
        } else {
            std::cout << " " << std::setw(6) << ' ' << " ";
        }

        // boardStack_5
        if (boardStack_5.size() == 0) {
            std::cout << "[" << std::setw(6) << '-' << "]";
        } else if (index < boardStack_5.size() - 1) {
            std::cout << "[" << std::setw(6) << '*' << "]";
        } else if (index == boardStack_5.size() - 1) {
            std::cout << "[" << boardStack_5.top() << "]";
        } else {
            std::cout << " " << std::setw(6) << ' ' << " ";
        }

        // boardStack_6
        if (boardStack_6.size() == 0) {
            std::cout << "[" << std::setw(6) << '-' << "]";
        } else if (index < boardStack_6.size() - 1) {
            std::cout << "[" << std::setw(6) << '*' << "]";
        } else if (index == boardStack_6.size() - 1) {
            std::cout << "[" << boardStack_6.top() << "]";
        } else {
            std::cout << " " << std::setw(6) << ' ' << " ";
        }

        if (
            (index >= boardStack_0.size()) &&
            (index >= boardStack_1.size()) &&
            (index >= boardStack_2.size()) &&
            (index >= boardStack_3.size()) &&
            (index >= boardStack_4.size()) &&
            (index >= boardStack_5.size()) &&
            (index >= boardStack_6.size())
        ) break;

        std::cout << std::endl;

        index++;
    }

    std::cout << std::endl;
}
