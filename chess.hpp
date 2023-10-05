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
    Chess() { menu(); }
    Chess(const Chess&) = delete;
    Chess(Chess&&) = delete;
    Chess& operator=( const Chess&) = delete;
    Chess& operator=(Chess&&) = delete;
    ~Chess() = default;
    
private:
    bool playturn();
    void startNewGame();
    bool loadGame();
    void saveGame();
    void deletSave();
    void menu();
    
    Board _board;
    bool _turn=true;
};

#endif /* chess_hpp */
