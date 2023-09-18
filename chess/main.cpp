//
//  main.cpp
//  chess
//
//  Created by pardo jérémie on 10/08/2023.
//

#include <iostream>
#include "chess.hpp"

int main(int argc, const char * argv[]) {
    // insert code here...
    Chess game;
    game.startNewGame();
    game.printBoard();
    return 0;
}
