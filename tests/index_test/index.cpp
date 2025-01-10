#include <iostream>

#include "card.h"

int main() {
    int x = GetIndexOfSuit('D');
    std::cout << "x: " << x << std::endl;
    x = GetIndexOfSuit('w');
    std::cout << "x: " << x << std::endl;

    int y = GetIndexOfFace('Q');
    std::cout << "y: " << y << std::endl;
    y = GetIndexOfFace('z');
    std::cout << "y: " << y << std::endl;

    return 0;
}