//piece.h

#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include <QPushButton>
#include <QObject>
#include <QWidget>
#include <QApplication>
#include <QDesktopWidget>
using namespace std;

class Piece : public QPushButton
{
	private:
		string color;
		int posX, posY;
		bool taken;
		bool king;
        bool direction;
		
	public:
        explicit Piece(QWidget* parent = nullptr, string c="", int x =0, int y=0);
        Piece(const Piece& p);
        virtual ~Piece();
		void setColor( string c);
		void changePos( int x, int y);
        void buildPiece(int t, int tilesize);
        int getX(){return posX;}
        int getY(){return posY;}
        vector<vector<int>> moveModifiers();
		void beenTaken() { taken=true;}
		void makeKing(){ king=true;}
        bool isKing(){return king;}
		string getColor(){ return color;}
	
};

#endif
