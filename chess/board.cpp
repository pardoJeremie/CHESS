//
//  board.cpp
//  chess
//
//  Created by pardo jérémie on 10/08/2023.
//

#include <iostream>

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

bool Board::onValidePosition(const Point& point, const bool teamColor, const bool enemy_necessary) {
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

bool Board::onValidePosition_specialMove_pawn(const Point& point, const bool teamColor) {
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

// all opponent pieces except king piece must have all thier possible moves already calculated for this fonction to work correctly!!
bool Board::KingPositionInCheck(const Point& point,const bool teamColor) { // also used to test possible move of a king

    std::vector<Piece *>::iterator it;
    for(it = _piecesList.begin(); it != _piecesList.end(); it++) {
        if((*it)->getTeamColor() != teamColor) {
            King* king = dynamic_cast<King*>(*it);
            if(king) { // have sence if testing for a possible king move
                if( (king->getPosition().getX() == point.getX() || king->getPosition().getX() == point.getX()+1 || king->getPosition().getX() == point.getX()-1) && (king->getPosition().getY() == point.getY() || king->getPosition().getY() == point.getY()+1 || king->getPosition().getY() == point.getY()-1))
                    return true; //A king cannot itself directly check the opposing king, since this would place the first king in check as well!
            }
            else {
                std::vector<std::pair <Point,EnumSpecialMove>>::const_iterator itMoves;
                for(itMoves = (*it)->getPossibleMoves().begin();itMoves != (*it)->getPossibleMoves().end(); itMoves++){
                    if(itMoves->first == point)
                        return true; //check
                }
            }
        }
    }
    return false;
}
void Board::updatePiecesMoves() {
    std::vector<Piece *>::iterator it;
    for(it = _piecesList.begin(); it != _piecesList.end(); it++) {
        (*it)->updatePossibleMove(*this);
    }
}

Piece* Board::returnPiece(const char x,const char y, const bool teamColor) {
    
    short varx = -1, vary = -1;
    
    if(x >= 'A' && x <= 'H') {
        varx = x -'A';
    }
    else if(x >= 'a' && x <='h') {
        varx = x -'a';
    }
    else if(x >= '1' && x <='8') {
        vary = x -'1';
    }
    
    if(y >= 'A' && y <= 'H') {
        varx = y -'A';
    }
    else if(y >= 'a' && y <='h') {
        varx = y -'a';
    }
    else if(y >= '1' && y <='8') {
        vary = y -'1';
    }
    
    if(varx == -1 || vary == -1) {
        std::cout << "Wrong user input" << std::endl;
        return nullptr;
    }
    
    std::vector<Piece *>::iterator it;
    for(it = _piecesList.begin(); it != _piecesList.end(); it++)
        if((*it)->getTeamColor() == teamColor) {
            if((*it)->getPosition().getX() == varx && (*it)->getPosition().getY() == vary) {
                if((*it)->getPossibleMoves().empty()) {
                    std::cout << "The selected " << (*it)->getName() << " cannot move! Choose another piece." << std::endl;
                    return nullptr;
                }
                return (*it);
            }
        }
    return nullptr;
}
