#include <algorithm>
#include <iomanip>

#include "board.h"

Board::Board()
{
}

void Board::PrintBoard() const
{

    // drawPile
    if (drawPile.size() > 0) {
        std::cout << "[" << drawPile.top() << "]";
    } else {
        std::cout << "[" << std::setw(3) << '-' << "]";
    }

    // discardPile
    if (discardPile.size() > 0) {
        std::cout << "[" << discardPile.top() << "]";
    } else {
        std::cout << "[" << std::setw(3) << '-' << "]";
    }
    
    std::cout << std::setw(5) << " ";

    // foundation_S
    if (foundation_S.size() > 0) {
        std::cout << "[" << foundation_S.top() << "]";
    } else {
        std::cout << "[" << std::setw(3) << '-' << "]";
    }

    // foundation_C
    if (foundation_C.size() > 0) {
        std::cout << "[" << foundation_C.top() << "]";
    } else {
        std::cout << "[" << std::setw(3) << '-' << "]";
    }
    
    // foundation_D
    if (foundation_D.size() > 0) {
        std::cout << "[" << foundation_D.top() << "]";
    } else {
        std::cout << "[" << std::setw(3) << '-' << "]";
    }
    // foundation_H
    if (foundation_H.size() > 0) {
        std::cout << "[" << foundation_H.top() << "]";
    } else {
        std::cout << "[" << std::setw(3) << '-' << "]";
    }

    std::cout << std::endl;

    // boardStack_0
    if (boardStack_0.size() > 0) {
        std::cout << "[" << boardStack_0.top() << "]";
    } else {
        std::cout << "[" << std::setw(3) << '-' << "]";
    }

    // boardStack_1
    if (boardStack_1.size() > 0) {
        std::cout << "[" << boardStack_1.top() << "]";
    } else {
        std::cout << "[" << std::setw(3) << '-' << "]";
    }

    // boardStack_2
    if (boardStack_2.size() > 0) {
        std::cout << "[" << boardStack_2.top() << "]";
    } else {
        std::cout << "[" << std::setw(3) << '-' << "]";
    }

    // boardStack_3
    if (boardStack_3.size() > 0) {
        std::cout << "[" << boardStack_3.top() << "]";
    } else {
        std::cout << "[" << std::setw(3) << '-' << "]";
    }

    // boardStack_4
    if (boardStack_4.size() > 0) {
        std::cout << "[" << boardStack_4.top() << "]";
    } else {
        std::cout << "[" << std::setw(3) << '-' << "]";
    }

    // boardStack_5
    if (boardStack_5.size() > 0) {
        std::cout << "[" << boardStack_5.top() << "]";
    } else {
        std::cout << "[" << std::setw(3) << '-' << "]";
    }

    // boardStack_6
    if (boardStack_6.size() > 0) {
        std::cout << "[" << boardStack_6.top() << "]";
    } else {
        std::cout << "[" << std::setw(3) << '-' << "]";
    }

    std::cout << std::endl;
}
