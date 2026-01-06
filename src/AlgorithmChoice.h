#ifndef CMAKESFMLPROJECT_ALGORITMCHOICE_H
#define CMAKESFMLPROJECT_ALGORITMCHOICE_H
#include <vector>
#include "Board.h"


class AlgoritmChoice {
protected:
    Board& board;
public:
    AlgoritmChoice(Board& _board):board(_board){};
    virtual int MakeChoice() = 0;
    virtual ~AlgoritmChoice() =default;

};

class Minimax: public AlgoritmChoice {
    BoardState me;
    BoardState opponent;
    int maxDepth;
    int minimaxRecursive(int depth, bool isMaximizing, int lastRow, int lastCol);
    public:
    Minimax(Board& _board, BoardState _me, int _depth): AlgoritmChoice(_board), me(_me), maxDepth(_depth) {
        opponent = (me == BoardState::Player1) ? BoardState::Player2 : BoardState::Player1;
    };
    int MakeChoice() override;
};


class AlgoritmRandom: public AlgoritmChoice {
public:
AlgoritmRandom(Board& _board): AlgoritmChoice(_board) {};
int MakeChoice() override {
    std::vector<int> availableCols;
    for (int c = 0; c < board.getCols(); c++) {
        if (board.GetField(0, c) == BoardState::Empty) {
            availableCols.push_back(c);
        }   
    }
    if(availableCols.empty()) {
            return -1; 
        }
    int randomIndex = std::rand() % availableCols.size();
    return availableCols[randomIndex];
     
        
}
};


class AlgoritmNaive: public AlgoritmChoice {
public:
    AlgoritmNaive(Board& _board): AlgoritmChoice(_board) {};
    int MakeChoice() override; 
};


class AlgorithmGreedy: public AlgoritmChoice {
    BoardState me;
    BoardState opponent;
public:
    AlgorithmGreedy(Board& _board, BoardState _me): AlgoritmChoice(_board), me(_me) {
        opponent = (me == BoardState::Player1) ? BoardState::Player2 : BoardState::Player1;
    };
    int MakeChoice() override;

    
};











#endif //CMAKESFMLPROJECT_ALGORITMCHOICE_H