#include "tile.h"

Tile::Tile(QWidget* parent) : QPushButton (parent)
{
    currentPiece=nullptr;
    isUsable = false;
    isOccupied=false;
}

Tile::Tile(const Tile& t)
{
    x = t.x;
    y = t.y;
    if(t.currentPiece == nullptr)
        currentPiece = nullptr;
    else
        currentPiece = new Piece(*(t.currentPiece));
}

Tile& Tile::operator=(const Tile& t)
{
    x = t.x;
    y = t.y;
    if(t.currentPiece == nullptr)
        currentPiece = nullptr;
    else
        currentPiece = new Piece(*(t.currentPiece));

    return *this;
}

Tile::~Tile()
{

}


void Tile::setTile(int x, int y, bool b, int t, int tilesize)
{
    if(b==true)
    {
        setLocation(x, y);
        setUsable(b);
        setOccupied(false);
        setLayout(new QHBoxLayout);
        layout()->setAlignment(Qt::AlignCenter);
        layout()->setContentsMargins(0,0,0,0);
        if(t==0)
        {
        setStyleSheet("QPushButton:hover { border-image: url(:/Images/Black-Tile-Hover.png)}");}
        if(t==1)
        {
            setIcon(QIcon(":/Images/Blue-Tile.png"));
            setStyleSheet("QPushButton:hover { border-image: url(:/Images/Black-Tile-Hover.png)}");
        }
        setIconSize(QSize(10+tilesize,10+tilesize));
            setGeometry(x*(10+tilesize), (((10+tilesize)*8)-(10+tilesize))-(y*(10+tilesize)), 10+tilesize, 10+tilesize);
    }
    else if (b==false)
    {
        setLocation(x, y);
        setUsable(false);
        if(t==0){
        setIcon(QIcon(":/Images/Grey-Tile.png"));
        }
        if(t==1)
        {
            setIcon(QIcon(":/Images/Orange-Tile.png"));
        }
        setIconSize(QSize(10+tilesize,10+tilesize));
            setGeometry(x*(10+tilesize), (((10+tilesize)*8)-(10+tilesize))-(y*(10+tilesize)), 10+tilesize, 10+tilesize);
    }
}

void Tile::removePiece()
{
    layout()->removeWidget(currentPiece);
    setPiece(new Piece);
    setOccupied(false);
    currentPiece=nullptr;
}

void Tile::addPiece(int x, int y)
{
    currentPiece->changePos(x,y);
    setOccupied(true);
    layout()->addWidget(currentPiece);
}
