//
//  piece.cpp
//  chess
//
//  Created by pardo jérémie on 10/08/2023.
//

#include <iostream>
#include <memory>
#include <functional>

#include "piece.hpp"
#include "board.hpp"

bool Piece::applyMove(const char x, const char y, Board& board) {
    short varx = -1, vary = -1;
    bool possible = false;
    // board is her for castle special move (two pieces move) and deleting eaten pieces.
    if(x == 'B' && y == 'C') { // big castle
        std::vector<std::pair <Point,EnumSpecialMove>>::iterator it;
        for(it = _possibleMove.begin(); it !=_possibleMove.end(); it ++) {
            if((*it).second == BIGCASTLE) { // if true, the piece is a king or a rook
               
                King* king = dynamic_cast<King*>(this); // if null the opposite piece is a king
                Rook* rook = dynamic_cast<Rook*>(this); // if null the opposite piece is a rook
                
                //look for the opposite piece
                std::vector<Piece *>::iterator itpieces;
                for(itpieces = board.getPiecesList().begin(); itpieces != board.getPiecesList().end(); itpieces++)
                    if((*itpieces)->getTeamColor() == getTeamColor()) {
                        if(!king)
                            king = dynamic_cast<King*>(*itpieces);
                        else if (!rook)
                            rook = dynamic_cast<Rook*>(*itpieces);
                        
                        if(king && rook) { // the rook/king pair is found
                            std::vector<std::pair <Point,EnumSpecialMove>>::const_iterator itpiecePossibleMoves;
                            for(itpiecePossibleMoves = (*itpieces)->getPossibleMoves().begin(); itpiecePossibleMoves !=(*itpieces)->getPossibleMoves().end(); itpiecePossibleMoves ++)
                                if((*itpiecePossibleMoves).second == BIGCASTLE) {
                                    setPosition((*it).first);
                                    (*itpieces)->setPosition((*itpiecePossibleMoves).first);
                                    return true;
                                }
                        }
                    }
            }
        }
        std::cout << "\nMove not possible." << std::endl;
        return false;
    }
    else if(x == 'S' && y == 'C') { // small castle
        std::vector<std::pair <Point,EnumSpecialMove>>::iterator it;
        for(it = _possibleMove.begin(); it !=_possibleMove.end(); it ++) {
            if((*it).second == SMALLCASTLE) {
                // if true, the piece is a king or a rook
                   
                    King* king = dynamic_cast<King*>(this); // if null the opposite piece is a king
                    Rook* rook = dynamic_cast<Rook*>(this); // if null the opposite piece is a rook
                    
                    //look for the opposite piece
                    std::vector<Piece *>::iterator itpieces;
                    for(itpieces = board.getPiecesList().begin(); itpieces != board.getPiecesList().end(); itpieces++)
                        if((*itpieces)->getTeamColor() == getTeamColor()) {
                            if(!king)
                                king = dynamic_cast<King*>(*itpieces);
                            else if (!rook)
                                rook = dynamic_cast<Rook*>(*itpieces);
                            
                            if(king && rook) { // the rook/king pair is found
                                std::vector<std::pair <Point,EnumSpecialMove>>::const_iterator itpiecePossibleMoves;
                                for(itpiecePossibleMoves = (*itpieces)->getPossibleMoves().begin(); itpiecePossibleMoves !=(*itpieces)->getPossibleMoves().end(); itpiecePossibleMoves ++)
                                    if((*itpiecePossibleMoves).second == SMALLCASTLE) {
                                        setPosition((*it).first);
                                        (*itpieces)->setPosition((*itpiecePossibleMoves).first);
                                        return true;
                                    }
                            }
                        }
            }
        }
        std::cout << "\nMove not possible." << std::endl;
        return false;
    }
    else {
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
            std::cout << "\nWrong user input." << std::endl;
            return false;
        }
        
        Pawn* pawn = dynamic_cast<Pawn*>(this);
        if(pawn)
            pawn->_didSpecialMoveLastTurn = false;
        Point point(varx, vary);
        
        std::vector<std::pair <Point,EnumSpecialMove>>::iterator it;
        for(it = _possibleMove.begin(); it !=_possibleMove.end(); it ++) {
            if((*it).second == NA && (*it).first.getX() == varx && (*it).first.getY() == vary) {
                setPosition(point);
                possible = true;
                break;
            }
            else if((*it).second == PAWNSPECIAL && (*it).first.getX() == varx && (*it).first.getY() == vary) {
                setPosition(point);
                pawn->_didSpecialMoveLastTurn = true; // pawn cannot be null
                possible = true;
                break;
            }
            else if((*it).second == PAWNDIAGONAL && (*it).first.getX() == varx && (*it).first.getY() == vary) {
                setPosition(point);
                
                // case where a pawn eat diagonaly another pawn that did its special move
                std::vector<Piece *>::iterator itpieces;
                for(itpieces = board.getPiecesList().begin(); itpieces != board.getPiecesList().end(); itpieces++)
                    if((*itpieces)->getTeamColor() != getTeamColor() && (*itpieces)->getPosition().getY() == point.getY() + (_teamColor? 1 : -1) && (*itpieces)->getPosition().getX() == point.getX()) {
                        Pawn* pawntodelete = dynamic_cast<Pawn*>(*itpieces);

                        if(pawntodelete && pawntodelete->_didSpecialMoveLastTurn) {
                            board.getPiecesList().erase(itpieces);
                            return true;
                        }
                    }
                possible = true;
                break;
            }
        }
        
        if(possible) {
            std::vector<Piece *>::iterator itpieces;
            for(itpieces = board.getPiecesList().begin(); itpieces != board.getPiecesList().end(); itpieces++)
                if((*itpieces)->getTeamColor() != getTeamColor() && (*itpieces)->getPosition() == point) {
                    board.getPiecesList().erase(itpieces);
                    break;
                }
            return true;
        }
        else {
            std::cout << "\nMove not possible." << std::endl;
            return false;
        }
    }
}

void Pawn::updatePossibleMove(Board& board) {
    short i = -1;
    bool precMovePossible = false;
    _possibleMove.clear();
    if(!getTeamColor())
        i = 1;
    
    // straigh +1 attention, pawn cannot eat piece when moving forward
    Point point(getPosition().getX(), getPosition().getY()+i);
    if((precMovePossible = board.onValidePosition(point)))
        _possibleMove.push_back(std::make_pair(point,NA));

    // starting straigh +2 attention, pawn cannot eat piece when moving forward 
    if(precMovePossible && !board.getLastValidePositionPresPiece() && !getMoved()) { // cannot do straigh +2 if straigh +1 is not possible
        point.updatePosition(getPosition().getX(), getPosition().getY()+i*2);
        if(board.onValidePosition(point))
            _possibleMove.push_back(std::make_pair(point,PAWNSPECIAL));
    }
    
    //diagonal #1
    point.updatePosition(getPosition().getX()+i, getPosition().getY()+i);
    Point point2(getPosition().getX()+i, getPosition().getY());
    if(board.onValidePosition(point, getTeamColor(),true) || board.onValidePosition_specialMove_pawn(point2, getTeamColor()))// if the adversary pawn did move two cases last turn, you can eat him as if he add moved only a case
        _possibleMove.push_back(std::make_pair(point,PAWNDIAGONAL));
    
    //diagonal #2
    point.updatePosition(getPosition().getX()-i, getPosition().getY()+i);
    point2.updatePosition(getPosition().getX()-i, getPosition().getY());
    if(board.onValidePosition(point, getTeamColor(),true)  || board.onValidePosition_specialMove_pawn(point2, getTeamColor()))// if the adversary pawn did move two cases last turn, you can eat him as if he add moved only a case
        _possibleMove.push_back(std::make_pair(point,PAWNDIAGONAL));
}

void Knight::updatePossibleMove(Board& board) {
    _possibleMove.clear();
    
    Point point(getPosition().getX()-2, getPosition().getY()+1);
    if(board.onValidePosition(point, getTeamColor()))
        _possibleMove.push_back(std::make_pair(point,NA));
    point.updatePosition(getPosition().getX()-2, getPosition().getY()-1);
    if(board.onValidePosition(point, getTeamColor()))
        _possibleMove.push_back(std::make_pair(point,NA));
    
    point.updatePosition(getPosition().getX()+2, getPosition().getY()+1);
    if(board.onValidePosition(point, getTeamColor()))
        _possibleMove.push_back(std::make_pair(point,NA));
    point = Point(getPosition().getX()+2, getPosition().getY()- 1);
    if(board.onValidePosition(point, getTeamColor()))
        _possibleMove.push_back(std::make_pair(point,NA));
    
    point.updatePosition(getPosition().getX()+1, getPosition().getY()-2);
    if(board.onValidePosition(point, getTeamColor()))
        _possibleMove.push_back(std::make_pair(point,NA));
    point = Point(getPosition().getX()-1, getPosition().getY()-2);
    if(board.onValidePosition(point, getTeamColor()))
        _possibleMove.push_back(std::make_pair(point,NA));
    
    point.updatePosition(getPosition().getX()+1, getPosition().getY()+2);
    if(board.onValidePosition(point, getTeamColor()))
        _possibleMove.push_back(std::make_pair(point,NA));
    point = Point(getPosition().getX()-1, getPosition().getY()+2);
    if(board.onValidePosition(point, getTeamColor()))
        _possibleMove.push_back(std::make_pair(point,NA));
}

void Bishop::updatePossibleMove(Board& board) {
    bool precMovePossible = true, presPiece = false;
    _possibleMove.clear();
    Point point;
    short i;
    
    for(i = 1; i < 8 && precMovePossible && !presPiece; i++) {
        point.updatePosition(getPosition().getX()+i, getPosition().getY()+i);
        if((precMovePossible = board.onValidePosition(point, getTeamColor()))) {
            _possibleMove.push_back(std::make_pair(point,NA));
            presPiece = board.getLastValidePositionPresPiece();
        }
    }
    
    precMovePossible = true;
    presPiece = false;
    for(i = 1; i < 8 && precMovePossible && !presPiece; i++) {
        point.updatePosition(getPosition().getX()-i, getPosition().getY()+i);
        if((precMovePossible = board.onValidePosition(point, getTeamColor()))) {
            _possibleMove.push_back(std::make_pair(point,NA));
            presPiece = board.getLastValidePositionPresPiece();
        }
    }
    
    precMovePossible = true;
    presPiece = false;
    for(i = 1; i < 8 && precMovePossible && !presPiece; i++) {
        point.updatePosition(getPosition().getX()-i, getPosition().getY()-i);
        if((precMovePossible = board.onValidePosition(point, getTeamColor()))) {
            _possibleMove.push_back(std::make_pair(point,NA));
            presPiece = board.getLastValidePositionPresPiece();
        }
    }
    
    precMovePossible = true;
    presPiece = false;
    for(i = 1; i < 8 && precMovePossible && !presPiece; i++) {
        point.updatePosition(getPosition().getX()+i, getPosition().getY()-i);
        if((precMovePossible = board.onValidePosition(point, getTeamColor()))) {
            _possibleMove.push_back(std::make_pair(point,NA));
            presPiece = board.getLastValidePositionPresPiece();
        }
    }
}

void Rook::updatePossibleMove(Board& board) {
    bool precMovePossible = true, presPiece = false;
    _possibleMove.clear();
    Point point;
    short i;
    
    for(i = 1; i < 8 && precMovePossible && !presPiece; i++) {
        point.updatePosition(getPosition().getX(), getPosition().getY()+i);
        if((precMovePossible = board.onValidePosition(point, getTeamColor()))) {
            _possibleMove.push_back(std::make_pair(point,NA));
            presPiece = board.getLastValidePositionPresPiece();
        }
    }
    
    precMovePossible = true;
    presPiece = false;
    for(i = 1; i < 8 && precMovePossible && !presPiece; i++) {
        point.updatePosition(getPosition().getX(), getPosition().getY()-i);
        if((precMovePossible = board.onValidePosition(point, getTeamColor()))) {
            _possibleMove.push_back(std::make_pair(point,NA));
            presPiece = board.getLastValidePositionPresPiece();
        }
    }
    
    precMovePossible = true;
    presPiece = false;
    for(i = 1; i < 8 && precMovePossible && !presPiece; i++) {
        point.updatePosition(getPosition().getX()+i, getPosition().getY());
        if((precMovePossible = board.onValidePosition(point, getTeamColor()))) {
            _possibleMove.push_back(std::make_pair(point,NA));
            presPiece = board.getLastValidePositionPresPiece();
            
            if(!getMoved()&& i == 3 )// big castle
                    _possibleMove.push_back(std::make_pair(point,BIGCASTLE));
        }
    }
    
    precMovePossible = true;
    presPiece = false;
    for(i = 1; i < 8 && precMovePossible && !presPiece; i++) {
        point.updatePosition(getPosition().getX()-i, getPosition().getY());
        if((precMovePossible = board.onValidePosition(point, getTeamColor()))) {
            _possibleMove.push_back(std::make_pair(point,NA));
            presPiece = board.getLastValidePositionPresPiece();
            
            if(!getMoved() && i == 2)// small castle
                    _possibleMove.push_back(std::make_pair(point,SMALLCASTLE));
        }
    }
}

void Queen::updatePossibleMove(Board& board) {
    bool precMovePossible = true, presPiece = false;
    _possibleMove.clear();
    Point point;
    short i;
    
    for(i = 1; i < 8 && precMovePossible && !presPiece; i++) {
        point.updatePosition(getPosition().getX()+i, getPosition().getY()+i);
        if((precMovePossible = board.onValidePosition(point, getTeamColor()))) {
            _possibleMove.push_back(std::make_pair(point,NA));
            presPiece = board.getLastValidePositionPresPiece();
        }
    }
    
    precMovePossible = true;
    presPiece = false;
    for(i = 1; i < 8 && precMovePossible && !presPiece; i++) {
        point.updatePosition(getPosition().getX()-i, getPosition().getY()+i);
        if(!presPiece && (precMovePossible = board.onValidePosition(point, getTeamColor()))) {
            _possibleMove.push_back(std::make_pair(point,NA));
            presPiece = board.getLastValidePositionPresPiece();
        }
    }
    
    precMovePossible = true;
    presPiece = false;
    for(i = 1; i < 8 && precMovePossible && !presPiece; i++) {
        point.updatePosition(getPosition().getX()-i, getPosition().getY()-i);
        if((precMovePossible = board.onValidePosition(point, getTeamColor()))) {
            _possibleMove.push_back(std::make_pair(point,NA));
            presPiece = board.getLastValidePositionPresPiece();
        }
    }
    
    precMovePossible = true;
    presPiece = false;
    for(i = 1; i < 8 && precMovePossible && !presPiece; i++) {
        point.updatePosition(getPosition().getX()+i, getPosition().getY()-i);
        if((precMovePossible = board.onValidePosition(point, getTeamColor()))) {
            _possibleMove.push_back(std::make_pair(point,NA));
            presPiece = board.getLastValidePositionPresPiece();
        }
    }
    
    precMovePossible = true;
    presPiece = false;
    for(i = 1; i < 8 && precMovePossible  && !presPiece; i++) {
        point.updatePosition(getPosition().getX(), getPosition().getY()+i);
        if((precMovePossible = board.onValidePosition(point, getTeamColor()))) {
            _possibleMove.push_back(std::make_pair(point,NA));
            presPiece = board.getLastValidePositionPresPiece();
        }
    }
    
    precMovePossible = true;
    presPiece = false;
    for(i = 1; i < 8 && precMovePossible && !presPiece; i++) {
        point.updatePosition(getPosition().getX(), getPosition().getY()-i);
        if((precMovePossible = board.onValidePosition(point, getTeamColor()))) {
            _possibleMove.push_back(std::make_pair(point,NA));
            presPiece = board.getLastValidePositionPresPiece();
        }
    }
    
    precMovePossible = true;
    presPiece = false;
    for(i = 1; i < 8 && precMovePossible && !presPiece; i++) {
        point.updatePosition(getPosition().getX()+i, getPosition().getY());
        if((precMovePossible = board.onValidePosition(point, getTeamColor()))) {
            _possibleMove.push_back(std::make_pair(point,NA));
            presPiece = board.getLastValidePositionPresPiece();
        }
    }
    
    precMovePossible = true;
    presPiece = false;
    for(i = 1; i < 8 && precMovePossible && !presPiece; i++) {
        point.updatePosition(getPosition().getX()-i, getPosition().getY());
        if((precMovePossible = board.onValidePosition(point, getTeamColor()))) {
            _possibleMove.push_back(std::make_pair(point,NA));
            presPiece = board.getLastValidePositionPresPiece();
        }
    }
}


/* RULE :
*  Under the standard rules of chess, a player may not make any move that places or leaves their king in check.
*  A player may move the king, capture the threatening piece, or block the check with another piece
*  A king cannot itself directly check the opposing king, since this would place the first king in check as well!*/

// Because of the us of board.KingPositionInCheck( ... ), all opponent pieces except king piece must have all thier possible moves already calculated for this fonction to work correctly!!
void King::updatePossibleMove(Board& board) {
    _possibleMove.clear();
    bool precMovePossible = false, ischecklasturn = _ischeck;
    _ischeckTwoTurn = (_ischeck = board.KingPositionInCheck(getPosition(),getTeamColor())) && ischecklasturn; // see if king is in check for two turn and update _ischeck value
    
    
    Point point(getPosition().getX()+1, getPosition().getY()+1);
    if(! board.KingPositionInCheck(point, getTeamColor()) && board.onValidePosition(point, getTeamColor()))
        _possibleMove.push_back(std::make_pair(point,NA));

    point.updatePosition(getPosition().getX()-1, getPosition().getY()+1);
    if(! board.KingPositionInCheck(point, getTeamColor()) && board.onValidePosition(point, getTeamColor()))
        _possibleMove.push_back(std::make_pair(point,NA));
    
    point.updatePosition(getPosition().getX()+1, getPosition().getY()-1);
    if(! board.KingPositionInCheck(point, getTeamColor()) && board.onValidePosition(point, getTeamColor()))
        _possibleMove.push_back(std::make_pair(point,NA));
    
    point.updatePosition(getPosition().getX()-1, getPosition().getY()-1);
    if(! board.KingPositionInCheck(point, getTeamColor()) && board.onValidePosition(point, getTeamColor()))
        _possibleMove.push_back(std::make_pair(point,NA));
    
    point.updatePosition(getPosition().getX(), getPosition().getY()+1);
    if(! board.KingPositionInCheck(point, getTeamColor()) && board.onValidePosition(point, getTeamColor()))
        _possibleMove.push_back(std::make_pair(point,NA));

    point.updatePosition(getPosition().getX(), getPosition().getY()-1);
    if(! board.KingPositionInCheck(point, getTeamColor()) && board.onValidePosition(point, getTeamColor()))
        _possibleMove.push_back(std::make_pair(point,NA));
    
    point.updatePosition(getPosition().getX()+1, getPosition().getY());
    if(! board.KingPositionInCheck(point, getTeamColor()) && (precMovePossible = board.onValidePosition(point, getTeamColor())))
        _possibleMove.push_back(std::make_pair(point,NA));
    
    point.updatePosition(getPosition().getX()+2, getPosition().getY());
    if(!getMoved() && !_ischeck && precMovePossible && ! board.KingPositionInCheck(point, getTeamColor())  && board.onValidePosition(point, getTeamColor()))
                _possibleMove.push_back(std::make_pair(point,SMALLCASTLE));
    
    precMovePossible = false;
    point.updatePosition(getPosition().getX()-1, getPosition().getY());
    if(! board.KingPositionInCheck(point, getTeamColor()) && (precMovePossible = board.onValidePosition(point, getTeamColor())))
        _possibleMove.push_back(std::make_pair(point,NA));

    point.updatePosition(getPosition().getX()-2, getPosition().getY());
    if(!getMoved() && !_ischeck && precMovePossible && ! board.KingPositionInCheck(point, getTeamColor())  && board.onValidePosition(point, getTeamColor()))
                _possibleMove.push_back(std::make_pair(point,BIGCASTLE));
}
