// Board.h file
#ifndef BOARD_H
#define BOARD_H

const int BOARD_SIZE = 8;

#include <iostream>
#include <QObject>
#include <QWidget>
#include <QApplication>
#include <QDesktopWidget>
#include <QHBoxLayout>
#include <ui_sidewidget.h>
#include "Player.h"
#include "tile.h"
#include <QThread>

using namespace std;

const int MAX_X = 8;
const int MAX_Y = 8;
const int MIN_X = 0;
const int MIN_Y = 0;
const int MAX_PIECES_SIDE = 12;
const int MAX_PIECES = 24;

class Player;

class Board : public QWidget
{
    Q_OBJECT
	public:
    explicit Board(QWidget *parent = nullptr, int t=0, int ts=80, int bs=640); //Initializes a board as described at the top of board.cpp
    Board(const Board&b);
	Piece* getPiece( int xcord, int ycord); //returns a pointer to the piece at the location given
	void output(); //terminal output of current boardstate
    void trueOutput();
    int returnBoardState(){return boardstate;}
    void setBoardState(int i){boardstate=i;}
    bool fullscreen;
    bool move(Tile Start, Tile End);
    vector<Player *> getPlayers(){return players;}
    void movePiece(int x, int y);
    void turnKing(int x, int y);
    void setTheme(int t){theme = t;}
    int getTheme(){return theme;}
    void setBS(int b){boardsize =b;}
    void setTS(int t){tilesize =t;}
    void setIsPaused(bool p){isPaused = p;}
    void rescale();
    Tile* getTile(int x, int y){return state[x][y];}
    void setwdg(QWidget* wdg){w=wdg;}
    QWidget *getwdg(){return w;}
    void setSWUI(Ui::sideWidget * sw){s=sw;}
    void addPlayer(Player *p){players.push_back(p);}
    Player *checkWins();
    void deleteBoard();
    Piece* getSP(){return selectedPiece;}
    void setSP(Piece *p){selectedPiece = p;}
    void setCurrentPlayer(Player * p){currentPlayer=p;}
    Player* getCurrentPlayer(){return currentPlayer;}
    void nextPlayer();
    void incrementNAD(string c);
    void incrementTurn();
    void delay(){QThread::sleep(2);}
    void copyBoard(Board *b);
    /*
	Board* oneMove( int startX, int startY, int endX, int endY); //Returns the board after one move is performed
	Board** totalMove(); //Returns a list of single moves made during one player's turn
    */
public slots:
    void tileClicked(int x, int y);
    void pieceClicked(int x, int y);

	private:
    vector<Player *> players;
    Player* currentPlayer;
    QWidget* w;
    Ui::sideWidget * s;
    int theme;
    int boardstate;
    int boardsize;
    int tilesize;
    bool isPaused;
    Tile* selectedTile;
    Piece* selectedPiece;
    Tile* state[MAX_X][MAX_Y]; //The board
	
};

#endif
