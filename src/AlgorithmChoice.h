#ifndef CMAKESFMLPROJECT_ALGORITMCHOICE_H
#define CMAKESFMLPROJECT_ALGORITMCHOICE_H
#include <vector>
#include <string>
#include "Board.h"


class AlgoritmChoice {
protected:
    Board& board;
public:
    AlgoritmChoice(Board& _board):board(_board){};
    virtual int MakeChoice() = 0;
    virtual std::string getName() const = 0;
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
    std::string getName() const override {
        return "Minimax";
    }
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
    std::string getName() const override {
        return "Random";
    }
};


class AlgoritmNaive: public AlgoritmChoice {
public:
    AlgoritmNaive(Board& _board): AlgoritmChoice(_board) {};
    int MakeChoice() override;
    std::string getName() const override {
        return "Naive";
    }
};

// pod greedy dodac jedno zagladanie w dol
class AlgorithmGreedyRandom: public AlgoritmChoice {
    BoardState me;
    BoardState opponent;
public:
    AlgorithmGreedyRandom(Board& _board, BoardState _me): AlgoritmChoice(_board), me(_me) {
        opponent = (me == BoardState::Player1) ? BoardState::Player2 : BoardState::Player1;
    };
    int MakeChoice() override;
    std::string getName() const override {
        return "GreedyRandom";
    }
};


class AlgoritmGreedy: public AlgoritmChoice {
    BoardState me;
    BoardState opponent;
    AlgoritmChoice* move;
    public:
    AlgoritmGreedy(Board& _board, BoardState _me): AlgoritmChoice(_board), me(_me) {
        opponent = (me == BoardState::Player1) ? BoardState::Player2 : BoardState::Player1;
        move = new Minimax(board, me, 1);
    }
    int MakeChoice() override {
        if (move) {
            return move->MakeChoice();
        }
        return -1;
    };
    std::string getName() const override {
        return "AlgoritmGreedy";
    }
};

class AlgorithmBruteForce: public AlgoritmChoice {
    BoardState me;
    BoardState opponent;
    int maxDepth;
    AlgoritmChoice* move;
public:
    AlgorithmBruteForce(Board& _board, BoardState _me): AlgoritmChoice(_board), me(_me) {
        opponent = (me == BoardState::Player1) ? BoardState::Player2 : BoardState::Player1;
        maxDepth = board.getRows() * board.getCols();
        move = new Minimax(board, me, maxDepth);
    };
    int MakeChoice() override {
        if(move) {
            return move->MakeChoice();
        }
        return -1;
    };
    ~AlgorithmBruteForce() {
        delete move;
    }
    std::string getName() const override {
        return "BruteForce";
    }
};

#endif //CMAKESFMLPROJECT_ALGORITMCHOICE_H