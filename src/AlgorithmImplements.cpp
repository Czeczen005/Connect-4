#include <chrono>
#include <ostream>
#include "AlgorithmChoice.h"
#include <vector>
#include <cstdlib>
#include <fstream>
const int SCORE_WIN = 100000;
const int SCORE_LOSE = -100000;
const int INF = 2000000000;

int Minimax::makeChoice() {
    int currentAlpha = -INF;
    auto startTime = std::chrono::system_clock::now();
    int bestScore = -999999999;
    int bestMove = -1;
    std::vector<int> bestMoves;
    for (int col = 0; col < Board::getCols(); col++) {
        if (board.GetField(0, col) == BoardState::Empty) {
            int row = board.MakeMove(col, me);
            int score = minimaxRecursive(maxDepth - 1, false, row, col,currentAlpha,INF);
            board.UndoMove(col);
            if (score > bestScore) {
                bestScore = score;
                bestMove = col;
                bestMoves.clear();
                bestMoves.push_back(col);
                currentAlpha = std::max(currentAlpha, bestScore);
            } else if (score == bestScore) {
                bestMoves.push_back(col);
            }
        }
    }
    auto endTime = std::chrono::system_clock::now();
    std::chrono::duration<double, std::milli> elapsedTime = endTime - startTime;
    std::ofstream file("wynik_z_czasu.txt", std::ios::app);
    if (file.is_open()) {
        file << elapsedTime.count() << std::endl;
        file.close();
    }
    if (!bestMoves.empty()) {
        if (getIsRandom()) {
            return minimaxRandomchoose(bestMoves);
        }else {
            return minimaxMinDistance(bestMoves);
        }
    }
    return -1;
}

int Minimax::minimaxRecursive(int depth, bool isMaximizing, int lastRow, int lastCol, int alpha, int beta){
    BoardState prevPlayer = isMaximizing ? opponent : me;
    if (board.CheckWin(lastRow, lastCol, prevPlayer)) {
        if (prevPlayer == me) return SCORE_WIN + depth;
        else return SCORE_LOSE - depth;
    }
    if (depth == 0) {
        return 0;
    }
    if (isMaximizing) {
        int maxEval = -99999999;
        bool canMove = false;
        for (int c = 0; c <Board::getCols(); c++) {
            if (board.GetField(0, c) == BoardState::Empty) {
                canMove = true;
                int row = board.MakeMove(c, me);
                int eval = minimaxRecursive(depth-1, false, row, c,alpha, beta);
                board.UndoMove(c);
                maxEval = std::max(maxEval, eval);
                alpha = std::max(alpha, eval);
                if (beta <= alpha) break;
            }
        }
        return canMove ? maxEval : 0;
    }
    else{
        int minEval = 999999999;
        bool canMove = false;
        for (int c = 0; c < Board::getCols(); c++) {
            if (board.GetField(0, c) == BoardState::Empty) {
                canMove = true;
                int row = board.MakeMove(c, opponent);
                int eval = minimaxRecursive(depth-1, true, row, c, alpha, beta);
                board.UndoMove(c);
                minEval = std::min(minEval, eval);
                beta = std::min(beta, eval);
                if (beta <= alpha) break;
            }
        }
        return canMove ? minEval : 0;
    }
}

int Minimax::minimaxRandomchoose(std::vector<int> bestMoves) {
    return bestMoves[std::rand() % bestMoves.size()];
}


int Minimax::minimaxMinDistance(std::vector<int> bestMoves) {
    int center = (board.getCols()) / 2;
    int bestMove = bestMoves[0];
    int minDistance = std::abs(bestMove - center);
    for (size_t i = 1; i < bestMoves.size(); ++i) {
        int move = bestMoves[i];
        int currentDistance = std::abs(move - center);
        if (currentDistance < minDistance) {
            minDistance = currentDistance;
            bestMove = move;
        }
    }
    return bestMove;
}

int AlgoritmNaive::makeChoice() {
    for (int c = 0; c < board.getCols(); c++) {
        if (board.GetField(0, c) == BoardState::Empty) {
            return c;
        }
    }
    return -1;
}

int AlgorithmGreedyRandom::makeChoice() {
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

int AlgoritmGreedy::makeChoice() {
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
    if (move) {
        return move->makeChoice();
    }
    return -1;
}
