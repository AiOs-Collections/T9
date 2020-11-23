#include "AI.h"
#include "Player.h"
#include "board.h"
#include "validmove.cpp"

std::vector<Tile> AI::getNextMove(){
    moves->findMoves(*player);
    switch (difficulty){
        case 0:{
            int choice = std::rand() % moves->total_moves;
            return moves->moves[choice];
        }
        break;

    }
}
