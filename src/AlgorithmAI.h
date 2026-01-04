//
// Created by patry on 06.12.2025.
//

#ifndef CMAKESFMLPROJECT_ALGORITHMAI_H
#define CMAKESFMLPROJECT_ALGORITHMAI_H
#include <iostream>

#include "Board.h"

enum class BoardState;

class Player {
};

class HumanPlayer : Player {
    BoardState playerState;
    bool myTurn = false;
    int cols;
    int winCounts;
public:
    HumanPlayer(BoardState _playerState): playerState(_playerState), winCounts(0) {
        if (playerState == BoardState::Player1) {
            myTurn = true;
        }
    }
    void setCols() {
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

class AIPlayer: Player{
};


class AlgorithmAI{};

class AlgorithmRandom : AlgorithmAI {};

class AlgorithSearchDeep : AlgorithmAI{};


#endif //CMAKESFMLPROJECT_ALGORITHMAI_H