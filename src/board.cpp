#include <algorithm>
#include <iomanip>

#include "board.h"
#include "common.h"

Board::Board() {
    // NOTE: Setup test scenarios here simply
    //       by making Card(<suit>, <face>) and
    //       Adding them to the particular stack

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

void Board::DrawCardOrResetDrawPile() {
    if (DrawPileIsEmpty()) {
        ResetDrawPile();
    } else {
        DrawCard();
    }
}

bool Board::DrawPileIsEmpty() const {
    return drawPile.empty();
}

void Board::DrawCard() {
    discardPile.push_back(drawPile.back());
    drawPile.pop_back();
}

void Board::ResetDrawPile() {
    std::for_each(discardPile.rbegin(), discardPile.rend(), [&](Card c) {
        drawPile.push_back(c);
    });
    discardPile.clear();
}

void Board::MoveColumn() {
    int from;
    std::cout << "Move from which column? ";
    std::cin >> from;
    while (!std::cin or not(from >= 0 and from <= 7)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Move from which column? ";
        std::cin >> from;
    }

    int to;
    std::cout << "Move to which column? ";
    std::cin >> to;
    while (!std::cin or not(from >= 0 and from <= 7)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Move to which column? ";
        std::cin >> to;
    }

    if (from == 0) {
        // Move from the discard pile
        AttemptMoveFromDiscardPile(to);
    } else {
        AttemptColumnMove(from, to);
    }
}

void Board::RevealTopMostCard(std::vector<Card> &sourceBoardStack) {
    if (sourceBoardStack.size() > 0) {
        sourceBoardStack.back().Reveal();
    }
}

void Board::AttemptMoveFromDiscardPile(int to) {

    // Can't move from empty discard pile
    if (discardPile.size() == 0 or to == 0) {
        return;
    }

    // Get the "from" card
    Card &fromCard = discardPile.back();

    if (fromCard.GetFace() == FACE_K) {
        // If moving a king, ensure that the target stack is empty
        std::vector<Card> &targetStack = GetSourceBoardStack(to);
        if (targetStack.size() > 0) {
            return;
        }

        // Checks passed; Move the card
        targetStack.push_back(fromCard);
        discardPile.pop_back();
        return;
    }

    // NOTE: Card is not a FACE_K

    // In the "to" column, get the "bottom-most" revealed card
    std::vector<Card> &targetStack = GetSourceBoardStack(to);
    if (targetStack.size() == 0) {
        return;
    }
    Card &toCard = targetStack[targetStack.size() - 1];

    // Ensure that the moving card is opposite color
    if (fromCard.IsDarkCard() == toCard.IsDarkCard()) {
        return;
    }

    // Ensure that the "from" card is "one less" from the "to" card
    int fromIndex = GetIndexOfFace(fromCard.GetFace());
    int toIndex   = GetIndexOfFace(toCard.GetFace());
    if (fromIndex + 1 != toIndex) {
        return;
    }

    // Checks passed; Move the card
    targetStack.push_back(fromCard);
    discardPile.pop_back();
}

void Board::AttemptColumnMove(int from, int to) {
    // Nothing to move
    if (from == to) {
        return;
    }

    // Can't move to the discard pile
    if (to == 0) {
        return;
    }

    // In the "from" column, get the "top-most" revealed card
    std::vector<Card> &sourceStack = GetSourceBoardStack(from);
    if (sourceStack.size() == 0) {
        return;
    }
    int sourceIndex = 0;
    while (!sourceStack[sourceIndex].isRevealed()) {
        sourceIndex++;
    }
    Card &fromCard = sourceStack[sourceIndex];

    // In the "to" column, get the "bottom-most" revealed card
    std::vector<Card> &targetStack = GetSourceBoardStack(to);

    // The only card that can move to empty columns are kings
    if (targetStack.size() == 0) {
        if (fromCard.GetFace() != FACE_K) {
            return;
        }

        // Move the whole column to the empty one
        int numberMoved = 0;
        std::for_each(sourceStack.begin() + sourceIndex, sourceStack.end(), [&](Card c) {
            numberMoved++;
            targetStack.push_back(c);
        });
        while (numberMoved--) {
            sourceStack.pop_back();
        }
        RevealTopMostCard(sourceStack);
        return;
    }
    Card &toCard = targetStack[targetStack.size() - 1];

    // Ensure that they are of opposite suit before the move
    if (fromCard.IsDarkCard() == toCard.IsDarkCard()) {
        return;
    }

    // Ensure that the "from" card is "one less" from the "to" card
    int fromIndex = GetIndexOfFace(fromCard.GetFace());
    int toIndex   = GetIndexOfFace(toCard.GetFace());
    if (fromIndex + 1 != toIndex) {
        return;
    }

    // Move the column
    int numberMoved = 0;
    std::for_each(sourceStack.begin() + sourceIndex, sourceStack.end(), [&](Card c) {
        numberMoved++;
        targetStack.push_back(c);
    });
    while (numberMoved--) {
        sourceStack.pop_back();
    }

    RevealTopMostCard(sourceStack);
}

std::vector<Card> &Board::GetFoundation(const Card &c) {
    switch (c.GetSuit()) {
        case SUIT_S:
            return foundation_S;
        case SUIT_C:
            return foundation_C;
        case SUIT_H:
            return foundation_H;
        case SUIT_D:
            return foundation_D;
    }

    GameAbort(std::string("Invalid suit for foundation fetch: ") + c.GetSuit());
}

std::vector<Card> &Board::GetSourceBoardStack(int stackID) {
    switch (stackID) {
        case 0:
            return discardPile;
        case 1:
            return boardStack_0;
        case 2:
            return boardStack_1;
        case 3:
            return boardStack_2;
        case 4:
            return boardStack_3;
        case 5:
            return boardStack_4;
        case 6:
            return boardStack_5;
        case 7:
            return boardStack_6;
    }

    // TODO: Take this into account
    GameAbort(std::string("Invalid stack ID to promote: ") + std::to_string(stackID));
}

void Board::PromoteToFoundation(char option) {

    std::vector<Card> &sourceBoardStack = GetSourceBoardStack(static_cast<int>(option - '0'));

    // Do nothing if source stack is empty
    if (sourceBoardStack.size() == 0) {
        return;
    }

    // Get the corresponding foundation
    std::vector<Card> &foundation = GetFoundation(sourceBoardStack.back());

    // Initial card
    if (foundation.empty() and sourceBoardStack.back().GetFace() == FACE_A) {
        foundation.push_back(sourceBoardStack.back());
        sourceBoardStack.pop_back();
        RevealTopMostCard(sourceBoardStack);
        return;
    }

    if (foundation.empty()) {
        return;
    }

    // All the others
    int indexOfFoundationTopFace = GetIndexOfFace(foundation.back().GetFace());
    int indexOfCardFace          = GetIndexOfFace(sourceBoardStack.back().GetFace());
    if (indexOfFoundationTopFace == indexOfCardFace - 1) {
        foundation.push_back(sourceBoardStack.back());
        sourceBoardStack.pop_back();
        RevealTopMostCard(sourceBoardStack);
    }
}

bool Board::CheckWinCondition() const {
    if (foundation_S.size() > 0 and foundation_S.back().GetFace() == FACE_K and //
        foundation_C.size() > 0 and foundation_C.back().GetFace() == FACE_K and //
        foundation_H.size() > 0 and foundation_H.back().GetFace() == FACE_K and //
        foundation_D.size() > 0 and foundation_D.back().GetFace() == FACE_K) {
        return true;
    }

    return false;
}

void Board::PrintBoard() const {

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
    std::cout << std::setw(8) << "[c1]" //
              << std::setw(8) << "[c2]" //
              << std::setw(8) << "[c3]" //
              << std::setw(8) << "[c4]" //
              << std::setw(8) << "[c5]" //
              << std::setw(8) << "[c6]" //
              << std::setw(8) << "[c7]" << std::endl;

    int index = 0;
    for (;;) {

        // boardStack_0
        if (boardStack_0.size() == 0 and index == 0) {
            std::cout << "[" << std::setw(6) << '-' << "]";
        } else if (index >= boardStack_0.size()) {
            std::cout << " " << std::setw(6) << ' ' << " ";
        } else if (boardStack_0[index].isRevealed()) {
            std::cout << "[" << boardStack_0[index] << "]";
        } else if (!boardStack_0[index].isRevealed()) {
            std::cout << "[" << std::setw(6) << '*' << "]";
        }

        // boardStack_1
        if (boardStack_1.size() == 0 and index == 0) {
            std::cout << "[" << std::setw(6) << '-' << "]";
        } else if (index >= boardStack_1.size()) {
            std::cout << " " << std::setw(6) << ' ' << " ";
        } else if (boardStack_1[index].isRevealed()) {
            std::cout << "[" << boardStack_1[index] << "]";
        } else if (!boardStack_1[index].isRevealed()) {
            std::cout << "[" << std::setw(6) << '*' << "]";
        }

        // boardStack_2
        if (boardStack_2.size() == 0 and index == 0) {
            std::cout << "[" << std::setw(6) << '-' << "]";
        } else if (index >= boardStack_2.size()) {
            std::cout << " " << std::setw(6) << ' ' << " ";
        } else if (boardStack_2[index].isRevealed()) {
            std::cout << "[" << boardStack_2[index] << "]";
        } else if (!boardStack_2[index].isRevealed()) {
            std::cout << "[" << std::setw(6) << '*' << "]";
        }

        // boardStack_3
        if (boardStack_3.size() == 0 and index == 0) {
            std::cout << "[" << std::setw(6) << '-' << "]";
        } else if (index >= boardStack_3.size()) {
            std::cout << " " << std::setw(6) << ' ' << " ";
        } else if (boardStack_3[index].isRevealed()) {
            std::cout << "[" << boardStack_3[index] << "]";
        } else if (!boardStack_3[index].isRevealed()) {
            std::cout << "[" << std::setw(6) << '*' << "]";
        }

        // boardStack_4
        if (boardStack_4.size() == 0 and index == 0) {
            std::cout << "[" << std::setw(6) << '-' << "]";
        } else if (index >= boardStack_4.size()) {
            std::cout << " " << std::setw(6) << ' ' << " ";
        } else if (boardStack_4[index].isRevealed()) {
            std::cout << "[" << boardStack_4[index] << "]";
        } else if (!boardStack_4[index].isRevealed()) {
            std::cout << "[" << std::setw(6) << '*' << "]";
        }

        // boardStack_5
        if (boardStack_5.size() == 0 and index == 0) {
            std::cout << "[" << std::setw(6) << '-' << "]";
        } else if (index >= boardStack_5.size()) {
            std::cout << " " << std::setw(6) << ' ' << " ";
        } else if (boardStack_5[index].isRevealed()) {
            std::cout << "[" << boardStack_5[index] << "]";
        } else if (!boardStack_5[index].isRevealed()) {
            std::cout << "[" << std::setw(6) << '*' << "]";
        }

        // boardStack_6
        if (boardStack_6.size() == 0 and index == 0) {
            std::cout << "[" << std::setw(6) << '-' << "]";
        } else if (index >= boardStack_6.size()) {
            std::cout << " " << std::setw(6) << ' ' << " ";
        } else if (boardStack_6[index].isRevealed()) {
            std::cout << "[" << boardStack_6[index] << "]";
        } else if (!boardStack_6[index].isRevealed()) {
            std::cout << "[" << std::setw(6) << '*' << "]";
        }

        if ((index >= boardStack_0.size()) and //
            (index >= boardStack_1.size()) and //
            (index >= boardStack_2.size()) and //
            (index >= boardStack_3.size()) and //
            (index >= boardStack_4.size()) and //
            (index >= boardStack_5.size()) and //
            (index >= boardStack_6.size())) {
            break;
        }

        std::cout << std::endl;

        index++;
    }

    // Print minimum 13 lines for somewhat-consistent printing
    while (index++ <= 13) {
        std::cout << std::endl;
    }

    std::cout << std::endl;
}
