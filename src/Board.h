//
// Created by patry on 06.12.2025.
//

#ifndef CMAKESFMLPROJECT_BOARD_H
#define CMAKESFMLPROJECT_BOARD_H

#include <iostream>

enum class BoardState {
    Empty = 0,
    Player1 = 1,
    Player2 = 2
};

class Board {
    // zmienne static constexpr -> wartosci staja się znane w czasie kompilacji
    static constexpr int rows = 6;
    static constexpr  int cols = 7;
    BoardState grid[rows][cols] = {};
public:
    // Konstruktor
    Board(){
        for (auto & i : grid){
            for (auto & j : i) {
                j = BoardState::Empty;
            }
        }
    }
    // Gettery
    static int getRows(){return rows;}
    static int getCols(){return cols;}

    // Podglad tablicy
    void ShowBoard() {
        for (int i = 0; i< rows; i++) {
            for (int j = 0; j< cols; j++) {
                std::cout << static_cast<int>(grid[i][j]) << " ";
            }
            std::cout << std::endl;
        }
    }

    // Metoda do wrzucania żeton-a (zajmowanie pola)
    int MakeMove(int col, BoardState player) {
        if (col < 0 || col >= cols) return false;
        for (int i = rows - 1; i > -1; i--) {
            if (grid[i][col] == BoardState::Empty) {
                grid[i][col] = player;
                return i;
            }
        }
        return -1;
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
    // Getter kontretnej komorki
    [[nodiscard]] BoardState GetField(int row, int col)const{return grid[row][col];}
    // Sprawdzanie wygranej
    bool CheckWin(int row, int col ,BoardState player) {
        // Tablice kierunkow: {ROW, COL}
        // Poziom {0,1}, Pion {1, 0}. Skos \ {1, 1}, Skos / {1, -1}
        int direction[4][2] = {{0,1}, {1, 0}, {1, 1}, {1, -1}};

        for (auto& d : direction) {
            int dRow = d[0];
            int dCol = d[1];
            int count = 1;

            for (int st = 1; st < 4; st++) {
                int r = row + st * dRow;
                int c = col + st * dCol;

                if (r >= 0 && r < rows && c>= 0 && c < cols && grid[r][c] == player) {
                    count++;
                }else {
                    break;
                }
            }

            for (int st = 1; st < 4; st++) {
                int r = row - st * dRow;
                int c = col - st * dCol;
                if (r >= 0 && r < rows && c>= 0 && c < cols && grid[r][c] == player) {
                    count++;
                }else {
                    break;
                }
            }
            if (count >= 4) return true;
        }
        return false;
    }

};
#endif //CMAKESFMLPROJECT_BOARD_H