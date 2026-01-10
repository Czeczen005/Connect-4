#ifndef CMAKESFMLPROJECT_FUNCTIONGAME_H
#define CMAKESFMLPROJECT_FUNCTIONGAME_H
class Board;
enum class BoardState;
class AlgoritmChoice;
class HumanPlayer;

enum class GameMode;
void waitSeconds(float seconds);
AlgoritmChoice* createStrategy(Board& board, BoardState playerID);
void PlayerVsPlayer(Board& board, HumanPlayer& p1, HumanPlayer& p2);
void PlayerVsAI(Board& board, HumanPlayer& p1, AlgoritmChoice* ai,bool& isTurnAi1);
void AIvsAI(Board &board, AlgoritmChoice *ai1, AlgoritmChoice *ai2, bool& isTurnAi1 );
void OneGame();
void Simulation(int numberSymulation);



#endif //CMAKESFMLPROJECT_FUNCTIONGAME_H