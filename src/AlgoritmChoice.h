#ifndef CMAKESFMLPROJECT_ALGORITMCHOICE_H
#define CMAKESFMLPROJECT_ALGORITMCHOICE_H
#include "Board.h"


class AlgoritmChoice {
protected:
    Board& board;
public:
    AlgoritmChoice(Board& _board):board(_board){};
    virtual int MakeChoise() = 0;
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









#endif //CMAKESFMLPROJECT_ALGORITMCHOICE_H