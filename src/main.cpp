#include <SFML/Graphics.hpp>
#include <iostream>
#include "AlgorithmAI.h"
#include "Board.h"
#include "VisualizationMove.h"

// 6x7 - plansza

void PlayerVsPlayer(Board& board, HumanPlayer& p1, HumanPlayer& p2) {
    // --- TURA GRACZA 1 ---
    if (p1.getTurn()) {
        p1.setCols();
        int lastRow = board.MakeMove(p1.getCols() - 1, p1.getPlayerState());
        while (lastRow == -1) {
            std::cout << "Maksymalna liczba zetonow lub zla kolumna. Podaj inna: " << std::endl;
            p1.setCols();
            lastRow = board.MakeMove(p1.getCols() - 1, p1.getPlayerState());
        }
        // Sprawdzamy wygraną
        if (board.CheckWin(lastRow, p1.getCols() - 1, p1.getPlayerState())) {
            std::cout << "WYGRAL GRACZ 1" << std::endl;
        }
        p1.setTurn(false); // Blokujemy P1
        p2.setTurn(true);  // Odblokowujemy P2
    }

    // --- TURA GRACZA 2 ---
    else if (p2.getTurn()) {
        p2.setCols();
        int lastRow = board.MakeMove(p2.getCols() - 1, p2.getPlayerState());
        while (lastRow == -1) {
            std::cout << "Maksymalna liczba zetonow lub zla kolumna. Podaj inna: " << std::endl;
            p2.setCols();
            lastRow = board.MakeMove(p2.getCols() - 1, p2.getPlayerState());
        }
        if (board.CheckWin(lastRow, p2.getCols() - 1, p2.getPlayerState())) {
            std::cout << "WYGRAL GRACZ 2" << std::endl;
        }
        p2.setTurn(false);
        p1.setTurn(true);
    }
}


void AIvsAI() {

}



int main()
{
    Board logicBoard;
    std::srand(std::time(nullptr));
    HumanPlayer p1 = HumanPlayer(BoardState::Player1);
    HumanPlayer p2 = HumanPlayer(BoardState::Player2);
    AlgorithmNaive AI1 = AlgorithmNaive(logicBoard);
    AlgorithmRandom AI2 = AlgorithmRandom(logicBoard);
    VisualizationMove visualizer;
    sf::ContextSettings contextSettings;
    contextSettings.antiAliasingLevel = 100;
    auto window = sf::RenderWindow(
    sf::VideoMode({400u, 400u}),
    "Connect 4",
    sf::Style::Default,
    sf::State::Windowed,
    contextSettings
    );

    window.setFramerateLimit(144);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }
        window.clear(sf::Color::White);
        visualizer.drawBoard(window, logicBoard);
        window.display();
        PlayerVsPlayer(logicBoard, p1, p2);
    }
}