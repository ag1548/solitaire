#pragma once

#include <algorithm>
#include <array>
#include <iostream>

const std::array<char, 4> Suits = {
    'S',
    'C',
    'H',
    'D',
};
int GetIndexOfSuit(char s);

const std::array<char, 13> Faces = {
    'A', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'J', 'Q', 'K',
};
int GetIndexOfFace(char f);

class Card {
public:
  Card(char, char);

  char GetSuit() const;
  char GetFace() const;

  void Reveal();
  bool isRevealed() const;

  bool operator==(const Card& other);

private:
  char suit;
  char face;

  bool revealed;
};

std::ostream &operator<<(std::ostream &os, const Card &card);
