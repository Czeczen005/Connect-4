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






#endif //CMAKESFMLPROJECT_ALGORITHMAI_H