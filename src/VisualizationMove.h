//
// Created by patry on 06.12.2025.
//

#ifndef CMAKESFMLPROJECT_VISUALIZATIONMOVE_H
#define CMAKESFMLPROJECT_VISUALIZATIONMOVE_H
#include <SFML/Graphics.hpp>
#include "Board.h"
class VisualizationMove {
    sf::Color boardC = sf::Color::White;
    sf::Color p1 = sf::Color::Blue;
    sf::Color p2 = sf::Color::Green;
public:
    void drawBoard(sf::RenderWindow& window,const Board& board){
        sf::Vector2u windowSize = window.getSize();
        int rows = board.getRows();
        int cols = board.getCols();
        float cellWidth = static_cast<float>(windowSize.x) / cols;
        float cellHeight = static_cast<float>(windowSize.y) / rows;
        float cellSize = std::min(cellWidth, cellHeight);
        float radius = (cellSize / 2.0f) *0.70f;
        float offsetX = (windowSize.x - (cols * cellSize)) / 2.0f;
        float offsetY = (windowSize.y - (rows * cellSize))/ 2.0f;

        for (int i = 0; i <rows; i++) {
            for (int j = 0 ; j<cols; j++) {
                sf::RectangleShape rect(sf::Vector2f({cellSize, cellSize}));
                rect.setPosition(sf::Vector2f(offsetX + j * cellSize, offsetY + i * cellSize));
                rect.setFillColor(boardC);
                rect.setOutlineColor(sf::Color::Black);
                rect.setOutlineThickness(2);
                window.draw(rect);
                sf::CircleShape coin(radius);
                coin.setOrigin(sf::Vector2f(radius, radius));
                coin.setPosition(sf::Vector2f(offsetX + j * cellSize + (cellSize / 2.0f), offsetY + i * cellSize + (cellSize / 2.0f)));
                BoardState state = board.GetField(i, j);
                if (state == BoardState::Player1) {
                    coin.setFillColor(p1);
                }
                else if (state == BoardState::Player2) {
                    coin.setFillColor(p2);
                }
                else {
                    coin.setFillColor(sf::Color::Black);
                }
                window.draw(coin);
            }
        }
    }
};
#endif //CMAKESFMLPROJECT_VISUALIZATIONMOVE_H