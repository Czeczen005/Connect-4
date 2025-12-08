//
// Created by patry on 06.12.2025.
//

#ifndef CMAKESFMLPROJECT_BOARD_H
#define CMAKESFMLPROJECT_BOARD_H

enum class BoardState {
    Empty = 0,
    Player1 = 1,
    Player2 = 2
};

class Board {
    // zmienne static constexpr -> wartosci staja się znane w czasie kompilacji
    static constexpr int rows = 7;
    static constexpr  int cols = 6;
    BoardState grid[rows][cols] = {};
public:
    Board(){
        for (auto & i : grid){
            for (auto & j : i) {
                j = BoardState::Empty;
            }
        }
    }
    static int getRows(){return rows;}
    static int getCols(){return cols;}

    // Metoda do wrzucania żeton-a (zajmowanie pola)
    bool MakeMove(int col, BoardState player) {
        if (col < 0 || col >= cols) return false;
        for (int i = rows - 1; i > -1; i--) {
            if (grid[i][col] == BoardState::Empty) {
                grid[i][col] = player;
                return true;
            }
        }
        return false;
    }
    // Metoda cofania ruchu (wazna pod AI)
    void UndoMove(int col) {
        for (auto & i : grid) {
            if (i[col] != BoardState::Empty) {
                i[col] = BoardState::Empty;
                return;
            }
        }
    }

    [[nodiscard]] BoardState GetField(int row, int col)const{return grid[row][col];}
    bool CheckWin(BoardState player);

};
#endif //CMAKESFMLPROJECT_BOARD_H