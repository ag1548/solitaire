#include <algorithm>
#include <iomanip>

#include "board.h"
#include "common.h"

Board::Board()
{
  // Shuffle the deck
  deck.Shuffle();

  // Populate the board stacks
  boardStack_0.push_back(deck.DrawCard());
  
  boardStack_1.push_back(deck.DrawCard());
  boardStack_1.push_back(deck.DrawCard());

  boardStack_2.push_back(deck.DrawCard());
  boardStack_2.push_back(deck.DrawCard());
  boardStack_2.push_back(deck.DrawCard());

  boardStack_3.push_back(deck.DrawCard());
  boardStack_3.push_back(deck.DrawCard());
  boardStack_3.push_back(deck.DrawCard());
  boardStack_3.push_back(deck.DrawCard());

  boardStack_4.push_back(deck.DrawCard());
  boardStack_4.push_back(deck.DrawCard());
  boardStack_4.push_back(deck.DrawCard());
  boardStack_4.push_back(deck.DrawCard());
  boardStack_4.push_back(deck.DrawCard());

  boardStack_5.push_back(deck.DrawCard());
  boardStack_5.push_back(deck.DrawCard());
  boardStack_5.push_back(deck.DrawCard());
  boardStack_5.push_back(deck.DrawCard());
  boardStack_5.push_back(deck.DrawCard());
  boardStack_5.push_back(deck.DrawCard());

  boardStack_6.push_back(deck.DrawCard());
  boardStack_6.push_back(deck.DrawCard());
  boardStack_6.push_back(deck.DrawCard());
  boardStack_6.push_back(deck.DrawCard());
  boardStack_6.push_back(deck.DrawCard());
  boardStack_6.push_back(deck.DrawCard());
  boardStack_6.push_back(deck.DrawCard());

  // Put the rest in the draw pile
  while (!deck.isEmpty()) {
    drawPile.push_back(deck.DrawCard());
  }
}

void Board::DrawCardOrResetDrawPile()
{
    if (DrawPileIsEmpty()) {
        ResetDrawPile();
    } else {
        DrawCard();
        PrintBoard();
    }
}

void Board::DrawCard()
{
    discardPile.push_back(drawPile.back());
    drawPile.pop_back();
}

void Board::ResetDrawPile()
{
    std::for_each(discardPile.rbegin(), discardPile.rend(), [&](Card c){
        drawPile.push_back(c);
    });
    discardPile.clear();
}

bool Board::DrawPileIsEmpty() const
{
    return drawPile.empty();
}

std::vector<Card>& Board::GetFoundation(const Card& c) {
    switch(c.GetSuit()) {
        case 'S': return foundation_S;
        case 'C': return foundation_C;
        case 'H': return foundation_H;
        case 'D': return foundation_D;
    }

    GameAbort(std::string("Invalid suit for foundation fetch: ") + c.GetSuit());
}

void Board::PromoteToFoundation(std::vector<Card> sourceBoardStack) {

    // Get the corresponding foundation
    std::vector<Card>& foundation = GetFoundation(sourceBoardStack.back());

    // Initial card
    if (foundation.empty() and sourceBoardStack.back().GetFace() == 'A') {
        foundation.push_back(sourceBoardStack.back());
        sourceBoardStack.pop_back();
        return;
    } 

    // All the others
    int indexOfFoundationTopFace = GetIndexOfFace(foundation.back().GetFace());
    int indexOfCardFace = GetIndexOfFace(sourceBoardStack.back().GetFace());
    if (indexOfFoundationTopFace == indexOfCardFace - 1) {
        foundation.push_back(sourceBoardStack.back());
        sourceBoardStack.pop_back();
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
        std::cout << "[" << discardPile.back() << "]";
    } else {
        std::cout << "[" << std::setw(6) << '-' << "]";
    }
    
    std::cout << std::setw(8) << " ";

    // foundation_S
    if (foundation_S.size() > 0) {
        std::cout << "[" << foundation_S.back() << "]";
    } else {
        std::cout << "[" << std::setw(6) << '-' << "]";
    }

    // foundation_C
    if (foundation_C.size() > 0) {
        std::cout << "[" << foundation_C.back() << "]";
    } else {
        std::cout << "[" << std::setw(6) << '-' << "]";
    }
    
    // foundation_D
    if (foundation_D.size() > 0) {
        std::cout << "[" << foundation_D.back() << "]";
    } else {
        std::cout << "[" << std::setw(6) << '-' << "]";
    }
    // foundation_H
    if (foundation_H.size() > 0) {
        std::cout << "[" << foundation_H.back() << "]";
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
            std::cout << "[" << boardStack_0.back() << "]";
        } else {
            std::cout << " " << std::setw(6) << ' ' << " ";
        }

        // boardStack_1
        if (boardStack_1.size() == 0) {
            std::cout << "[" << std::setw(6) << '-' << "]";
        } else if (index < boardStack_1.size() - 1) {
            std::cout << "[" << std::setw(6) << '*' << "]";
        } else if (index == boardStack_1.size() - 1) {
            std::cout << "[" << boardStack_1.back() << "]";
        } else {
            std::cout << " " << std::setw(6) << ' ' << " ";
        }

        // boardStack_2
        if (boardStack_2.size() == 0) {
            std::cout << "[" << std::setw(6) << '-' << "]";
        } else if (index < boardStack_2.size() - 1) {
            std::cout << "[" << std::setw(6) << '*' << "]";
        } else if (index == boardStack_2.size() - 1) {
            std::cout << "[" << boardStack_2.back() << "]";
        } else {
            std::cout << " " << std::setw(6) << ' ' << " ";
        }

        // boardStack_3
        if (boardStack_3.size() == 0) {
            std::cout << "[" << std::setw(6) << '-' << "]";
        } else if (index < boardStack_3.size() - 1) {
            std::cout << "[" << std::setw(6) << '*' << "]";
        } else if (index == boardStack_3.size() - 1) {
            std::cout << "[" << boardStack_3.back() << "]";
        } else {
            std::cout << " " << std::setw(6) << ' ' << " ";
        }

        // boardStack_4
        if (boardStack_4.size() == 0) {
            std::cout << "[" << std::setw(6) << '-' << "]";
        } else if (index < boardStack_4.size() - 1) {
            std::cout << "[" << std::setw(6) << '*' << "]";
        } else if (index == boardStack_4.size() - 1) {
            std::cout << "[" << boardStack_4.back() << "]";
        } else {
            std::cout << " " << std::setw(6) << ' ' << " ";
        }

        // boardStack_5
        if (boardStack_5.size() == 0) {
            std::cout << "[" << std::setw(6) << '-' << "]";
        } else if (index < boardStack_5.size() - 1) {
            std::cout << "[" << std::setw(6) << '*' << "]";
        } else if (index == boardStack_5.size() - 1) {
            std::cout << "[" << boardStack_5.back() << "]";
        } else {
            std::cout << " " << std::setw(6) << ' ' << " ";
        }

        // boardStack_6
        if (boardStack_6.size() == 0) {
            std::cout << "[" << std::setw(6) << '-' << "]";
        } else if (index < boardStack_6.size() - 1) {
            std::cout << "[" << std::setw(6) << '*' << "]";
        } else if (index == boardStack_6.size() - 1) {
            std::cout << "[" << boardStack_6.back() << "]";
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
