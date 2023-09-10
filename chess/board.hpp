//
//  board.hpp
//  chess
//
//  Created by pardo jérémie on 10/08/2023.
//

#ifndef board_hpp
#define board_hpp

#include <stdio.h>
#include "basicGeometric.hpp"
#include <memory>
#include "piece.hpp"

class Board {
public:
    Board() {}
    Board(const Board&) = delete;
    Board(Board&&) = delete;
    Board& operator=( const Board&) = delete;
    Board& operator=(Board&&) = delete;
    ~Board() {}
    
    std::vector<Piece *>& getPiecesList() { return _piecesList; }
    bool addToPiecesList(Piece piece);
    bool deletInPiecesList(Piece piece);
    
    bool onValidePosition(const Point& point, bool teamColor, bool enemy_necessary = false);
    
private:
    const RectangleZone _playZone = RectangleZone(8,8);
    std::vector<Piece *> _piecesList;
    
};
    
#endif /* board_hpp */
