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
  boardStack_0[0].Reveal();
  
  boardStack_1.push_back(deck.DrawCard());
  boardStack_1.push_back(deck.DrawCard());
  boardStack_1[1].Reveal();

  boardStack_2.push_back(deck.DrawCard());
  boardStack_2.push_back(deck.DrawCard());
  boardStack_2.push_back(deck.DrawCard());
  boardStack_2[2].Reveal();

  boardStack_3.push_back(deck.DrawCard());
  boardStack_3.push_back(deck.DrawCard());
  boardStack_3.push_back(deck.DrawCard());
  boardStack_3.push_back(deck.DrawCard());
  boardStack_3[3].Reveal();

  boardStack_4.push_back(deck.DrawCard());
  boardStack_4.push_back(deck.DrawCard());
  boardStack_4.push_back(deck.DrawCard());
  boardStack_4.push_back(deck.DrawCard());
  boardStack_4.push_back(deck.DrawCard());
  boardStack_4[4].Reveal();

  boardStack_5.push_back(deck.DrawCard());
  boardStack_5.push_back(deck.DrawCard());
  boardStack_5.push_back(deck.DrawCard());
  boardStack_5.push_back(deck.DrawCard());
  boardStack_5.push_back(deck.DrawCard());
  boardStack_5.push_back(deck.DrawCard());
  boardStack_5[5].Reveal();

  boardStack_6.push_back(deck.DrawCard());
  boardStack_6.push_back(deck.DrawCard());
  boardStack_6.push_back(deck.DrawCard());
  boardStack_6.push_back(deck.DrawCard());
  boardStack_6.push_back(deck.DrawCard());
  boardStack_6.push_back(deck.DrawCard());
  boardStack_6.push_back(deck.DrawCard());
  boardStack_6[6].Reveal();

  // Put the rest in the draw pile
  while (!deck.isEmpty()) {
    drawPile.push_back(deck.DrawCard());
    drawPile.back().Reveal();
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

void Board::MoveColumn() {
    std::cout << "Move from which column? ";
    int from;
    std::cin >> from;

    std::cout << "Move to which column? ";
    int to;
    std::cin >> to;

    // FIXME: Don't abort when to-column is the discard pile!
    if (to == 0) {
        GameAbort(std::string("You can't move to the discard pile..."));
    }

    AttemptColumnMove(from, to);
}

void Board::RevealTopMostCard(std::vector<Card> &sourceBoardStack)
{
    // Reveal the top most card of the boardStack
    // NOTE: Cards in the draw/discard pile are already revealed
    if (sourceBoardStack.size() > 0) {
        sourceBoardStack.back().Reveal();
    }
}

void Board::AttemptColumnMove(int from, int to)
{

    // TODO: This is different if moving from the discard pile
    // TODO: The only card that can move to empty columns are kings

    // In the "from" column, get the "top-most" revealed card
    std::vector<Card>& sourceStack = GetSourceBoardStack(from);
    if (sourceStack.size() == 0) {
        // FIXME: Don't crash on moving from empty stack
        GameAbort(std::string("Can't move from an empty stack!"));
    }
    int sourceIndex = 0;
    while (!sourceStack[sourceIndex].isRevealed()) {
        sourceIndex++;
    }
    Card& fromCard = sourceStack[sourceIndex];

    // In the "to" column, get the "bottom-most" revealed card
    std::vector<Card>& targetStack = GetSourceBoardStack(to);
    if (targetStack.size() == 0) {
        // FIXME: Don't crash on moving to empty stack
        GameAbort(std::string("Can't move from an empty stack!"));
    }
    Card& toCard = targetStack[targetStack.size() - 1];

    // Ensure that they are of opposite suit before the move'
    if (fromCard.IsDarkCard() == toCard.IsDarkCard()) {
      return;
    }

    // Ensure that the "from" card is one number down from the "to" card
    int fromIndex = GetIndexOfFace(fromCard.GetFace());
    int toIndex = GetIndexOfFace(toCard.GetFace());
    if (fromIndex + 1 != toIndex) {
      return;
    }

    // Move the column
    int numberMoved = 0;
    std::for_each(sourceStack.begin() + sourceIndex, sourceStack.end(), [&](Card c){
        numberMoved++;
        targetStack.push_back(c);
    });
    while(numberMoved--) sourceStack.pop_back();

    // Reveal topmost card
    RevealTopMostCard(sourceStack);
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

std::vector<Card> &Board::GetSourceBoardStack(int stackID)
{
    switch (stackID)
    {
        case 0: return discardPile;
        case 1: return boardStack_0;
        case 2: return boardStack_1;
        case 3: return boardStack_2;
        case 4: return boardStack_3;
        case 5: return boardStack_4;
        case 6: return boardStack_5;
        case 7: return boardStack_6;
    }

    // TODO: Take this into account later
    GameAbort(std::string("Invalid stack ID to promote: ") + std::to_string(stackID));
}

void Board::PromoteToFoundation(char option) {

    std::vector<Card>& sourceBoardStack = GetSourceBoardStack(static_cast<int>(option - '0'));

    // Get the corresponding foundation
    std::vector<Card>& foundation = GetFoundation(sourceBoardStack.back());

    // Initial card
    if (foundation.empty() and sourceBoardStack.back().GetFace() == 'A') {
        foundation.push_back(sourceBoardStack.back());
        sourceBoardStack.pop_back();
    } else {
        // All the others
        int indexOfFoundationTopFace = GetIndexOfFace(foundation.back().GetFace());
        int indexOfCardFace = GetIndexOfFace(sourceBoardStack.back().GetFace());
        if (indexOfFoundationTopFace == indexOfCardFace - 1) {
            foundation.push_back(sourceBoardStack.back());
            sourceBoardStack.pop_back();
        }
    }

    RevealTopMostCard(sourceBoardStack);
}

void Board::PrintBoard() const
{

    std::cout << std::setw(8) << " " << std::setw(8) << "[c0]" << std::endl;

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

    // Column numbers
    std::cout << std::setw(8) << "[c1]"
              << std::setw(8) << "[c2]"
              << std::setw(8) << "[c3]"
              << std::setw(8) << "[c4]"
              << std::setw(8) << "[c5]"
              << std::setw(8) << "[c6]"
              << std::setw(8) << "[c7]"
              << std::endl;

    int index = 0;
    for (;;) {

        // boardStack_0
        if (boardStack_0.size() == 0 && index == 0) {
            std::cout << "[" << std::setw(6) << '-' << "]";
        } else if (index >= boardStack_0.size()) {
            std::cout << " " << std::setw(6) << ' ' << " ";
        } else if (boardStack_0[index].isRevealed()) {
            std::cout << "[" << boardStack_0[index] << "]";
        } else if (!boardStack_0[index].isRevealed()) {
            std::cout << "[" << std::setw(6) << '*' << "]";
        }

        // boardStack_1
        if (boardStack_1.size() == 0) {
            std::cout << "[" << std::setw(6) << '-' << "]";
        } else if (index >= boardStack_1.size()) {
            std::cout << " " << std::setw(6) << ' ' << " ";
        } else if (boardStack_1[index].isRevealed()) {
            std::cout << "[" << boardStack_1[index] << "]";
        } else if (!boardStack_1[index].isRevealed()) {
            std::cout << "[" << std::setw(6) << '*' << "]";
        }

        // boardStack_2
        if (boardStack_2.size() == 0) {
            std::cout << "[" << std::setw(6) << '-' << "]";
        } else if (index >= boardStack_2.size()) {
            std::cout << " " << std::setw(6) << ' ' << " ";
        } else if (boardStack_2[index].isRevealed()) {
            std::cout << "[" << boardStack_2[index] << "]";
        } else if (!boardStack_2[index].isRevealed()) {
            std::cout << "[" << std::setw(6) << '*' << "]";
        }

        // boardStack_3
        if (boardStack_3.size() == 0) {
            std::cout << "[" << std::setw(6) << '-' << "]";
        } else if (index >= boardStack_3.size()) {
            std::cout << " " << std::setw(6) << ' ' << " ";
        } else if (boardStack_3[index].isRevealed()) {
            std::cout << "[" << boardStack_3[index] << "]";
        } else if (!boardStack_3[index].isRevealed()) {
            std::cout << "[" << std::setw(6) << '*' << "]";
        }

        // boardStack_4
        if (boardStack_4.size() == 0) {
            std::cout << "[" << std::setw(6) << '-' << "]";
        } else if (index >= boardStack_4.size()) {
            std::cout << " " << std::setw(6) << ' ' << " ";
        } else if (boardStack_4[index].isRevealed()) {
            std::cout << "[" << boardStack_4[index] << "]";
        } else if (!boardStack_4[index].isRevealed()) {
            std::cout << "[" << std::setw(6) << '*' << "]";
        }

        // boardStack_5
        if (boardStack_5.size() == 0) {
            std::cout << "[" << std::setw(6) << '-' << "]";
        } else if (index >= boardStack_5.size()) {
            std::cout << " " << std::setw(6) << ' ' << " ";
        } else if (boardStack_5[index].isRevealed()) {
            std::cout << "[" << boardStack_5[index] << "]";
        } else if (!boardStack_5[index].isRevealed()) {
            std::cout << "[" << std::setw(6) << '*' << "]";
        }

        // boardStack_6
        if (boardStack_6.size() == 0) {
            std::cout << "[" << std::setw(6) << '-' << "]";
        } else if (index >= boardStack_6.size()) {
            std::cout << " " << std::setw(6) << ' ' << " ";
        } else if (boardStack_6[index].isRevealed()) {
            std::cout << "[" << boardStack_6[index] << "]";
        } else if (!boardStack_6[index].isRevealed()) {
            std::cout << "[" << std::setw(6) << '*' << "]";
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
