#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread> // Do sleepa (opcjonalnie)
#include "AlgorithmAI.h"
#include "Board.h"
#include "VisualizationMove.h"
// --- POPRAWKA 1: Dodano brakujący nagłówek ---
#include "AlgorithmChoice.h" 

// 6x7 - plansza
// stany obsługi trybu gry
enum class GameMode {
    PlayerVsPlayer = 1,
    PlayerVsAI = 2,
    AIvsAI = 3
};

// Funkcja pomocnicza do opóźnienia
void waitSeconds(float seconds) {
    sf::sleep(sf::seconds(seconds));
}


AlgoritmChoice* createStrategy(Board& board, BoardState playerID) {
    int choice;
    std::string playerName = (playerID == BoardState::Player1) ? "AI 1" : "AI 2";
    std::cout << "\n Wybierz strategie dla " << playerName << std::endl;
    std::cout << "1. Minimax" << std::endl;
    std::cout << "2. Random" << std::endl;
    std::cout << "3. Naive" << std::endl;
    std::cout << "4. Greedy" << std::endl;
    std::cin >> choice;
    switch (choice) {
        case 1:
            int depth;
            std::cout << "Podaj glebokosc dla Minimax";
            std::cin >> depth;
            return new Minimax(board, playerID, depth);
        case 2:
            return new AlgoritmRandom(board);
        case 3:
            return new AlgoritmNaive(board);
        case 4:
            return new AlgorithmGreedy(board, playerID);
        default:
            std::cout << "Nieprawidlowy wybor, ustawiam Random" << std::endl;
            return new AlgoritmRandom(board);
    }
}


void PlayerVsPlayer(Board& board, HumanPlayer& p1, HumanPlayer& p2) {
    //  TURA GRACZA 1 
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
            sf::sleep(sf::seconds(3)); 
            exit(0);
        }
        p1.setTurn(false); // Blokujemy P1
        p2.setTurn(true);  // Odblokowujemy P2
    }

    //  TURA GRACZA 2
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
            sf::sleep(sf::seconds(5));
            exit(0);
        }
        p2.setTurn(false);
        p1.setTurn(true);
    }
}

// Logika dla trybu Gracz vs AI 
void PlayerVsAI(Board& board, HumanPlayer& p1, AlgoritmChoice* ai,bool& isTurnAi1) {
    if (p1.getTurn()) {
        isTurnAi1 = false;
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
            sf::sleep(sf::seconds(3)); 
            exit(0);
        }
        p1.setTurn(false);
        isTurnAi1 = true; // Przekazanie tury AI
        } 
         //  TURA AI 2
    else { 
        std::cout << "RUCH AI 2" << std::endl;
        sf::sleep(sf::seconds(0.5f));  
        int column = ai->MakeChoice();
        
        if (column != -1){
            int row = board.MakeMove(column, BoardState::Player2);
            if (board.CheckWin(row, column, BoardState::Player2)) {
                std::cout <<"Wygral AI 2" << std::endl;
                sf::sleep(sf::seconds(3));
                exit(0);
            }
            isTurnAi1 = true; // Przekazanie tury
        } else {
            std::cout<<"REMIS (brak ruchow)"<<std::endl;
            sf::sleep(sf::seconds(5));
            exit(0);
        }
        p1.setTurn(true);
        isTurnAi1 = false; 
    }  
}

// Funkcja AI vs AI
void AIvsAI(Board &board, AlgoritmChoice *ai1, AlgoritmChoice *ai2, bool& isTurnAi1 ) {
    waitSeconds(0.5f); // Opóźnienie 

    // TURA AI 1 
    if (isTurnAi1) {
        std::cout << "RUCH AI 1 (Minimax)" << std::endl;
        int column = ai1->MakeChoice();

        if (column != -1) {
            int row = board.MakeMove(column, BoardState::Player1);
            if (board.CheckWin(row, column, BoardState::Player1)) {
                std::cout <<"Wygral AI 1" << std::endl;
                sf::sleep(sf::seconds(2));
                exit(0);
            }
            isTurnAi1 = false; // Przekazanie tury
        } else {
            std::cout<<"REMIS (brak ruchow)"<<std::endl;
            sf::sleep(sf::seconds(2));
            exit(0);
        }
    } 
    // TURA AI 2 
    else { 
        std::cout << "RUCH AI 2 (Minimax)" << std::endl;
        int column = ai2->MakeChoice();
        
        if (column != -1){
            int row = board.MakeMove(column, BoardState::Player2);
            if (board.CheckWin(row, column, BoardState::Player2)) {
                std::cout <<"Wygral AI 2" << std::endl;
                sf::sleep(sf::seconds(5));
                exit(0);
            }
            isTurnAi1 = true; // Przekazanie tury
        } else {
            std::cout<<"REMIS (brak ruchow)"<<std::endl;
            sf::sleep(sf::seconds(3));
            exit(0);
        }
    }
}

int main()
{
    Board logicBoard;
    std::srand(std::time(nullptr));
    
    // Gracze ludzcy
    HumanPlayer p1 = HumanPlayer(BoardState::Player1);
    HumanPlayer p2 = HumanPlayer(BoardState::Player2);
    
    // AI
    AlgoritmChoice* ai1 = nullptr;
    AlgoritmChoice* ai2 = nullptr;

    VisualizationMove visualizer;
    sf::ContextSettings contextSettings;
    contextSettings.antiAliasingLevel = 8; // 100 to za duzo, max to zazwyczaj 8 lub 16

    auto window = sf::RenderWindow(
        sf::VideoMode({400u, 400u}),
        "Connect 4",
        sf::Style::Default,
        sf::State::Windowed,
        contextSettings
    );
    window.setFramerateLimit(60); 

    // Menu wyboru
    std::cout << "Wybierz tryb gry:\n1. Gracz vs Gracz\n2. Gracz vs AI \n3. AI vs AI\nPodaj numer trybu: ";
    int modeInput;
    std::cin >> modeInput;
    GameMode gameMode = static_cast<GameMode>(modeInput);
    if (gameMode == GameMode::PlayerVsAI) {
        ai2 = createStrategy(logicBoard, BoardState::Player2);
    }
    else if (gameMode == GameMode::AIvsAI) {
        ai1 = createStrategy(logicBoard, BoardState::Player1);
        ai2 = createStrategy(logicBoard, BoardState::Player2);
    }
   

    bool isTurnAi1 = true;

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

        
        switch (gameMode)
        {
        case GameMode::PlayerVsPlayer:
            PlayerVsPlayer(logicBoard, p1, p2);
            break;

        case GameMode::PlayerVsAI: 
            PlayerVsAI(logicBoard, p1, ai2, isTurnAi1);
            break;

        case GameMode::AIvsAI:
            AIvsAI(logicBoard, ai1, ai2, isTurnAi1);
            break;
        
        default:
            AIvsAI(logicBoard, ai1, ai2, isTurnAi1);
            break;
        }

    }
}