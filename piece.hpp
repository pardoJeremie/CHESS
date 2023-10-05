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
enum EnumSpecialMove : short { NA, PAWNSPECIAL, PAWNDIAGONAL, BIGCASTLE, SMALLCASTLE}; // utiliser enum class??

class Piece {
public:
    Piece(Point& position, bool teamColor, bool moved = false, std::string name = "piece") : _position(position), _moved(moved), _name(name), _teamColor(teamColor) {}
    Piece(const Piece& p) = delete;
    Piece(Piece&&) = delete;
    Piece& operator=( const Piece&) = delete;
    Piece& operator=(Piece&&) = delete;
    virtual ~Piece() = default;
    
    bool getTeamColor() const { return _teamColor; }
    
    std::string getName() const { return _name; }

    bool getMoved() const { return _moved; }
    
    const Point& getPosition() const { return _position; }
    
    void setPosition(const Point& position) {
        _position = position;
        _moved = true;
    }
    
    virtual void updatePossibleMove(Board& board) = 0;
    const std::vector<std::pair <Point,EnumSpecialMove>>& getPossibleMoves() const { return _possibleMove; }
    
    bool applyMove(const char x, const char y, Board& board);
    
protected:
    std::vector<std::pair <Point,EnumSpecialMove>> _possibleMove;

private:
    Point _position;
    bool _moved;

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
    Pawn(Point& position, bool teamColor, bool moved = false, bool didSpecialMoveLastTurn = false) : Piece(position,teamColor,moved,"PAWN"), _didSpecialMoveLastTurn(didSpecialMoveLastTurn) {}
    ~Pawn() = default;
    
    void updatePossibleMove(Board& board);

    bool _didSpecialMoveLastTurn; // TO REDO DIFFERENTLY?
};

class Knight : public Piece {
public:
    Knight(Point& position, bool teamColor, bool moved = false) : Piece(position,teamColor,moved,"KNIGHT") {}
    ~Knight() = default;
    
    void updatePossibleMove(Board& board);
};

class Bishop : public Piece {
public:
    Bishop(Point& position, bool teamColor, bool moved = false) : Piece(position,teamColor,moved,"BISHOP") {}
    ~Bishop() = default;
    
    void updatePossibleMove(Board& board);
};

class Rook : public Piece {
public:
    Rook(Point& position, bool teamColor, bool moved = false) : Piece(position,teamColor,moved,"ROOK") {}
    ~Rook() = default;
    
    void updatePossibleMove(Board& board);
};

class Queen : public Piece {
public:
    Queen(Point& position, bool teamColor, bool moved = false) : Piece(position,teamColor,moved,"QUEEN") {}
    ~Queen() = default;
    
    void updatePossibleMove(Board& board);
};

class King : public Piece {
public:
    King(Point& position, bool teamColor, bool moved = false) : Piece(position,teamColor, moved,"KING") {}
    ~King() = default;

    void updatePossibleMove(Board& board);

    bool _ischeck=false;
    bool _ischeckTwoTurn=false;
};

#endif /* piece_hpp */
