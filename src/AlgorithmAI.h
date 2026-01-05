//
// Created by patry on 06.12.2025.
//

#ifndef CMAKESFMLPROJECT_ALGORITHMAI_H
#define CMAKESFMLPROJECT_ALGORITHMAI_H
#include <cmath>
#include <iostream>

#include "AlgoritmChoice.h"
#include "Board.h"
enum class BoardState;

class Board;
class Minimax;
class AlgoritmChoice;
class Player {
};

class HumanPlayer : public Player {
    BoardState playerState;
    bool myTurn = false;
    int cols;
    int winCounts;
public:
    explicit HumanPlayer(BoardState _playerState): playerState(_playerState), winCounts(0), cols(0), myTurn(false) {
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
protected:
    Board& board;
public:
    explicit AIPlayer(Board& _board): board(_board) {}
    virtual int chooseCol() = 0;
    virtual ~AIPlayer() = default;
};


// Random wybiera losowo wolna kolumne
class AlgorithmRandom : public AIPlayer {
    int col;
public:
    explicit AlgorithmRandom(Board& board):AIPlayer(board), col(0) {}
    int chooseCol() override{
        int col = rand() % 6;
        return col;
    }
};


// Naive wybiera pierwszy z brzegu dostepny
class AlgorithmNaive : public AIPlayer {
    int col;
    int row;
public:
    explicit AlgorithmNaive(Board& _board): AIPlayer(_board), col(0), row(0) {};
    int chooseCol() override{
        for (int c = 0; c < board.getCols(); c++) {
            if (board.GetField(0, c) == BoardState::Empty) {
                return c;
            }
        }
        return -1;

    }
};


// Losowo wybiera kolumny, zamin wykona ruch sprawdza
// czy nie ma szansy na wygranie oraz czy przeciwnik nie wygrywa
class AlgorithmGreedy : public AIPlayer {
    int col;
    int row;
    BoardState me;
    BoardState opponent;
    public:
    explicit AlgorithmGreedy(Board& _board): AIPlayer(_board), col(0), row(0) {
        opponent = (me == BoardState::Player1) ? BoardState::Player2 : BoardState::Player1;
    };
    int chooseCol() override{
        for (int c = 0; c < board.getCols(); c++) {
            if (board.GetField(0, c) == BoardState::Empty) {
                int r = board.MakeMove(c, me);
                if (board.CheckWin(r, c, me)) {
                    board.UndoMove(c);
                    return c;
                }
                board.UndoMove(c);
            }
        }
        for (int c = 0; c < board.getCols(); c++) {
            if (board.GetField(0, c) == BoardState::Empty) {
                int r = board.MakeMove(c, opponent);
                if (board.CheckWin(r, c, opponent)) {
                    board.UndoMove(c);
                    return c;
                }
                board.UndoMove(c);
            }
        }
        std::vector<int> potentialMove;
        for (int c = 0; c<board.getCols(); c++) {
            if (board.GetField(0, c) == BoardState::Empty) {
                potentialMove.push_back(c);
            }
        }
        if (!potentialMove.empty()) {
            return potentialMove[std::rand() % potentialMove.size()];
        }
        return -1;
    }
};

class AlgorithmBruteForce: public AIPlayer{
    BoardState myBoardState;
    int MaxDepth;
    AlgoritmChoice* moveStrategy;
    public:
    AlgorithmBruteForce(Board& _board, BoardState& _my):AIPlayer(_board), myBoardState(_my), moveStrategy(nullptr) {
        double rowsExpr = std::pow(2,board.getRows() + 1) - 1;
        double totalStates = std::pow(rowsExpr,board.getCols());
        moveStrategy = new Minimax(board, myBoardState, totalStates);
    };
    ~AlgorithmBruteForce() {
        if (moveStrategy != nullptr) {
            delete moveStrategy;
        }
    }
    int chooseCol() override {
        if (moveStrategy) return moveStrategy ->MakeChoice();
        return -1;
    }
};

#endif //CMAKESFMLPROJECT_ALGORITHMAI_H