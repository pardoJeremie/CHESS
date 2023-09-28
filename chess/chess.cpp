//
//  chess.cpp
//  chess
//
//  Created by pardo jérémie on 18/09/2023.
//

#include <iostream>
#include <vector>

#include "chess.hpp"
#include "piece.hpp"

void Chess::startMainLoop() {
    while (true) {
        // main menu
        break; // quit
    }
}

void Chess::startNewGame() {
    _board.resetPiecesList();
    
    // Black\LowerCase
    Point p(0,1);
    _board.addToPiecesList(std::make_shared<Pawn>(p,false));
    p.updatePosition(1, 1);
    _board.addToPiecesList(std::make_shared<Pawn>(p,false));
    p.updatePosition(2, 1);
    _board.addToPiecesList(std::make_shared<Pawn>(p,false));
    p.updatePosition(3, 1);
    _board.addToPiecesList(std::make_shared<Pawn>(p,false));
    p.updatePosition(4, 1);
    _board.addToPiecesList(std::make_shared<Pawn>(p,false));
    p.updatePosition(5, 1);
    _board.addToPiecesList(std::make_shared<Pawn>(p,false));
    p.updatePosition(6, 1);
    _board.addToPiecesList(std::make_shared<Pawn>(p,false));
    p.updatePosition(7, 1);
    _board.addToPiecesList(std::make_shared<Pawn>(p,false));
    
    p.updatePosition(0, 0);
    _board.addToPiecesList(std::make_shared<Rook>(p,false));
    p.updatePosition(1, 0);
    _board.addToPiecesList(std::make_shared<Knight>(p,false));
    p.updatePosition(2, 0);
    _board.addToPiecesList(std::make_shared<Bishop>(p,false));
    p.updatePosition(3, 0);
    _board.addToPiecesList(std::make_shared<Queen>(p,false));
    p.updatePosition(5, 0);
    _board.addToPiecesList(std::make_shared<Bishop>(p,false));
    p.updatePosition(6, 0);
    _board.addToPiecesList(std::make_shared<Knight>(p,false));
    p.updatePosition(7, 0);
    _board.addToPiecesList(std::make_shared<Rook>(p,false));
    
    // White\UperCase
    p.updatePosition(0, 6);
    _board.addToPiecesList(std::make_shared<Pawn>(p,true));
    p.updatePosition(1, 6);
    _board.addToPiecesList(std::make_shared<Pawn>(p,true));
    p.updatePosition(2, 6);
    _board.addToPiecesList(std::make_shared<Pawn>(p,true));
    p.updatePosition(3, 6);
    _board.addToPiecesList(std::make_shared<Pawn>(p,true));
    p.updatePosition(4, 6);
    _board.addToPiecesList(std::make_shared<Pawn>(p,true));
    p.updatePosition(5, 6);
    _board.addToPiecesList(std::make_shared<Pawn>(p,true));
    p.updatePosition(6, 6);
    _board.addToPiecesList(std::make_shared<Pawn>(p,true));
    p.updatePosition(7, 6);
    _board.addToPiecesList(std::make_shared<Pawn>(p,true));
    
    p.updatePosition(0, 7);
    _board.addToPiecesList(std::make_shared<Rook>(p,true));
    p.updatePosition(1, 7);
    _board.addToPiecesList(std::make_shared<Knight>(p,true));
    p.updatePosition(2, 7);
    _board.addToPiecesList(std::make_shared<Bishop>(p,true));
    p.updatePosition(3, 7);
    _board.addToPiecesList(std::make_shared<Queen>(p,true));
    p.updatePosition(5, 7);
    _board.addToPiecesList(std::make_shared<Bishop>(p,true));
    p.updatePosition(6, 7);
    _board.addToPiecesList(std::make_shared<Knight>(p,true));
    p.updatePosition(7, 7);
    _board.addToPiecesList(std::make_shared<Rook>(p,true));
    
    
    //kings added last to allway be last in the vector  (king possible move calcultation must be donne last)
    p.updatePosition(4, 0);
    _board.addToPiecesList(std::make_shared<King>(p,false));
    p.updatePosition(4, 7);
    _board.addToPiecesList(std::make_shared<King>(p,true));
    
    turn = true; // white start
    
    std::cout <<"\n ***- New Game -***\n";
}

bool Chess::playturn() {
    char x, y;
    std::shared_ptr<Piece> piece;
   /* (Qu to quit)*/
    _board.updatePiecesMoves();
    
    // loock for end condition
    EnumEndCondition v = _board.returnEndCondition(turn);
    if(v == NO_END_COND_BUT_CHECK)
        std::cout <<"\n- "<< (turn ?"UperCases(white)":"LowerCases(Black)") << "king is CHECK -\n";
    else if(_board.returnEndCondition(!turn) == CHECKMAT) {
        std::cout <<"\n***- "<< (!turn ?"UperCases(white)":"LowerCases(Black)") << " king is CHECKMAT," << (turn ?"UperCases (white)":"LowerCases (Black)") << " WIN the game -***\n\n";
        return false;
    }
    else if(v == STALEMATE) {
        std::cout << "\n***- " <<(turn ?"UperCases(white)":"LowerCases(Black)") << " cannot move any piece, DRAW by stalemate -***\n\n";
        return false;
    }
    
    std::cout <<"\n"<< (turn ?"UperCases(white)":"LowerCases(Black)") << " turn to play" << std::endl;
    
    while(true) {
        _board.printBoard();
        std::cout << "(GU to give up, Sa to save the game)\nType the piece position:" << std::endl;
        std::cin >> x >> y;
        if(x == 'G' && y == 'U') {
            std::cout <<"\n***- " << (!turn ?"UperCases(white)":"LowerCases(Black)") << " WIN the game -***\n\n";
            return false;
        }
        else if(x == 'S' && y == 'a') {
            std::cout << "\n***- game save -***\n\n"<< std::endl;
            // to implement
            return false;
        }
        else if((piece = _board.returnPiece(x,y,turn))) // if piece not == nullptr
            break;
    }

    while(true) {
        _board.printBoard();
        std::cout << "(GU to give up, BC and SC for respectively big castle and small castle)\nType the " << static_cast<char>(piece->getPosition().getX() + 'A')<< static_cast<char>(piece->getPosition().getY() + '1') <<  " "<< piece->getName() <<" desired new position:\n";
        std::cin >> x >> y;
        
        if(x == 'G' && y == 'U') {
            std::cout <<"\n***- " << (!turn ?"UperCases(white)":"LowerCases(Black)") << " WIN the game -***\n\n";
            return false;
        }
        else if(piece->applyMove(x,y,_board)) // move impossible, // wrong input
            break;
    }
    
    _board.pawnPromotion();
    
    turn = !turn;
    return true;
}
