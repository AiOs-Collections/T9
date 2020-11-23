#ifndef PLAYER_H
#define PLAYER_H

#include "board.h"
#include "piece.h"
#include "tile.h"
#include "AI.h"
#include <vector>
#include <iostream>
#include <QThread>
using namespace std;

class Board;

class Player{
private:
    string name;
    vector<Piece*> pieces;
    string color;
    Board *board;
    void findPieces();
    char player_type;
    bool drawing;
    bool forfeit;
    int draw_count;
    bool makeMove(Tile start, Tile end);
    AI* agent;
public:
    //constructor
        Player(string n, string c, Board *b, AI* a=nullptr);
        Player(const Player& p, Board* newBoard);

    //accessors
        std::string getName() const             { return name; }
        std::string getColor() const            { return color; }
        std::vector<Piece *> getPieces()        { return pieces; }
        bool isDrawing() const                  { return drawing; }
        int getDrawCount() const                { return draw_count; }
        bool isForfeit() const                  { return forfeit; }
        Board* getBoard() const	                { return board; }
        char getType() const                    { return player_type; }
        AI* getAgent() const                    { return agent;}
    //mutators
        void setName(std::string n) { name = n; }
        void setColor(std::string c) { color = c; }
        void setType(char t) { player_type = t; }
        //returns true on successful removal of piece pointer
        bool removePiece(Piece *p);
        void startDraw();
        void incrementDraw() { draw_count++; }
        void stopDrawing();
        void setDraw(bool d) {drawing = d;}
        void setForfeit(bool f) {forfeit = f;}
        void setDrawCount(int c) {draw_count = c;}
        void forfeitGame() { forfeit = true; }
        void setPieces(vector<Piece*> pcs) {pieces = pcs;}
        void setAgent(AI *a){agent = a;}

    //utility
        //returns true if a particular piece is owned by the player
        bool hasPiece(Piece *p);
        void takeTurn(int gx, int gy, int x, int y);
};

#endif
