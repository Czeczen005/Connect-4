#include <iostream>
#include <fstream>
#include <ctime>
#include <algorithm>
#include "functionGame.h"

int main()
{
    std::srand(std::time(nullptr));
    GameMode gameMode;
    int modeInput = 0;
    std::cout<<"Wybierz tryb"<<std::endl;
    std::cout<<"SYMULACJA - 1"<<std::endl;
    std::cout<<"Pojedyncza rozgrywka - 2"<<std::endl;
    std::cin >> modeInput;
    if (modeInput == 1){
        int sym = 0;
        std::cout<<"Jak duzo symulacji chcesz wykonac?"<<std::endl;
        std::cin >> sym;
        Simulation(sym);
    }else if (modeInput == 2) {
        OneGame();
    }else {
        std::cout<<" " << std::endl;
    }
    return 0;
}