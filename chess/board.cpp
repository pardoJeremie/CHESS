//
//  board.cpp
//  chess
//
//  Created by pardo jérémie on 10/08/2023.
//

#include "board.hpp"

void Board::setPiecesList(std::vector<Piece*>* piecesList) {
    if (_piecesList)
        delete _piecesList;
    _piecesList = piecesList;
}

// return false when the piece was not added to the board
bool Board::addToPiecesList(Piece* piece) {
    if (!_piecesList)
        _piecesList = new std::vector<Piece*>();

    std::vector<Piece*>::iterator it;
    for(it = _piecesList->begin(); it != _piecesList->end(); it++)
        if( (*it)->getPosition() == piece->getPosition()) {
            return false; // a piece already exist at this position
        }

    _piecesList->push_back(piece); // add new piece
    return true;
}

// return false when the piece was not on the board
bool Board::deletInPiecesList(Piece* piece) {
    if (!_piecesList)
        return false;

    std::vector<Piece*>::iterator it;
    for(it = _piecesList->begin(); it != _piecesList->end(); it++)
        if( *it == piece) {
            it = _piecesList->erase(it); // delete piece
            return true;
        }

    return false;
}

bool Board::onValidePosition(const Point& point, bool teamColor) const {
   if (! _playZone->inZone(point))
       return false;

    std::vector<Piece*>::iterator it;
    for(it = _piecesList->begin(); it != _piecesList->end(); it++)
        if( (*it)->getPosition() == point) {
            if((*it)->getTeamColor() == teamColor)
                return false;
            return true;
        }

    return true;
}
