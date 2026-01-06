
#include "AlgorithmChoice.h"
#include <vector>
#include <cstdlib>
const int SCORE_WIN = 100000;
const int SCORE_LOSE = -100000;

int Minimax::MakeChoice() {
    int bestScore = -999999999;
    int bestMove = -1;
    std::vector<int> bestMoves;
    for (int col = 0; col < board.getCols(); col++) {
        if (board.GetField(0, col) == BoardState::Empty) {
            int row = board.MakeMove(col, me);
            int score = minimaxRecursive(maxDepth - 1, false, row, col);
            board.UndoMove(col);
            if (score > bestScore) {
                bestScore = score;
                bestMove = col;
                bestMoves.clear();
                bestMoves.push_back(col);
            } else if (score == bestScore) {
                bestMoves.push_back(col);
            }
        }
    }
    if (!bestMoves.empty()) {
        return bestMoves[std::rand() % bestMoves.size()];
    }
    return -1;
}

int Minimax::minimaxRecursive(int depth, bool isMaximizing, int lastRow, int lastCol) {
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
        for (int c = 0; c <board.getCols(); c++) {
            if (board.GetField(0, c) == BoardState::Empty) {
                canMove = true;
                int row = board.MakeMove(c, me);
                int eval = minimaxRecursive(depth-1, false, row, c);
                board.UndoMove(c);
                maxEval = std::max(maxEval, eval);
            }
        }
        return canMove ? maxEval : 0;
    }
    else {
        int minEval = 999999999;
        bool canMove = false;
        for (int c = 0; c < board.getCols(); c++) {
            if (board.GetField(0, c) == BoardState::Empty) {
                canMove = true;
                int row = board.MakeMove(c, opponent);
                int eval = minimaxRecursive(depth-1, true, row, c);
                board.UndoMove(c);
                minEval = std::min(minEval, eval);

            }
        }
        return canMove ? minEval : 0;
    }
}
int AlgoritmNaive::MakeChoice() {
    for (int c = 0; c < board.getCols(); c++) {
        if (board.GetField(0, c) == BoardState::Empty) {
            return c;
        }
    }
    return -1;
}


int AlgorithmGreedy::MakeChoice() {
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


