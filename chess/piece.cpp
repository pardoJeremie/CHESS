//
//  piece.cpp
//  chess
//
//  Created by pardo jérémie on 10/08/2023.
//

#include "piece.hpp"
#include <memory>
#include <functional>
#include "board.hpp"

void Pawn::updatePossibleMove(Board& board) {
    int8_t i = -1;
    bool precMovePossible = false;
    _possibleMove.clear();
    if(this->getTeamColor())
        i = 1;
    
    // straigh +1
    Point point(this->getPosition().getX(), this->getPosition().getY()+i);
    if(board.onValidePosition(point, this->getTeamColor())) {
        _possibleMove.push_back(std::make_pair(point,NA));
        precMovePossible = true;
    }
    
    // starting straigh +2
    if(precMovePossible && !this->getMoved()) { // cannot do straigh +2 if straigh +1 is not possible
        point.updatePosition(this->getPosition().getX(), this->getPosition().getY()+i*2);
        if(board.onValidePosition(point, this->getTeamColor()))
            _possibleMove.push_back(std::make_pair(point,PAWN));
    }
    
    //diagonal #1
    point.updatePosition(this->getPosition().getX()+i, this->getPosition().getY()+i);
    Point point2(this->getPosition().getX()+i, this->getPosition().getY());
    if(board.onValidePosition(point, this->getTeamColor(),true) || board.onValidePosition_specialMove_pawn(point2, this->getTeamColor()))// if the adversary pawn did move two cases last turn, you can eat him as if he add moved only a case
        _possibleMove.push_back(std::make_pair(point,NA));
    
    //diagonal #2
    point.updatePosition(this->getPosition().getX()-i, this->getPosition().getY()+i);
    point2.updatePosition(this->getPosition().getX()-i, this->getPosition().getY());
    if(board.onValidePosition(point, this->getTeamColor(),true)  || board.onValidePosition_specialMove_pawn(point2, this->getTeamColor()))// if the adversary pawn did move two cases last turn, you can eat him as if he add moved only a case
        _possibleMove.push_back(std::make_pair(point,NA));
}

void Knight::updatePossibleMove(Board& board) {
    _possibleMove.clear();
    
    Point point(this->getPosition().getX()-2, this->getPosition().getY()+1);
    if(board.onValidePosition(point, this->getTeamColor()))
        _possibleMove.push_back(std::make_pair(point,NA));
    point.updatePosition(this->getPosition().getX()-2, this->getPosition().getY()-1);
    if(board.onValidePosition(point, this->getTeamColor()))
        _possibleMove.push_back(std::make_pair(point,NA));
    
    point.updatePosition(this->getPosition().getX()+2, this->getPosition().getY()+1);
    if(board.onValidePosition(point, this->getTeamColor()))
        _possibleMove.push_back(std::make_pair(point,NA));
    point = Point(this->getPosition().getX()+2, this->getPosition().getY()- 1);
    if(board.onValidePosition(point, this->getTeamColor()))
        _possibleMove.push_back(std::make_pair(point,NA));
    
    point.updatePosition(this->getPosition().getX()+1, this->getPosition().getY()-2);
    if(board.onValidePosition(point, this->getTeamColor()))
        _possibleMove.push_back(std::make_pair(point,NA));
    point = Point(this->getPosition().getX()-1, this->getPosition().getY()-2);
    if(board.onValidePosition(point, this->getTeamColor()))
        _possibleMove.push_back(std::make_pair(point,NA));
    
    point.updatePosition(this->getPosition().getX()+1, this->getPosition().getY()+2);
    if(board.onValidePosition(point, this->getTeamColor()))
        _possibleMove.push_back(std::make_pair(point,NA));
    point = Point(this->getPosition().getX()-1, this->getPosition().getY()+2);
    if(board.onValidePosition(point, this->getTeamColor()))
        _possibleMove.push_back(std::make_pair(point,NA));
}

void Bishop::updatePossibleMove(Board& board) {
    bool precMovePossible = true;
    _possibleMove.clear();
    Point point;
    short i;
    
    for(i = 1; i < 8 && precMovePossible; i++) {
        point.updatePosition(this->getPosition().getX()+i, this->getPosition().getY()+i);
        if((precMovePossible = board.onValidePosition(point, this->getTeamColor())))
            _possibleMove.push_back(std::make_pair(point,NA));
    }
    
    precMovePossible = true;
    for(i = 1; i < 8 && precMovePossible; i++) {
        point.updatePosition(this->getPosition().getX()-i, this->getPosition().getY()+i);
        if((precMovePossible = board.onValidePosition(point, this->getTeamColor())))
            _possibleMove.push_back(std::make_pair(point,NA));
    }
    
    precMovePossible = true;
    for(i = 1; i < 8 && precMovePossible; i++) {
        point.updatePosition(this->getPosition().getX()-i, this->getPosition().getY()-i);
        if((precMovePossible = board.onValidePosition(point, this->getTeamColor())))
            _possibleMove.push_back(std::make_pair(point,NA));
    }
    
    precMovePossible = true;
    for(i = 1; i < 8 && precMovePossible; i++) {
        point.updatePosition(this->getPosition().getX()+i, this->getPosition().getY()-i);
        if((precMovePossible = board.onValidePosition(point, this->getTeamColor())))
            _possibleMove.push_back(std::make_pair(point,NA));
    }
}

void Rook::updatePossibleMove(Board& board) {
    bool precMovePossible = true;
    _possibleMove.clear();
    Point point;
    short i;
    
    for(i = 1; i < 8 && precMovePossible; i++) {
        point.updatePosition(this->getPosition().getX(), this->getPosition().getY()+i);
        if((precMovePossible = board.onValidePosition(point, this->getTeamColor())))
            _possibleMove.push_back(std::make_pair(point,NA));
    }
    
    precMovePossible = true;
    for(i = 1; i < 8 && precMovePossible; i++) {
        point.updatePosition(this->getPosition().getX(), this->getPosition().getY()-i);
        if((precMovePossible = board.onValidePosition(point, this->getTeamColor())))
            _possibleMove.push_back(std::make_pair(point,NA));
    }
    
    precMovePossible = true;
    for(i = 1; i < 8 && precMovePossible; i++) {
        point.updatePosition(this->getPosition().getX()+i, this->getPosition().getY());
        if((precMovePossible = board.onValidePosition(point, this->getTeamColor()))) {
            _possibleMove.push_back(std::make_pair(point,NA));

            if(!this->getMoved()) {
                if(i == 3 && this->getTeamColor())// big castle
                    _possibleMove.push_back(std::make_pair(point,BIGCASTLE));
                else if(!this->getMoved() && i == 2)// small castle
                    _possibleMove.push_back(std::make_pair(point,SMALLCASTLE));
            }
        }
    }
    
    precMovePossible = true;
    for(i = 1; i < 8 && precMovePossible; i++) {
        point.updatePosition(this->getPosition().getX()-i, this->getPosition().getY());
        if((precMovePossible = board.onValidePosition(point, this->getTeamColor()))) {
            _possibleMove.push_back(std::make_pair(point,NA));

            if(!this->getMoved()) {
                if(i == 3 && !this->getTeamColor())// big castle
                    _possibleMove.push_back(std::make_pair(point,BIGCASTLE));
                else if(!this->getMoved() && i == 2)// small castle
                    _possibleMove.push_back(std::make_pair(point,SMALLCASTLE));
            }
        }
    }
}

void Queen::updatePossibleMove(Board& board) {
    bool precMovePossible = true;
    _possibleMove.clear();
    Point point;
    short i;
    
    
    for(i = 1; i < 8 && precMovePossible; i++) {
        point.updatePosition(this->getPosition().getX()+i, this->getPosition().getY()+i);
        if((precMovePossible = board.onValidePosition(point, this->getTeamColor())))
            _possibleMove.push_back(std::make_pair(point,NA));
    }
    
    precMovePossible = true;
    for(i = 1; i < 8 && precMovePossible; i++) {
        point.updatePosition(this->getPosition().getX()-i, this->getPosition().getY()+i);
        if((precMovePossible = board.onValidePosition(point, this->getTeamColor())))
            _possibleMove.push_back(std::make_pair(point,NA));
    }
    
    precMovePossible = true;
    for(i = 1; i < 8 && precMovePossible; i++) {
        point.updatePosition(this->getPosition().getX()-i, this->getPosition().getY()-i);
        if((precMovePossible = board.onValidePosition(point, this->getTeamColor())))
            _possibleMove.push_back(std::make_pair(point,NA));
    }
    
    precMovePossible = true;
    for(i = 1; i < 8 && precMovePossible; i++) {
        point.updatePosition(this->getPosition().getX()+i, this->getPosition().getY()-i);
        if((precMovePossible = board.onValidePosition(point, this->getTeamColor())))
            _possibleMove.push_back(std::make_pair(point,NA));
    }
    
    for(i = 1; i < 8 && precMovePossible; i++) {
        point.updatePosition(this->getPosition().getX(), this->getPosition().getY()+i);
        if((precMovePossible = board.onValidePosition(point, this->getTeamColor())))
            _possibleMove.push_back(std::make_pair(point,NA));
    }
    
    precMovePossible = true;
    for(i = 1; i < 8 && precMovePossible; i++) {
        point.updatePosition(this->getPosition().getX(), this->getPosition().getY()-i);
        if((precMovePossible = board.onValidePosition(point, this->getTeamColor())))
            _possibleMove.push_back(std::make_pair(point,NA));
    }
    
    precMovePossible = true;
    for(i = 1; i < 8 && precMovePossible; i++) {
        point.updatePosition(this->getPosition().getX()+i, this->getPosition().getY());
        if((precMovePossible = board.onValidePosition(point, this->getTeamColor())))
            _possibleMove.push_back(std::make_pair(point,NA));
    }
    
    precMovePossible = true;
    for(i = 1; i < 8 && precMovePossible; i++) {
        point.updatePosition(this->getPosition().getX()-i, this->getPosition().getY());
        if((precMovePossible = board.onValidePosition(point, this->getTeamColor())))
            _possibleMove.push_back(std::make_pair(point,NA));
    }
}

void King::updatePossibleMove(Board& board) {
    _possibleMove.clear();
    
    Point point(this->getPosition().getX()+1, this->getPosition().getY()+1);
    if(board.onValidePosition(point, this->getTeamColor()))
        _possibleMove.push_back(std::make_pair(point,NA));

    point.updatePosition(this->getPosition().getX()-1, this->getPosition().getY()+1);
    if(board.onValidePosition(point, this->getTeamColor()))
        _possibleMove.push_back(std::make_pair(point,NA));
    
    point.updatePosition(this->getPosition().getX()+1, this->getPosition().getY()-1);
    if(board.onValidePosition(point, this->getTeamColor()))
        _possibleMove.push_back(std::make_pair(point,NA));
    
    point.updatePosition(this->getPosition().getX()-1, this->getPosition().getY()-1);
    if(board.onValidePosition(point, this->getTeamColor()))
        _possibleMove.push_back(std::make_pair(point,NA));
    
    point.updatePosition(this->getPosition().getX(), this->getPosition().getY()+1);
    if(board.onValidePosition(point, this->getTeamColor()))
        _possibleMove.push_back(std::make_pair(point,NA));

    point.updatePosition(this->getPosition().getX(), this->getPosition().getY()-1);
    if(board.onValidePosition(point, this->getTeamColor()))
        _possibleMove.push_back(std::make_pair(point,NA));
    
    point.updatePosition(this->getPosition().getX()+1, this->getPosition().getY());
    if(board.onValidePosition(point, this->getTeamColor()))
    {
        _possibleMove.push_back(std::make_pair(point,NA));
        if(this->getMoved()) {
            if(this->getTeamColor())
                _possibleMove.push_back(std::make_pair(point,SMALLCASTLE));
            else
                _possibleMove.push_back(std::make_pair(point,BIGCASTLE));
        }
    }
    
    point.updatePosition(this->getPosition().getX()-1, this->getPosition().getY());
    if(board.onValidePosition(point, this->getTeamColor()))
    {
        _possibleMove.push_back(std::make_pair(point,NA));
        if(this->getMoved()) {
            if(this->getTeamColor())
                _possibleMove.push_back(std::make_pair(point,BIGCASTLE));
            else
                _possibleMove.push_back(std::make_pair(point,SMALLCASTLE));
        }
    }
}
