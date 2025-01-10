#include <iostream>

#include "common.h"

void GameAbort(std::string msg) {
    std::cerr << "Game Aborted" << std::endl
              << "  - " << msg << std::endl;
    
    exit(1);
}