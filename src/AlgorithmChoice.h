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
    virtual int makeChoice() = 0;
    virtual std::string getName() const = 0;
    virtual ~AlgoritmChoice() =default;


};

class Minimax: public AlgoritmChoice {
    BoardState me;
    BoardState opponent;
    int maxDepth;
    bool isRandom;
    int minimaxRecursive(int depth, bool isMaximizing, int lastRow, int lastCol, int alpha, int beta);
    public:
    Minimax(Board& _board, BoardState _me, int _depth, bool variant): AlgoritmChoice(_board), me(_me), maxDepth(_depth) {
        opponent = (me == BoardState::Player1) ? BoardState::Player2 : BoardState::Player1;
        isRandom = variant;

    };
    int makeChoice() override;
    std::string getName() const override {
        if (isRandom)return "Minimax-Random";
        return "Minimax-MinDistance";
    }
    static int minimaxRandomchoose(std::vector<int> bestMoves);
    int minimaxMinDistance(std::vector<int> bestMoves);
    bool getIsRandom(){return isRandom;}
};


class AlgoritmRandom: public AlgoritmChoice {
public:
AlgoritmRandom(Board& _board): AlgoritmChoice(_board) {};
    int makeChoice() override {
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
    int makeChoice() override;
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
    int makeChoice() override;
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
        move = new Minimax(board, me, 1, true);
    }
    int makeChoice() override;
    std::string getName() const override {
        return "AlgoritmGreedy";
    }
    ~AlgoritmGreedy() override {
        delete move;
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
        move = new Minimax(board, me, maxDepth, true);
    };
    int makeChoice() override {
        if(move) {
            return move->makeChoice();
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