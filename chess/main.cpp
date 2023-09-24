//
//  main.cpp
//  chess
//
//  Created by pardo jérémie on 10/08/2023.
//

#include <iostream>

#include "chess.hpp"

int main(int argc, const char * argv[]) {
    /* not implemented :
     - Threefold Repetition
     - checkmat because the program calculated that no movement could alter the check
     */
    Chess game;
    game.startNewGame();
    while(game.playturn());
    return 0;
}
