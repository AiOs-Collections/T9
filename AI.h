#ifndef AI_H
#define AI_H

//#include "board.h"
//#include "Player.h"
#include "Tile.h"
//#include "validmove.cpp"
#include <cstdlib>
#include <ctime>
#include <vector>

class Player;
struct ValidMove;

class AI{
private:
    int difficulty;   //0 is easiest - higher is harder
    Player *player;
    ValidMove* moves;

  public:
    AI(Player *p){ player = p; moves = nullptr; std::srand(std::time(nullptr)); }
//accessors
    int getDifficulty() { return difficulty; }
//mutators
    void setDifficulty(int d) { difficulty = d; }
    void setValidMoveStruct(ValidMove *vm) { moves = vm; }
//utility
    std::vector<Tile> getNextMove();
};

#endif
