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
    Piece(Point& position, std::string& name, bool teamColor) : _position(position), _name(name), _teamColor(teamColor) {}
    Piece(const Piece&) = delete;
    Piece(Piece&&) = delete;
    Piece& operator=( const Piece&) = delete;
    Piece& operator=(Piece&&) = delete;
    ~Piece(){}
    
    bool getTeamColor() const { return _teamColor; }

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

//*****************
//**    Pieces   **
//*****************
class Pawn : public Piece {
public:
    Pawn();
    Pawn(const Pawn&) = delete;
    Pawn(Pawn&&) = delete;
    Pawn& operator=( const Pawn&) = delete;
    Pawn& operator=(Pawn&&) = delete;
    ~Pawn(){}
    
    void updatePossibleMove(Board& board);
};

class Knights : public Piece {
public:
    Knights();
    Knights(const Knights&) = delete;
    Knights(Knights&&) = delete;
    Knights& operator=( const Knights&) = delete;
    Knights& operator=(Knights&&) = delete;
    ~Knights(){}
    
    void updatePossibleMove(Board& board);
};

class Bishops : public Piece {
public:
    Bishops();
    Bishops(const Bishops&) = delete;
    Bishops(Bishops&&) = delete;
    Bishops& operator=( const Bishops&) = delete;
    Bishops& operator=(Bishops&&) = delete;
    ~Bishops(){}
    
    void updatePossibleMove(Board& board);
};

class Rooks : public Piece {
public:
    Rooks();
    Rooks(const Rooks&) = delete;
    Rooks(Rooks&&) = delete;
    Rooks& operator=( const Rooks&) = delete;
    Rooks& operator=(Rooks&&) = delete;
    ~Rooks(){}
    
    void updatePossibleMove(Board& board);
};

class Queen : public Piece {
public:
    Queen();
    Queen(const Queen&) = delete;
    Queen(Queen&&) = delete;
    Queen& operator=( const Queen&) = delete;
    Queen& operator=(Queen&&) = delete;
    ~Queen(){}
    
    void updatePossibleMove(Board& board);
};

class King : public Piece {
public:
    King();
    King(const King&) = delete;
    King(King&&) = delete;
    King& operator=( const King&) = delete;
    King& operator=(King&&) = delete;
    ~King(){}

    void updatePossibleMove(Board& board);
};

#endif /* piece_hpp */
