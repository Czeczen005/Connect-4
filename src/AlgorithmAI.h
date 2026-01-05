//
// Created by patry on 06.12.2025.
//

#ifndef CMAKESFMLPROJECT_ALGORITHMAI_H
#define CMAKESFMLPROJECT_ALGORITHMAI_H
#include <iostream>

#include "Board.h"

enum class BoardState;

class Board;

class Player {
};

class HumanPlayer : public Player {
    BoardState playerState;
    bool myTurn = false;
    int cols;
    int winCounts;
public:
    HumanPlayer(BoardState _playerState): playerState(_playerState), winCounts(0), cols(0), myTurn(false) {
        if (playerState == BoardState::Player1) {
            myTurn = true;
        }
    }
    void setCols(){
        std::cout<<"Gracz "<<static_cast<int>(playerState) <<" Podaj kolumne: ";
        std::cin >> cols;
        myTurn = false;
    }
    void setTurn(bool turn) {
        myTurn = turn;
    }
    bool getTurn(){return myTurn;}
    int getCols() {return cols;}
    BoardState getPlayerState() {return playerState;}

};

class AIPlayer: public Player{
};

class AlgorithmRandom : public AIPlayer {
    int col;
public:
    AlgorithmRandom(): col(0) {}
    int chooseCol() {
        int col = rand() % 6;
        return col;
    }
};

class AlgorithmNaive : public AIPlayer {
    int col;
    int row;
    Board& board;
public:
    AlgorithmNaive(Board& _board): board(_board), col(0), row(0) {};
    int chooseRow() {
        for (int c = 0; c < board.getCols(); c++) {
            if (board.GetField(0, c) == BoardState::Empty) {
                return c;
            }
        }
        return -1;

    }
};



class AlgorithmGreedy : public AIPlayer {
};


#endif //CMAKESFMLPROJECT_ALGORITHMAI_H