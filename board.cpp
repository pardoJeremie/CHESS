//
//  board.cpp
//  chess
//
//  Created by pardo jérémie on 10/08/2023.
//

#include <iostream>

#include "board.hpp"

// return false when the piece was not added to the board
bool Board::addToPiecesList(std::shared_ptr<Piece> piece) {
    for(std::vector<std::shared_ptr<Piece>>::iterator it = _piecesList.begin(); it != _piecesList.end(); it++)
        if( (*it)->getPosition() == piece->getPosition()) {
            return false; // a piece already exist at this position
        }

    _piecesList.push_back(piece); // add new piece*/
    return true;
}


bool Board::onValidePosition(const Point& point, const bool teamColor, const bool enemy_necessary) {
    if (! _playZone.inZone(point))
       return false;
    
    for(std::vector<std::shared_ptr<Piece>>::iterator it = _piecesList.begin(); it != _piecesList.end(); it++)
        if( (*it)->getPosition() == point) {
            if((*it)->getTeamColor() == teamColor)
                return false;
            lastValidePositionPresPiece = true;
            return true;
        }
    lastValidePositionPresPiece = false;
    return !enemy_necessary;
}

bool Board::onValidePosition(const Point& point) {
    if (! _playZone.inZone(point))
       return false;
    
    for(std::vector<std::shared_ptr<Piece>>::iterator it = _piecesList.begin(); it != _piecesList.end(); it++)
        if( (*it)->getPosition() == point)
            return false;

    lastValidePositionPresPiece = false; // no valid pos have the presence of a piece in this function.
    return true;
}

bool Board::onValidePosition_specialMove_pawn(const Point& point, const bool teamColor) {
    if (! _playZone.inZone(point))
       return false;
    
    for(std::vector<std::shared_ptr<Piece>>::iterator it = _piecesList.begin(); it != _piecesList.end(); it++)
        if( (*it)->getPosition() == point) {
            if((*it)->getTeamColor() == teamColor)
                return false;
            
            std::shared_ptr<Pawn> pawn = std::dynamic_pointer_cast<Pawn>(*it);
            if(pawn && pawn->_didSpecialMoveLastTurn)
                return true;
            
            return false;
        }
    return false;
}

// all opponent pieces except king piece must have all thier possible moves already calculated for this fonction to work correctly!!
bool Board::KingPositionInCheck(const Point& point,const bool teamColor) { // also used to test possible move of a king

    for(std::vector<std::shared_ptr<Piece>>::iterator it = _piecesList.begin(); it != _piecesList.end(); it++) {
        if((*it)->getTeamColor() != teamColor) {
            std::shared_ptr<King> king = std::dynamic_pointer_cast<King>(*it);
            if(king) { // A king cannot itself directly check the opposing king, since this would place the first king in check as well!
                if( (king->getPosition().getX() == point.getX() || king->getPosition().getX() == point.getX()+1 || king->getPosition().getX() == point.getX()-1) && (king->getPosition().getY() == point.getY() || king->getPosition().getY() == point.getY()+1 || king->getPosition().getY() == point.getY()-1))
                    return true;
            }
            else
                for(std::vector<std::pair <Point,EnumSpecialMove>>::const_iterator itMoves = (*it)->getPossibleMoves().begin();itMoves != (*it)->getPossibleMoves().end(); itMoves++){
                    if(itMoves->first == point)
                        return true; //check
            }
        }
    }
    return false;
}
void Board::updatePiecesMoves() {
    for(std::vector<std::shared_ptr<Piece>>::iterator it = _piecesList.begin(); it != _piecesList.end(); it++)
        (*it)->updatePossibleMove(*this);
}

void Board::pawnPromotion() {
    for(std::vector<std::shared_ptr<Piece>>::iterator it = _piecesList.begin(); it != _piecesList.end(); it++) {
        if((*it)->getPosition().getY() == ((*it)->getTeamColor()? 0 : 7)) {
            std::shared_ptr<Pawn> pawn = std::dynamic_pointer_cast<Pawn>(*it);
            if(pawn) {
                printBoard();
                char c;
                Point p = (*it)->getPosition();
                bool team = (*it)->getTeamColor();
                _piecesList.erase(it);
                while(true){
                    std::cout << "pawn Promotion to (r,n,b,q):" << std::endl;
                    std::cin >> c;
                    if(!std::cin.good())
                        c = 0;
                    std::cin.clear();
                    
                    if(c == 'R' || c == 'r') {
                        _piecesList.insert(_piecesList.begin(),std::make_shared<Rook>(p,team));
                        break;
                    }
                    else if(c == 'N' || c == 'n') {
                        _piecesList.insert(_piecesList.begin(),std::make_shared<Knight>(p,team));
                        break;
                    }
                    else if(c == 'B' || c == 'b'){
                            _piecesList.insert(_piecesList.begin(),std::make_shared<Bishop>(p,team));
      
                        break;
                    }
                    else if(c == 'Q' || c == 'q') {
                        _piecesList.insert(_piecesList.begin(),std::make_shared<Queen>(p,team));
                        break;
                    }
                    else
                        std::cout << "\nWrong user input." << std::endl;
                }
                return; // only one promotation is possible each turn!
            }
        }
    }
}

EnumEndCondition Board::returnEndCondition(const bool teamColor) {
    bool isempty = true, ischeck = false;
    for(std::vector<std::shared_ptr<Piece>>::iterator it = _piecesList.begin(); it != _piecesList.end(); it++)
        if((*it)->getTeamColor() == teamColor) {
            isempty = isempty && (*it)->getPossibleMoves().empty();

            std::shared_ptr<King> king = std::dynamic_pointer_cast<King>(*it);
            if(king && (ischeck = king->_ischeck))
                if(king->_ischeckTwoTurn)
                    return CHECKMAT;
        }
    
    if( isempty)
        return ischeck? CHECKMAT : STALEMATE;
    else if (ischeck)
        return NO_END_COND_BUT_CHECK;
    return NO_END_COND;
}


std::shared_ptr<Piece> Board::returnPiece(const char x,const char y, const bool teamColor) {
    
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
    
    for(std::vector<std::shared_ptr<Piece>>::iterator it = _piecesList.begin(); it != _piecesList.end(); it++)
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

void Board::printBoard() {
    
    char graphicboard[8][8] = {
        {[0 ... 7] = '.'},
        {[0 ... 7] = '.'},
        {[0 ... 7] = '.'},
        {[0 ... 7] = '.'},
        {[0 ... 7] = '.'},
        {[0 ... 7] = '.'},
        {[0 ... 7] = '.'},
        {[0 ... 7] = '.'}};
    
    for(std::vector<std::shared_ptr<Piece>>::iterator it = _piecesList.begin(); it != _piecesList.end(); it++) {
        std::shared_ptr<Pawn> pawn = std::dynamic_pointer_cast<Pawn>(*it);
        if(pawn) {
            graphicboard[(*it)->getPosition().getX()][(*it)->getPosition().getY()] = (*it)->getTeamColor()?'P':'p';
            continue;
        }
        
        std::shared_ptr<Knight> knight = std::dynamic_pointer_cast<Knight>(*it);
        if(knight) {
            graphicboard[(*it)->getPosition().getX()][(*it)->getPosition().getY()] = (*it)->getTeamColor()?'N':'n';
            continue;
        }
            
        std::shared_ptr<Bishop> bishop = std::dynamic_pointer_cast<Bishop>(*it);
        if(bishop) {
            graphicboard[(*it)->getPosition().getX()][(*it)->getPosition().getY()] = (*it)->getTeamColor()?'B':'b';
            continue;
        }
        
        std::shared_ptr<Rook> rook = std::dynamic_pointer_cast<Rook>(*it);
        if(rook) {
            graphicboard[(*it)->getPosition().getX()][(*it)->getPosition().getY()] = (*it)->getTeamColor()?'R':'r';
            continue;
        }
        
        std::shared_ptr<Queen> queen = std::dynamic_pointer_cast<Queen>(*it);
        if(queen) {
            graphicboard[(*it)->getPosition().getX()][(*it)->getPosition().getY()] = (*it)->getTeamColor()?'Q':'q';
            continue;
        }
            
        std::shared_ptr<King> king = std::dynamic_pointer_cast<King>(*it);
        if(king) {
            graphicboard[(*it)->getPosition().getX()][(*it)->getPosition().getY()] = (*it)->getTeamColor()?'K':'k';
            continue;
        }
    }
    
    std::cout << std::endl << "  A B C D E F G H" <<  std::endl;
    for(short i = 0; i<8; i++){
        std::cout << i+1;
        for(short j = 0; j<8; j++)
            std::cout <<' '<<graphicboard[j][i];
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
