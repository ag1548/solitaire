#pragma once

#include <algorithm>
#include <array>
#include <iostream>

const char SUIT_S = 'S';
const char SUIT_C = 'C';
const char SUIT_H = 'H';
const char SUIT_D = 'D';

const char FACE_A = 'A';
const char FACE_2 = '2';
const char FACE_3 = '3';
const char FACE_4 = '4';
const char FACE_5 = '5';
const char FACE_6 = '6';
const char FACE_7 = '7';
const char FACE_8 = '8';
const char FACE_9 = '9';
const char FACE_0 = '0';
const char FACE_J = 'J';
const char FACE_Q = 'Q';
const char FACE_K = 'K';

const std::array<char, 4> SUITS = {
    SUIT_S,
    SUIT_C,
    SUIT_H,
    SUIT_D,
};

const std::array<char, 13> FACES = {
    FACE_A,
    FACE_2,
    FACE_3,
    FACE_4,
    FACE_5,
    FACE_6,
    FACE_7,
    FACE_8,
    FACE_9,
    FACE_0,
    FACE_J,
    FACE_Q,
    FACE_K,
};

template <typename T>
int GetIndexOf(const T &theArray, const char &C) {
    auto it = std::find(theArray.begin(), theArray.end(), C);

    if (it == theArray.end()) {
        return -1;
    }

    return std::distance(theArray.begin(), it);
}

class Card {
public:
    Card(char, char);

    char GetSuit() const;
    char GetFace() const;
    bool IsDarkCard() const;

    void Reveal();
    bool isRevealed() const;

    bool operator==(const Card &other);

private:
    char suit;
    char face;

    bool revealed;
};

std::ostream &operator<<(std::ostream &os, const Card &card);
