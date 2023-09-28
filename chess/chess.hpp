//
//  chess.hpp
//  chess
//
//  Created by pardo jérémie on 18/09/2023.
//

#ifndef chess_hpp
#define chess_hpp

#include <stdio.h>
#include <string>
#include "board.hpp"

class Chess {
public:
    Chess(){}
    Chess(const Chess&) = delete;
    Chess(Chess&&) = delete;
    Chess& operator=( const Chess&) = delete;
    Chess& operator=(Chess&&) = delete;
    ~Chess(){}
    
    void startMainLoop();
//private:
    void startNewGame();
    void chargeGame(std::string path);
    bool playturn();
    void quit();
    
    Board _board;
    bool turn=true;
};

#endif /* chess_hpp */
