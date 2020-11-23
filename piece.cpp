//piece.cpp
#include <iostream>

#include "piece.h"

using namespace std;

Piece::Piece(QWidget* parent, string c, int x, int y) : QPushButton (parent)
{
    setColor(c);
	taken=false;
	king=false;
    posX = x;
    posY = y;
    setAttribute(Qt::WA_DeleteOnClose);
}

Piece::Piece(const Piece& p)
{
    setColor(p.color);
    king = p.king;
    posX = p.posX;
    posY = p.posY;
}

Piece::~Piece()
{

}

void Piece::setColor( string c)
{
    color=c;
    //direction is true for up - white is up, otherwise down
    direction = (color == "white");
}

void Piece::changePos( int x, int y)
{
	posX=x;
	posY=y;
}

void Piece::buildPiece(int t, int tilesize){
    if(color=="white")
    {
        if(t==0)
        {
        setIcon(QIcon(":/Images/White-Normal-Piece.png"));
        }
        if(t==1)
        {
        setIcon(QIcon(":/Images/TempWhite.png"));
        setStyleSheet("Piece {background-color: rgb(116,255,240);}");
        }
        setIconSize(QSize(4+tilesize,4+tilesize));
        setMinimumSize(4+tilesize,4+tilesize);
            setGeometry(posX*(10+tilesize), (((10+tilesize)*8)-(10+tilesize))-(posY*(10+tilesize)), 10+tilesize, 10+tilesize);
        raise();

    }
    else if(color=="black")
    {
        if(t==0)
        {
        setIcon(QIcon(":/Images/Black-Normal-Piece.png"));
        }
        if(t==1)
        {
        setIcon(QIcon(":/Images/TempBlack.png"));
        setStyleSheet("Piece {background-color: rgb(116,255,240);}");
        }
        setIconSize(QSize(4+tilesize,4+tilesize));
        setMinimumSize(4+tilesize,4+tilesize);
            setGeometry(posX*(10+tilesize), (((10+tilesize)*8)-(10+tilesize))-(posY*(10+tilesize)), 10+tilesize, 10+tilesize);
        raise();
    }

}

vector<vector<int>> Piece::moveModifiers(){
    vector<vector<int>> modifiers;
    vector<int> modifier;

    if(!king){
        if(direction){	//allowed to move up the board
            //diagonal is up and over
            modifier.push_back(1);
            modifier.push_back(1);
            modifiers.push_back(modifier);
            modifier[0] = -1;
            modifiers.push_back(modifier);
        } else{
            modifier.push_back(-1);
            modifier.push_back(-1);
            modifiers.push_back(modifier);
            modifier[0] = 1;
            modifiers.push_back(modifier);
        }
    } else{
        modifier.push_back(1);
        modifier.push_back(-1);
        modifiers.push_back(modifier);
        modifier[1] = 1;
        modifiers.push_back(modifier);
        modifier[0] = -1;
        modifiers.push_back(modifier);
        modifier[1] = -1;
        modifiers.push_back(modifier);
    }
    return modifiers;
}
