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

void Chess::printBoard() {
    
    char graphicboard[8][8] = {
        {[0 ... 7] = '.'},
        {[0 ... 7] = '.'},
        {[0 ... 7] = '.'},
        {[0 ... 7] = '.'},
        {[0 ... 7] = '.'},
        {[0 ... 7] = '.'},
        {[0 ... 7] = '.'},
        {[0 ... 7] = '.'}};
    
    for (std::vector<Piece *>::iterator it = _board.getPiecesList().begin() ; it != _board.getPiecesList().end(); ++it) {
        Pawn* pawn = dynamic_cast<Pawn*>(*it);
        if(pawn) {
            graphicboard[(*it)->getPosition().getX()][(*it)->getPosition().getY()] = (*it)->getTeamColor()?'P':'p';
            continue;
        }
        
        Knight* knight = dynamic_cast<Knight*>(*it);
        if(knight) {
            graphicboard[(*it)->getPosition().getX()][(*it)->getPosition().getY()] = (*it)->getTeamColor()?'N':'n';
            continue;
        }
            
        Bishop* bishop = dynamic_cast<Bishop*>(*it);
        if(bishop) {
            graphicboard[(*it)->getPosition().getX()][(*it)->getPosition().getY()] = (*it)->getTeamColor()?'B':'b';
            continue;
        }
        
        Rook* rook = dynamic_cast<Rook*>(*it);
        if(rook) {
            graphicboard[(*it)->getPosition().getX()][(*it)->getPosition().getY()] = (*it)->getTeamColor()?'R':'r';
            continue;
        }
        
        Queen* queen = dynamic_cast<Queen*>(*it);
        if(queen) {
            graphicboard[(*it)->getPosition().getX()][(*it)->getPosition().getY()] = (*it)->getTeamColor()?'Q':'q';
            continue;
        }
            
        King* king = dynamic_cast<King*>(*it);
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

void Chess::startNewGame() {
    _board.resetPiecesList();
    
    // Black\LowerCase
    Point p(0,1);
    _board.addToPiecesList(new Pawn(p,false));
    p.updatePosition(1, 1);
    _board.addToPiecesList(new Pawn(p,false));
    p.updatePosition(2, 1);
    _board.addToPiecesList(new Pawn(p,false));
    p.updatePosition(3, 1);
    _board.addToPiecesList(new Pawn(p,false));
    p.updatePosition(4, 1);
    _board.addToPiecesList(new Pawn(p,false));
    p.updatePosition(5, 1);
    _board.addToPiecesList(new Pawn(p,false));
    p.updatePosition(6, 1);
    _board.addToPiecesList(new Pawn(p,false));
    p.updatePosition(7, 1);
    _board.addToPiecesList(new Pawn(p,false));
    
    p.updatePosition(0, 0);
    _board.addToPiecesList(new Rook(p,false));
    p.updatePosition(1, 0);
    _board.addToPiecesList(new Knight(p,false));
    p.updatePosition(2, 0);
    _board.addToPiecesList(new Bishop(p,false));
    p.updatePosition(3, 0);
    _board.addToPiecesList(new Queen(p,false));
    p.updatePosition(5, 0);
    _board.addToPiecesList(new Bishop(p,false));
    p.updatePosition(6, 0);
    _board.addToPiecesList(new Knight(p,false));
    p.updatePosition(7, 0);
    _board.addToPiecesList(new Rook(p,false));
    
    // White\UperCase
    p.updatePosition(0, 6);
    _board.addToPiecesList(new Pawn(p,true));
    p.updatePosition(1, 6);
    _board.addToPiecesList(new Pawn(p,true));
    p.updatePosition(2, 6);
    _board.addToPiecesList(new Pawn(p,true));
    p.updatePosition(3, 6);
    _board.addToPiecesList(new Pawn(p,true));
    p.updatePosition(4, 6);
    _board.addToPiecesList(new Pawn(p,true));
    p.updatePosition(5, 6);
    _board.addToPiecesList(new Pawn(p,true));
    p.updatePosition(6, 6);
    _board.addToPiecesList(new Pawn(p,true));
    p.updatePosition(7, 6);
    _board.addToPiecesList(new Pawn(p,true));
    
    p.updatePosition(0, 7);
    _board.addToPiecesList(new Rook(p,true));
    p.updatePosition(1, 7);
    _board.addToPiecesList(new Knight(p,true));
    p.updatePosition(2, 7);
    _board.addToPiecesList(new Bishop(p,true));
    p.updatePosition(3, 7);
    _board.addToPiecesList(new Queen(p,true));
    p.updatePosition(5, 7);
    _board.addToPiecesList(new Bishop(p,true));
    p.updatePosition(6, 7);
    _board.addToPiecesList(new Knight(p,true));
    p.updatePosition(7, 7);
    _board.addToPiecesList(new Rook(p,true));
    
    
    //kings added last to allway be last in the vector  (king possible move calcultation must be donne last)
    p.updatePosition(4, 0);
    _board.addToPiecesList(new King(p,false));
    p.updatePosition(4, 7);
    _board.addToPiecesList(new King(p,true));
    
    turn = true; // white start
    
    std::cout <<"\n ***- New Game -***\n\n ";
}

bool Chess::playturn() {
    char x, y;
    Piece* piece;
   /* (Qu to quit)*/
    _board.updatePiecesMoves();
    
    std::cout << (turn ?"UperCases (white)":"LowerCases (Black)") << " turn to play" << std::endl;
    
    while(true) {
        printBoard();
        std::cout << "(GU to give up, Sa to save the game)\nType the piece position:" << std::endl;
        std::cin >> x >> y;
        if(x == 'G' && y == 'U') {
            std::cout <<"\n ***- " << (!turn ?"UperCases (white)":"LowerCases (Black)") << " WIN the game -***\n\n ";
            return false;
        }
        else if(x == 'S' && y == 'a') {
            std::cout << "game save"<< std::endl;
            // to implement
            return false;
        }
        else if((piece = _board.returnPiece(x,y,turn))) // if piece not == nullptr
            break;
    }

    while(true) {
        printBoard();
        std::cout << "(GU to give up, BC and SC for respectively big castle and small castle)\nType the " << static_cast<char>(piece->getPosition().getX() + 'A')<< static_cast<char>(piece->getPosition().getY() + '1') <<  " "<< piece->getName() <<" desired new position:\n";
        std::cin >> x >> y;
        
        if(x == 'G' && y == 'U') {
            std::cout <<"\n ***- " << (!turn ?"UperCases (white)":"LowerCases (Black)") << " WIN the game -***\n\n ";
            return false;
        }
        else if(piece->applyMove(x,y,_board)) // move impossible, // wrong input
            break;
    }
    
    turn = !turn;
    return true;
}
