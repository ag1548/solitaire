#pragma once

#include <array>
#include <vector>

#include "card.h"
#include "deck.h"

class Board {
public:
    explicit Board();

    void DrawCardOrResetDrawPile();
    void ResetDrawPile();

    void MoveColumn();

    void PromoteToFoundation(char option);

    bool CheckWinCondition() const;

    void PrintBoard() const;

private:
    Deck deck;

    std::vector<Card> drawPile;
    std::vector<Card> discardPile;

    std::vector<Card> &GetFoundation(const Card &);
    std::vector<Card>  foundation_S;
    std::vector<Card>  foundation_C;
    std::vector<Card>  foundation_D;
    std::vector<Card>  foundation_H;

    const std::array<std::reference_wrapper<std::vector<Card>>, 4> foundationStacks = {
        foundation_S,
        foundation_C,
        foundation_D,
        foundation_H,
    };

    std::vector<Card> &GetSourceBoardStack(int);
    std::vector<Card>  boardStack_0;
    std::vector<Card>  boardStack_1;
    std::vector<Card>  boardStack_2;
    std::vector<Card>  boardStack_3;
    std::vector<Card>  boardStack_4;
    std::vector<Card>  boardStack_5;
    std::vector<Card>  boardStack_6;

    const std::array<std::reference_wrapper<std::vector<Card>>, 7> boardStacks = {
        boardStack_0,
        boardStack_1,
        boardStack_2,
        boardStack_3,
        boardStack_4,
        boardStack_5,
        boardStack_6,
    };

    void RevealTopMostCard(std::vector<Card> &);
    void AttemptMoveFromDiscardPile(int);
    void AttemptColumnMove(int, int);
};