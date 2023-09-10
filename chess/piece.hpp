//
//  piece.hpp
//  chess
//
//  Created by pardo jérémie on 10/08/2023.
//

#ifndef piece_hpp
#define piece_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include "basicGeometric.hpp"

class Board;

class Piece {
public:
    Piece(Point& position, bool teamColor, std::string name = "piece") : _position(position), _name(name), _teamColor(teamColor) {}
    ~Piece(){}
    
    bool getTeamColor() const { return _teamColor; }
    
    std::string getName() const { return _name; }

    bool getMoved() const { return _moved; }
    
    
    const Point& getPosition() const { return _position; }
    void setPosition(const Point& position) {
        _position = position;
        _moved = true;
    }
    
    virtual void updatePossibleMove(Board* board) = 0;
    const std::vector<Point*>& getPossibleMove() const { return _possibleMove; }
    
protected:
    std::vector<Point*> _possibleMove;

private:
    Point _position;
    bool _moved = false;

    const std::string _name;
    bool _teamColor; // BLACK = 0, WHITE = 1
};

inline bool operator==(const Piece& a,const Piece& b)
{
    return a.getPosition() == b.getPosition() && a.getTeamColor() == b.getTeamColor() && a.getName() == b.getName() ;
}

//*****************
//**    Pieces   **
//*****************
class Pawn : public Piece {
public:
    Pawn(Point& position, bool teamColor) : Piece(position,teamColor,"pawn") {}
    Pawn(const Pawn&) = delete;
    Pawn(Pawn&&) = delete;
    Pawn& operator=( const Pawn&) = delete;
    Pawn& operator=(Pawn&&) = delete;
    ~Pawn(){}
    
    void updatePossibleMove(Board& board);
};

class Knights : public Piece {
public:
    Knights(Point& position, bool teamColor) : Piece(position,teamColor,"knights") {}
    Knights(const Knights&) = delete;
    Knights(Knights&&) = delete;
    Knights& operator=( const Knights&) = delete;
    Knights& operator=(Knights&&) = delete;
    ~Knights(){}
    
    void updatePossibleMove(Board& board);
};

class Bishops : public Piece {
public:
    Bishops(Point& position, bool teamColor) : Piece(position,teamColor,"bishops") {}
    Bishops(const Bishops&) = delete;
    Bishops(Bishops&&) = delete;
    Bishops& operator=( const Bishops&) = delete;
    Bishops& operator=(Bishops&&) = delete;
    ~Bishops(){}
    
    void updatePossibleMove(Board& board);
};

class Rooks : public Piece {
public:
    Rooks(Point& position, bool teamColor) : Piece(position,teamColor,"rooks") {}
    Rooks(const Rooks&) = delete;
    Rooks(Rooks&&) = delete;
    Rooks& operator=( const Rooks&) = delete;
    Rooks& operator=(Rooks&&) = delete;
    ~Rooks(){}
    
    void updatePossibleMove(Board& board);
};

class Queen : public Piece {
public:
    Queen(Point& position, bool teamColor) : Piece(position,teamColor,"queen") {}
    Queen(const Queen&) = delete;
    Queen(Queen&&) = delete;
    Queen& operator=( const Queen&) = delete;
    Queen& operator=(Queen&&) = delete;
    ~Queen(){}
    
    void updatePossibleMove(Board& board);
};

class King : public Piece {
public:
    King(Point& position, bool teamColor) : Piece(position,teamColor,"king") {}
    King(const King&) = delete;
    King(King&&) = delete;
    King& operator=( const King&) = delete;
    King& operator=(King&&) = delete;
    ~King(){}

    void updatePossibleMove(Board& board);
};

#endif /* piece_hpp */
