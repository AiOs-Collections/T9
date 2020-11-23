#ifndef VALIDMOVE_CPP
#define VALIDMOVE_CPP

#include <vector>
#include "Tile.h"
#include "Player.h"
#include <cmath>   //used for std::abs()

struct MoveNode{
    Tile start;
    std::vector<Tile> end_positions;
};

struct ValidMove{
    int total_moves;
    //2 elements, x then y
    std::vector<std::vector<Tile>> moves;

    void findMoves(Player &p){
        moves.clear();
        total_moves = 0;

        std::vector<Piece *> player_pieces;
        for(int i = 0; i < p.getPieces().size(); i ++)	{
            player_pieces.push_back(new Piece(*(p.getPieces().at(i))));
        }

        for (int i = 0; i < player_pieces.size(); i++){
            Piece *piece = player_pieces[i];
            std::vector<std::vector<int>> move_mods = piece->moveModifiers();
            for (int j = 0; j < move_mods.size(); j++){
                for (int k = 1; k <= 2; k++){   //tests for single moves and jump moves
                    int x = piece->getX(),
                        y = piece->getY();
                    Tile start(x, y),
                         end((x + (k * move_mods[j][0])), (y + (k * move_mods[j][1])));
                    Board tmp(*p.getBoard());
                    tmp.copyBoard(p.getBoard());
            //p.getBoard()->trueOutput();
                    if(tmp.move(start, end)){
                        std::vector<Tile> move_pair;
                        move_pair.push_back(start);
                        move_pair.push_back(end);
                        moves.push_back(move_pair);
                        total_moves++;
                    }
                    tmp.deleteBoard();
            //p.getBoard()->trueOutput();
                }
            }
        }

        return;
    }
};

#endif
