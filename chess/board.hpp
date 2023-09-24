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

enum EnumEndCondition : short { NO_END_COND, NO_END_COND_BUT_CHECK, STALEMATE, CHECKMAT};
class Board {
public:
    Board() {}
    Board(const Board&) = delete;
    Board(Board&&) = delete;
    Board& operator=( const Board&) = delete;
    Board& operator=(Board&&) = delete;
    ~Board() {}
    
    std::vector<Piece *>& getPiecesList() { return _piecesList; }
    bool addToPiecesList(Piece* piece);
    bool deletInPiecesList(Piece* piece);
    void resetPiecesList() { _piecesList.clear(); }
    // bool deletInPiecesList(Point point);
    
    bool onValidePosition(const Point& point, const bool teamColor, const bool enemy_necessary = false);
    bool getLastValidePositionPresPiece() {return lastValidePositionPresPiece;}
    bool onValidePosition_specialMove_pawn(const Point& point, const bool teamColor);
    bool KingPositionInCheck(const Point& point, const bool teamColor);
    void updatePiecesMoves();
    EnumEndCondition returnEndCondition(const bool teamColor);
    
    Piece* returnPiece( const char x, const char y, const bool teamColor);

private:
    bool lastValidePositionPresPiece = false;
    const RectangleZone _playZone = RectangleZone(8,8);
    std::vector<Piece *> _piecesList;
    
};
    
#endif /* board_hpp */
