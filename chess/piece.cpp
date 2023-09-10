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

/*
 * PAWN MOVES
 */

void Pawn::updatePossibleMove(Board& board) {
    
    //TODO : delete possible move list.
    
    int8_t i = -1;
    bool precMovePossible;
    
    
    if(this->getTeamColor())
        i= 1;
    
    // straigh +1
    Point* point = new Point(this->getPosition().getX(), this->getPosition().getY() + i);
    
    /*if(board.onValidePosition(*point, this->getTeamColor())) {
        _possibleMove.push_back(point);
        precMovePossible = true;
    }
    else {
        precMovePossible = false;
        delete point;
    }
    
    
    // starting straigh +2
    if(!this->getMoved() && precMovePossible) {
        
        Point* point = new Point(this->getPosition().getX(), this->getPosition().getY() + i*2);

        if(board.onValidePosition(*point, this->getTeamColor())) {
            _possibleMove.push_back(point);
        }
        else {
            delete point;
        }
    }*/
    
    //diagonal #1
    
    //diagonal #2
    
}

/*void f(){

    /*
     * PAWN MOVES
    
    std::vector<std::function<std::unique_ptr<Point>(Piece&/*, int)>>  pawnMoves;
    // straigh +1
    pawnMoves.push_back(
    [](Piece& p/*,Board &b) {
        std::unique_ptr<Point> point( new Point(p.getPosition().getX(),p.getTeamColor()?
                                  ( p.getPosition().getY() + 1 ): (p.getPosition().getY() - 1)));
        if(false)// !Board.validstraightmove(point,p.getTeamColor())
            point = nullptr;
        return point;});
    
    // starting straigh +2
    pawnMoves.push_back([](Piece &p/*,Board &b) {
        std::unique_ptr<Point> point( new Point(p.getPosition().getX(),p.getTeamColor()?
                                                ( p.getPosition().getY() + 2 ): (p.getPosition().getY() - 2)));
        if(false)// p.getMoved() /*already moved || !Board.validstraightmove(point,p.getTeamColor())
            point=nullptr;
        return point;});
    
    //diagonal #1
    pawnMoves.push_back([](Piece &p/*,Board &b) {
        std::unique_ptr<Point> point( p.getTeamColor()?
                                     new Point(p.getPosition().getX() + 1 , p.getPosition().getY() + 1):
                                     new Point(p.getPosition().getX() + 1 , p.getPosition().getY() -1 ));
        if(false)// !Board.validEatMove(p.getTeamColor())
            point=nullptr;
        
        return point;});
    
    //diagonal #2
    pawnMoves.push_back([](Piece &p/*,Board &b) {
        std::unique_ptr<Point> point( p.getTeamColor()?
                                     new Point(p.getPosition().getX() - 1 , p.getPosition().getY() + 1):
                                     new Point(p.getPosition().getX() - 1 , p.getPosition().getY() -1 ));
        if(false)// !Board.validEatMove(p.getTeamColor())
            point=nullptr;
        
        return point;});
    
    /*
     * KNIGHTS MOVES
     
    std::vector<std::function<std::unique_ptr<Point>(Piece&/*, int)>>  knigthsMoves;
    
    int8_t x,y;
    std::tuple<int8_t, int8_t> pos[8]  = {
        {-2, -1},{-2, 1},
        {2, -1},{2, 1},
        {-1, -2},{1, -2},
        {-1, 2},{1, 2}};
    
    /* the variable x and y are captured by value in the lambda function
     see the following link for more info: https://learn.microsoft.com/en-us/cpp/cpp/lambda-expressions-in-cpp?view=msvc-170
     

    for(uint8_t i=0; i<8; i++)
    {
        x = std::get<0>(pos[i]);
        y = std::get<1>(pos[i]);;
        
        knigthsMoves.push_back([=](Piece &p/*,Board &b) {
            std::unique_ptr<Point> point(new Point(p.getPosition().getX() + x, p.getPosition().getY() + y));
            if(false)// !Board.validJumpMove(p.getTeamColor())
                point=nullptr;
            return point;});
    }
    
    /*
     * BISHOPS MOVES
     
    std::vector<std::function<std::unique_ptr<Point>(Piece&/*, int)>>  bishopsMoves;
    
    for(int8_t i=-7; i<8; i++)
    {
        if(i == 0)
            continue;
        
        bishopsMoves.push_back([=](Piece &p/*,Board &b) {
            std::unique_ptr<Point> point(new Point(p.getPosition().getX() + i, p.getPosition().getY() + i));
            if(false)// !Board.validstraightmove(p.getTeamColor())
                point=nullptr;
            return point;});
        
        bishopsMoves.push_back([=](Piece &p/*,Board &b) {
            std::unique_ptr<Point> point(new Point(p.getPosition().getX() + i, p.getPosition().getY() - i));
            if(false)// !Board.validstraightmove(p.getTeamColor())
                point=nullptr;
            return point;});
    }
    
    /*
     * ROOKS MOVES
     
    std::vector<std::function<std::unique_ptr<Point>(Piece&/*, int*>>  rooksMoves;
    
    for(int8_t i=-7; i<8; i++)
    {
        if(i == 0)
            continue;
        
        rooksMoves.push_back([=](Piece &p/*,Board &b) {
            std::unique_ptr<Point> point(new Point(p.getPosition().getX() + i, p.getPosition().getY()));
            if(false)// !Board.validstraightmove(p.getTeamColor())
                point=nullptr;
            return point;});
        
        rooksMoves.push_back([=](Piece &p/*,Board &b) {
            std::unique_ptr<Point> point(new Point(p.getPosition().getX(), p.getPosition().getY() + i));
            if(false)// !Board.validstraightmove(p.getTeamColor())
                point=nullptr;
            return point;});
    }
    //add kingside castling and queenside castling?
    
    /*
     * QUEEN MOVES
     
    std::vector<std::function<std::unique_ptr<Point>(Piece&/*, int)>>  queenMoves;
    
    for(int8_t i=-7; i<8; i++)
    {
        if(i == 0)
            continue;
        
        queenMoves.push_back([=](Piece &p/*,Board &b) {
            std::unique_ptr<Point> point(new Point(p.getPosition().getX() + i, p.getPosition().getY()));
            if(false)// !Board.validstraightmove(p.getTeamColor())
                point=nullptr;
            return point;});
        
        queenMoves.push_back([=](Piece &p/*,Board &b) {
            std::unique_ptr<Point> point(new Point(p.getPosition().getX(), p.getPosition().getY() + i));
            if(false)// !Board.validstraightmove(p.getTeamColor())
                point=nullptr;
            return point;});
        
        queenMoves.push_back([=](Piece &p/*,Board &b) {
            std::unique_ptr<Point> point(new Point(p.getPosition().getX() + i, p.getPosition().getY() + i));
            if(false)// !Board.validstraightmove(p.getTeamColor())
                point=nullptr;
            return point;});
        
        queenMoves.push_back([=](Piece &p/*,Board &b) {
            std::unique_ptr<Point> point(new Point(p.getPosition().getX() + i, p.getPosition().getY() - i));
            if(false)// !Board.validstraightmove(p.getTeamColor())
                point=nullptr;
            return point;});
    }
    
    /*
     * KING MOVES
     
    std::vector<std::function<std::unique_ptr<Point>(Piece&/*, int)>>  kingMoves;
    
    for(int8_t i=-1; i<2; i++)
    {
        if(i == 0)
            continue;
        
        kingMoves.push_back([=](Piece &p/*,Board &b) {
            std::unique_ptr<Point> point(new Point(p.getPosition().getX() + i, p.getPosition().getY()));
            if(false)// !Board.validstraightmove(p.getTeamColor())
                point=nullptr;
            return point;});
        
        kingMoves.push_back([=](Piece &p/*,Board &b) {
            std::unique_ptr<Point> point(new Point(p.getPosition().getX(), p.getPosition().getY() + i));
            if(false)// !Board.validstraightmove(p.getTeamColor())
                point=nullptr;
            return point;});
        
        kingMoves.push_back([=](Piece &p/*,Board &b) {
            std::unique_ptr<Point> point(new Point(p.getPosition().getX() + i, p.getPosition().getY() + i));
            if(false)// !Board.validstraightmove(p.getTeamColor())
                point=nullptr;
            return point;});
        
        kingMoves.push_back([=](Piece &p/*,Board &b) {
            std::unique_ptr<Point> point(new Point(p.getPosition().getX() + i, p.getPosition().getY() - i));
            if(false)// !Board.validstraightmove(p.getTeamColor())
                point=nullptr;
            return point;});
    }
    //add kingside castling and queenside castling?
}*/
