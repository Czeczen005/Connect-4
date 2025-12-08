#include <SFML/Graphics.hpp>
#include <iostream> // Do wypisywania w konsoli

#include "Board.h"
#include "VisualizationMove.h"
// 6x7 -plansza
int main()
{
    Board logicBoard;
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

        window.clear(sf::Color::Black);
        visualizer.drawBoard(window, logicBoard);
        window.display();
    }
}