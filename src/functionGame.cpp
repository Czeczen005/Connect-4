#include <SFML/Graphics.hpp>
#include <iostream>
#include "AlgorithmAI.h"
#include "Board.h"
#include "VisualizationMove.h"
#include "AlgorithmChoice.h"

enum class GameMode {
    OneGame = 0,
    Simulation = 1,
    PlayerVsPlayer = 2,
    PlayerVsAI = 3,
    AIvsAI = 4
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
    std::cout << "5. GreedyRandom" << std::endl;
    std::cout << "6. Brute Force"<<std::endl;
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
            return new AlgoritmGreedy(board, playerID);
        case 5:
            return new AlgorithmGreedyRandom(board, playerID);
        case 6:
            return new AlgorithmBruteForce(board, playerID);
        default:
            std::cout << "Nieprawidlowy wybor, ustawiam Random" << std::endl;
            return new AlgoritmRandom(board);
    }
}


void PlayerVsPlayer(Board& board, HumanPlayer& p1, HumanPlayer& p2, bool& somebodyWon) {
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
            somebodyWon = true;
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
            somebodyWon = true;
        }
        p2.setTurn(false);
        p1.setTurn(true);
    }
}

// Logika dla trybu Gracz vs AI
void PlayerVsAI(Board& board, HumanPlayer& p1, AlgoritmChoice* ai,bool& isTurnAi1, bool& somebodyWon) {
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
            somebodyWon = true;
        }
        p1.setTurn(false);
        isTurnAi1 = true; // Przekazanie tury AI
        }
         //  TURA AI 2
    else {
        std::cout << "RUCH AI 2" << std::endl;
        int column = ai->MakeChoice();
        if (column != -1){
            int row = board.MakeMove(column, BoardState::Player2);
            if (board.CheckWin(row, column, BoardState::Player2)) {
                std::cout <<"Wygral AI - " <<ai->getName()<< std::endl;
                somebodyWon = true;
            }
            isTurnAi1 = true; // Przekazanie tury
        } else {
            std::cout<<"REMIS (brak ruchow)"<<std::endl;
            somebodyWon = true;
        }
        p1.setTurn(true);
        isTurnAi1 = false;
    }
}

// Funkcja AI vs AI
void AIvsAI(Board &board, AlgoritmChoice *ai1, AlgoritmChoice *ai2, bool& isTurnAi1, bool& somebodyWon) {
    // TURA AI 1
    if (isTurnAi1) {
        std::cout << "RUCH AI 1" << std::endl;
        int column = ai1->MakeChoice();
        if (column != -1) {
            int row = board.MakeMove(column, BoardState::Player1);
            if (board.CheckWin(row, column, BoardState::Player1)) {
                std::cout <<"Wygral AI - " <<ai1->getName()<< std::endl;
                somebodyWon = true;
            }
            isTurnAi1 = false; // Przekazanie tury
        } else {
            std::cout<<"REMIS (brak ruchow)"<<std::endl;
            somebodyWon = true;
        }
    }
    // TURA AI 2
    else {
        std::cout << "RUCH AI 2" << std::endl;
        int column = ai2->MakeChoice();
        if (column != -1){
            int row = board.MakeMove(column, BoardState::Player2);
            if (board.CheckWin(row, column, BoardState::Player2)) {
                std::cout <<"Wygral AI - " <<ai2->getName()<< std::endl;
                somebodyWon = true;
            }
            isTurnAi1 = true; // Przekazanie tury
        } else {
            std::cout<<"REMIS (brak ruchow)"<<std::endl;
            somebodyWon = true;
        }
    }
}

void OneGame() {
    Board logicBoard;
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
    modeInput += 1;
    GameMode gameMode = static_cast<GameMode>(modeInput);
    if (gameMode == GameMode::PlayerVsAI) {
        ai2 = createStrategy(logicBoard, BoardState::Player2);
    }
    else if (gameMode == GameMode::AIvsAI) {
        ai1 = createStrategy(logicBoard, BoardState::Player1);
        ai2 = createStrategy(logicBoard, BoardState::Player2);
    }

    bool isTurnAi1 = true;
    bool ended = false;
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
        if (!ended) {
            switch (gameMode)
            {
                case GameMode::PlayerVsPlayer:
                    if (logicBoard.freeFields() == 0) {
                        std::cout<<"REMIS!"<<std::endl;
                        ended = true;
                    }
                    PlayerVsPlayer(logicBoard, p1, p2, ended);
                    break;
                case GameMode::PlayerVsAI:
                    if (isTurnAi1) waitSeconds(0.5f);
                    PlayerVsAI(logicBoard, p1, ai2, isTurnAi1, ended);
                    break;
                case GameMode::AIvsAI:
                    waitSeconds(0.5f);
                    AIvsAI(logicBoard, ai1, ai2, isTurnAi1, ended);
                    break;
                default:
                    std::cout<<"nwm po co to ale jest "<<std::endl;
            }
        }

    }
}

void Simulation(int numberSymulation) {
    Board logicBoard;
    // Gracze ludzcy
    HumanPlayer p1 = HumanPlayer(BoardState::Player1);
    HumanPlayer p2 = HumanPlayer(BoardState::Player2);
    // AI
    AlgoritmChoice* ai1 = nullptr;
    AlgoritmChoice* ai2 = nullptr;
    // Menu wyboru
    std::cout << "Wybierz tryb gry:\n1. Gracz vs Gracz\n2. Gracz vs AI \n3. AI vs AI\nPodaj numer trybu: ";
    int modeInput;
    std::cin >> modeInput;
    modeInput += 1;
    GameMode gameMode = static_cast<GameMode>(modeInput);
    if (gameMode == GameMode::PlayerVsAI) {
        ai2 = createStrategy(logicBoard, BoardState::Player2);
    }
    else if (gameMode == GameMode::AIvsAI) {
        ai1 = createStrategy(logicBoard, BoardState::Player1);
        ai2 = createStrategy(logicBoard, BoardState::Player2);
    }
    bool isTurnAi1 = true;
    for (int i = 0; i < numberSymulation; i++) {
        bool ended = false;
        logicBoard.clearBoard();
        while (!ended){
            switch (gameMode)
            {
                case GameMode::PlayerVsPlayer:
                    if (logicBoard.freeFields() == 0) {
                        std::cout<<"REMIS!"<<std::endl;
                        ended = true;
                    }
                    PlayerVsPlayer(logicBoard, p1, p2, ended);
                    break;
                case GameMode::PlayerVsAI:
                    PlayerVsAI(logicBoard, p1, ai2, isTurnAi1, ended);
                    break;
                case GameMode::AIvsAI:
                    AIvsAI(logicBoard, ai1, ai2, isTurnAi1, ended);
                    break;
                default:
                    std::cout<<"nwm po co to ale jest "<<std::endl;
            }
        }
    }
}
