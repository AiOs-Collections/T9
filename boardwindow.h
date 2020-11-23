#ifndef BOARDWINDOW_H
#define BOARDWINDOW_H

#include "board.h"
#include <QMainWindow>
#include <QDesktopWidget>
#include <QFormLayout>
#include <QFrame>
#include <QApplication>
#include <QMouseEvent>

namespace Ui {
class BoardWindow;
}

class BoardWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit BoardWindow(QWidget *parent = nullptr, int t=0, int ts=80, int bs=640);
    ~BoardWindow();
    void setBoard(Board *a){b=a;}
    void setTheme(int t){theme = t;}
    int getTheme(){return theme;}
    void setSL(int s){soundlevel = s;}
    void setML(int s){musiclevel = s;}
    void setMS(bool s){mutesound = s;}
    void setMM(bool s){mutemusic = s;}
    void setFS(bool s){fullscreen=s;}
    void setBS(int s){boardsize=s;}
    bool getMS(){return mutesound;}
    bool getMM(){return mutemusic;}
    int getBS(){return boardsize;}
    bool getFS(){return fullscreen;}
    int getTS(){return tilesize;}
    int getML(){return musiclevel;}
    int getSL(){return soundlevel;}
    void setTS(){tilesize=(boardsize/8);}
    void setPause(bool p){isPaused=p;}
    void resize();
    Board* getBoard(){return b;}
    void setFrame(QFrame* frame){f=frame;}
    void ThemeChange();
    QFrame* getFrame(){return f;}


private:
    Ui::BoardWindow *ui;
    Board* b;
    QFrame* f;
    bool isPaused;
    int theme;
    int soundlevel;
    int musiclevel;
    bool mutesound;
    bool mutemusic;
    bool fullscreen;
    int boardsize;
    int tilesize;
};

#endif // BOARDWINDOW_H
