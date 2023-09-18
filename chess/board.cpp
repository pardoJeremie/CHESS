//
//  board.cpp
//  chess
//
//  Created by pardo jérémie on 10/08/2023.
//

#include "board.hpp"

// return false when the piece was not added to the board
bool Board::addToPiecesList(Piece* piece) {
    std::vector<Piece *>::iterator it;
    for(it = _piecesList.begin(); it != _piecesList.end(); it++)
        if( (*it)->getPosition() == piece->getPosition()) {
            return false; // a piece already exist at this position
        }

    _piecesList.push_back(piece); // add new piece*/
    return true;
}

// return false when the piece was not on the board
bool Board::deletInPiecesList(Piece* piece) {
    std::vector<Piece * >::iterator it;
    for(it = _piecesList.begin(); it != _piecesList.end(); it++)
        if( *it == piece) {
            it = _piecesList.erase(it); // delete piece
            return true;
        }

    return false;
}

bool Board::onValidePosition(const Point& point, bool teamColor, bool enemy_necessary) {
    if (! _playZone.inZone(point))
       return false;
    
    std::vector<Piece *>::iterator it;
    for(it = _piecesList.begin(); it != _piecesList.end(); it++)
        if( (*it)->getPosition() == point) {
            if((*it)->getTeamColor() == teamColor)
                return false;
            return true;
        }
    return !enemy_necessary;
}

bool Board::onValidePosition_specialMove_pawn(const Point& point, bool teamColor) {
    if (! _playZone.inZone(point))
       return false;
    
    std::vector<Piece *>::iterator it;
    for(it = _piecesList.begin(); it != _piecesList.end(); it++)
        if( (*it)->getPosition() == point) {
            if((*it)->getTeamColor() == teamColor)
                return false;
            
            Pawn* pawn = dynamic_cast<Pawn*>(*it);
            if(pawn && pawn->_didSpecialMoveLastTurn)
                return true;
            
            return false;
        }
    return false;
}

