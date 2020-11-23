#ifndef TILE_H
#define TILE_H

#include <QPushButton>
#include <QHBoxLayout>
#include "piece.h"

class Tile : public QPushButton
{
    private:
    int x, y;
    bool isUsable;
    bool isOccupied;
    Piece* currentPiece;
    bool validmove;

    public:
    explicit Tile(QWidget* parent = nullptr);
    virtual ~Tile();
    bool getOccupied(){return isOccupied;}
    bool getUsable(){return isUsable;}
    void setOccupied(bool occupied){isOccupied = occupied;}
    void setPiece(Piece* p){currentPiece = p; isOccupied = true;}
    void removePiece();
    void addPiece(int x, int y);
    void setUsable(bool u){isUsable=u;}
    void setLocation(int a, int b){x=a; y=b;}
    int getX(){return x;}
    int getY(){return y;}
    Piece* getPiece(){return currentPiece;}
    void setTile(int x, int y, bool b, int t, int tilesize);
    void isValidMove(){validmove=true;}
    void setToDefault(){validmove=false;}
    Tile(const Tile& t); // Copy ctor
    Tile& operator=(const Tile& t);
    Tile(int init_x, int init_y)
    {
        currentPiece = nullptr;
        x = init_x;
        y = init_y;
    }
};

#endif // TILE_H
