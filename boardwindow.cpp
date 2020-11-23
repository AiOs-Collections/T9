#include "board.h"
#include "boardwindow.h"
#include "ui_boardwindow.h"


BoardWindow::BoardWindow(QWidget *parent, int t, int ts, int bs) :
    QMainWindow(parent),
    ui(new Ui::BoardWindow)
{
    ui->setupUi(this);
    theme = t;
    boardsize = bs;
    tilesize = ts;
    isPaused=false;
    centralWidget()->layout()->setAlignment(Qt::AlignCenter);
    QFrame* frame = new QFrame;
    this->setFrame(frame);
    frame->setLayout(new QHBoxLayout);
    frame->layout()->setAlignment(Qt::AlignCenter);
    frame->setMinimumSize(100+boardsize,100+boardsize);
    frame->setStyleSheet("QFrame {background-color: rgb(255, 255, 255)}");
    Board * b = new Board(this, theme, tilesize, boardsize);
    b->setLayout(new QVBoxLayout);
    b->setMinimumSize(80+boardsize,80+boardsize);
    frame->layout()->addWidget(b);
    centralWidget()->layout()->addWidget(frame);
    this->setMinimumSize(100+boardsize, 100+boardsize);
    this->setBoard(b);
}

void BoardWindow::resize()
{

    if(boardsize+80<=200)
    {
        f->setMinimumSize(220, 220);
        b->setMinimumSize(200,200);
        this->setMinimumSize(220,220);
    }
    else if(boardsize+80>200)
    {
        f->setMinimumSize(100+boardsize,100+boardsize);
        b->setMinimumSize(80+boardsize,80+boardsize);
        this->setMinimumSize(100+boardsize, 100+boardsize);
    }
    b->rescale();
}

BoardWindow::~BoardWindow()
{
    delete ui;
}

/*void BoardWindow::mousePressEvent(QMouseEvent *event) {
    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();
}

void BoardWindow::mouseMoveEvent(QMouseEvent *event) {
    move(event->globalX()-m_nMouseClick_X_Coordinate,event->globalY()-m_nMouseClick_Y_Coordinate);
}
*/

void BoardWindow::ThemeChange(){
    b->setTheme(theme);
    if(theme==0)
    {
        for (int x = MIN_X; x < MAX_X; x++) {
            for (int y = MIN_Y; y < MAX_Y; y++)
            {
                if(b->getTile(x, y)->getUsable()==true)
                {
                    b->getTile(x,y)->setIcon(QIcon(":/Images/Black-Tile.png"));
                }
                if(b->getTile(x, y)->getUsable()==false)
                {
                    b->getTile(x,y)->setIcon(QIcon(":/Images/Grey-Tile.png"));
                }
                if(b->getTile(x, y)->getOccupied()==true)
                {
                    if(b->getPiece(x,y)->getColor()=="white" &&
                            b->getPiece(x,y)->isKing()==true)
                    {
                        b->getPiece(x,y)->setIcon(QIcon(":/Images/White-King-Piece.png"));
                    }
                    if(b->getPiece(x,y)->getColor()=="black" &&
                            b->getPiece(x,y)->isKing()==true)
                    {
                        b->getPiece(x,y)->setIcon(QIcon(":/Images/Black-King-Piece.png"));
                    }
                    if(b->getPiece(x,y)->getColor()=="white" &&
                            b->getPiece(x,y)->isKing()==false)
                    {
                        b->getPiece(x,y)->setIcon(QIcon(":/Images/White-Normal-Piece.png"));
                    }
                    if(b->getPiece(x,y)->getColor()=="black" &&
                            b->getPiece(x,y)->isKing()==false)
                    {
                        b->getPiece(x,y)->setIcon(QIcon(":/Images/Black-Normal-Piece.png"));
                    }
                }
            }
        }
        b->setStyleSheet("background-color: rgb(0,0,0);");
        setStyleSheet("BoardWindow {border-image: url(:/Images/BoardBG1.png);}");
        setCursor(Qt::ArrowCursor);
    }
    else if(theme==1)
    {
        for (int x = MIN_X; x < MAX_X; x++) {
            for (int y = MIN_Y; y < MAX_Y; y++)
            {
                if(b->getTile(x, y)->getUsable()==true)
                {
                    b->getTile(x,y)->setIcon(QIcon(":/Images/Blue-Tile.png"));
                }
                if(b->getTile(x, y)->getUsable()==false)
                {
                    b->getTile(x,y)->setIcon(QIcon(":/Images/Orange-Tile.png"));
                }
                if(b->getTile(x, y)->getOccupied()==true)
                {
                    if(b->getPiece(x,y)->getColor()=="white" &&
                            b->getPiece(x,y)->isKing()==false)
                    {
                        b->getPiece(x,y)->setIcon(QIcon(":/Images/TempWhite.png"));
                    }
                    if(b->getPiece(x,y)->getColor()=="black" &&
                           b->getPiece(x,y)->isKing()==false)
                    {
                        b->getPiece(x,y)->setIcon(QIcon(":/Images/TempBlack.png"));
                    }
                    if(b->getPiece(x,y)->getColor()=="white" &&
                            b->getPiece(x,y)->isKing()==true)
                    {
                        b->getPiece(x,y)->setIcon(QIcon(":/Images/TempWhiteKing.png"));
                    }
                    if(b->getPiece(x,y)->getColor()=="black" &&
                            b->getPiece(x,y)->isKing()==true)
                    {
                        b->getPiece(x,y)->setIcon(QIcon(":/Images/TempBlackKing.png"));
                    }
                }
            }
        }

        b->setStyleSheet("background-image: url(:/Images/Blue-Tile.png);");
        setStyleSheet("BoardWindow {border-image: url(:/Images/BoardBG2.png);}");
        setCursor(QCursor(QPixmap(":/Images/Cursor.png"),25,25));
    }
}

