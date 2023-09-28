//
//  chess.cpp
//  chess
//
//  Created by pardo jérémie on 18/09/2023.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include "chess.hpp"
#include "piece.hpp"

bool Chess::playturn() {
    char x, y;
    std::shared_ptr<Piece> piece;
   /* (Qu to quit)*/
    _board.updatePiecesMoves();
    
    // loock for end condition
    EnumEndCondition v = _board.returnEndCondition(_turn);
    if(v == NO_END_COND_BUT_CHECK)
        std::cout <<"\n- "<< (_turn ?"UperCases(white)":"LowerCases(Black)") << "king is CHECK -\n";
    else if(_board.returnEndCondition(!_turn) == CHECKMAT) {
        std::cout <<"\n***- "<< (!_turn ?"UperCases(white)":"LowerCases(Black)") << " king is CHECKMAT," << (_turn ?"UperCases (white)":"LowerCases (Black)") << " WIN the game -***\n\n";
        return false;
    }
    else if(v == STALEMATE) {
        std::cout << "\n***- " <<(_turn ?"UperCases(white)":"LowerCases(Black)") << " cannot move any piece, DRAW by stalemate -***\n\n";
        return false;
    }
    
    std::cout <<"\n"<< (_turn ?"UperCases(white)":"LowerCases(Black)") << " turn to play\n";
    
    while(true) {
        _board.printBoard();
        std::cout << "(\'GU\' to give up, \'Sa\' to save the game)\nType the piece position:\n";
        std::cin >> x >> y;
        if(!std::cin.good()) {
            x = 0;
            y = 0;
        }
        std::cin.clear();
        
        if((x == 'G' || x == 'g') && (y == 'U' || y == 'u')) {
            std::cout <<"\n***- " << (!_turn ?"UperCases(white)":"LowerCases(Black)") << " WIN the game -***\n\n";
            return false;
        }
        else if((x == 'S' || x == 's') && (y == 'A' || y == 'a')) {
            saveGame();
            std::cout << "\n***- game save -***\n\n\n";
            return false;
        }
        else if((piece = _board.returnPiece(x,y,_turn))) // if piece not == nullptr
            break;
    }

    while(true) {
        _board.printBoard();
        std::cout << "(\'GU\' to give up, \'BC\' and \'SC\' for respectively big castle and small castle)\nType the " << static_cast<char>(piece->getPosition().getX() + 'A')<< static_cast<char>(piece->getPosition().getY() + '1') <<  " "<< piece->getName() <<" desired new position:\n";
        std::cin >> x >> y;
        if(!std::cin.good()) {
            x = 0;
            y = 0;
        }
        std::cin.clear();
        
        if((x == 'G' || x == 'g') && (y == 'U' || y == 'u')) {
            std::cout <<"\n***- " << (!_turn ?"UperCases(white)":"LowerCases(Black)") << " WIN the game -***\n\n";
            return false;
        }
        else if(piece->applyMove(x,y,_board)) // move impossible, // wrong input
            break;
    }
    
    _board.pawnPromotion();
    
    _turn = !_turn;
    return true;
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
    
    _turn = true; // white start
    
    std::cout <<"\n ***- New Game -***\n";
}

bool Chess::loadGame() {
    std::ifstream fstream("save");
    if (fstream.is_open()) {
        _board.resetPiecesList(); // clear board
        
        std::string line;
        char type = '\0';
        short x, y;
        bool team, moved, other /*_didSpecialMoveLastTurn or ischecked??*/;
        bool turn;
        std::getline(fstream, line);
        { // using lstream.str(line) give me erronous value ...
            std::stringstream lstream(line);
            lstream >> turn;
        }
        _turn = turn;
        do {
            std::getline(fstream, line);
            std::stringstream lstream(line);
            lstream >> type >> x >> y >> team >> moved;
            Point p(x,y);
            switch (type) {
                case 'p':
                    lstream >> other;
                    _board.addToPiecesList(std::make_shared<Pawn>(p,team,moved,other));
                    break;
                case 'r':
                    _board.addToPiecesList(std::make_shared<Rook>(p,team,moved));
                    break;
                case 'b':
                    _board.addToPiecesList(std::make_shared<Bishop>(p,team,moved));
                    break;
                case 'n':
                    _board.addToPiecesList(std::make_shared<Knight>(p,team,moved));
                    break;
                case 'q':
                    _board.addToPiecesList(std::make_shared<Queen>(p,team,moved));
                    break;
                case 'k':
                    _board.addToPiecesList(std::make_shared<King>(p,team,moved));
                    break;
                default:
                    std::cout << "error during file reading\n";
                    return false;
                    break;
            }
            
        } while (fstream);
        std::cout <<"\n ***- Game Loaded -***\n";
        return true;
    }
    std::cout << "Cannot open file, no save present\n";
    return false;
}

void Chess::saveGame() {
    std::ofstream fstream("save");
    
    fstream << _turn << std::endl;
        
    for(std::vector<std::shared_ptr<Piece>>::iterator it = _board.getPiecesList().begin(); it != _board.getPiecesList().end(); it++) {
        std::shared_ptr<Pawn> pawn =  std::dynamic_pointer_cast<Pawn>(* it);
        if(pawn) {
            fstream << 'p' << ' ' << (*it)->getPosition().getX() << ' ' << (*it)->getPosition().getY() << ' ' << (*it)->getTeamColor() << ' ' << (*it)->getMoved() << ' ' << pawn->_didSpecialMoveLastTurn << std::endl;
            continue;
        }
        std::shared_ptr<Rook> rook =  std::dynamic_pointer_cast<Rook>(* it);
        if(rook) {
            fstream << 'r' << ' ' << (*it)->getPosition().getX() << ' ' << (*it)->getPosition().getY() << ' ' << (*it)->getTeamColor() << ' ' << (*it)->getMoved() << std::endl;
            continue;
        }
        std::shared_ptr<Knight> knight =  std::dynamic_pointer_cast<Knight>(* it);
        if(knight) {
            fstream << 'n' << ' ' << (*it)->getPosition().getX() << ' ' << (*it)->getPosition().getY() << ' ' << (*it)->getTeamColor() << ' ' << (*it)->getMoved() << std::endl;
            continue;
        }
        std::shared_ptr<Bishop> bishop =  std::dynamic_pointer_cast<Bishop>(* it);
        if(bishop) {
            fstream << 'b' << ' ' << (*it)->getPosition().getX() << ' ' << (*it)->getPosition().getY() << ' ' << (*it)->getTeamColor() << ' ' << (*it)->getMoved() << std::endl;
            continue;
        }
        std::shared_ptr<Queen> queen =  std::dynamic_pointer_cast<Queen>(* it);
        if(queen) {
            fstream << 'q' << ' ' << (*it)->getPosition().getX() << ' ' << (*it)->getPosition().getY() << ' ' << (*it)->getTeamColor() << ' ' << (*it)->getMoved() << std::endl;
            continue;
        }
        std::shared_ptr<King> king =  std::dynamic_pointer_cast<King>(* it);
        if(king) {
            fstream << 'k' << ' ' << (*it)->getPosition().getX() << ' ' << (*it)->getPosition().getY() << ' ' << (*it)->getTeamColor() << ' ' << (*it)->getMoved() << std::endl;
            continue;
        }
    }
}

void Chess::deletSave() {
    if (remove("save") == 0)
        std::cout << "Deleted successfully\n";
    else
        std::cout <<"Unable to delete the save\n";
}

void Chess::menu() {
    char x;
    while(true) {
        std::cout << "\n###- WELCOM TO CHESS -###\n\n* To play a new game, write \'N\'\n* To load the saved party, write \'L\'\n* To delete the saved party, write \'D\'\n* To quit, write \'Q\'\n\n";
        std::cin >> x;
        if(!std::cin.good()) {
            x = 0;
        }
        std::cin.clear();
        if(x == 'N' || x == 'n') {
            startNewGame();
            while(playturn());
        }
        else if(x == 'L' || x == 'l') {
            if(loadGame())
                while(playturn());
        }
        else if(x == 'D' || x == 'd') {
            deletSave();
        }
        else if(x == 'Q' || x == 'q') {
            std::cout << "\n###- Thank you for playing -###\n\n";
            return;
        }
        else {
            std::cout << "\nWrong user input.\n";
        }
    }
}
