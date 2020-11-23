#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QMainWindow>
#include <iostream>
#include "boardwindow.h"
#include "sidewidget.h"

namespace Ui {
class StartWindow;
}

class StartWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StartWindow(QWidget *parent = nullptr, bool fs=true);
    ~StartWindow();
    void runBoard(int i);
    void transferPreferences(BoardWindow * b);
    void setTilesize(){tilesize = boardsize/8;}
    void switchOO(){optionsOpened=false;}
    int getBS(){return boardsize;}
    int getML(){return musiclevel;}
    int getSL(){return soundlevel;}
    int getTheme(){return theme;}
    bool getFS(){return fullscreen;}
    bool getMS(){return mutesound;}
    bool getMM(){return mutemusic;}
    void setBS(int bs){boardsize=bs;}
    void setML(int ml){musiclevel=ml;}
    void setSL(int sl){soundlevel=sl;}
    void setFS(bool fs){fullscreen=fs;}
    void setTheme(int t){theme=t;}
    void setMS(bool ms){mutesound=ms;}
    void setMM(bool mm){mutemusic=mm;}
    void LabelSize();
    void themeChange();

private:
    Ui::StartWindow *ui;
    int theme;
    int soundlevel;
    int musiclevel;
    bool mutesound;
    bool mutemusic;
    bool fullscreen;
    int boardsize;
    int tilesize;
    QPixmap p;
    bool optionsOpened;
    string player1name;
    string player2name;

private slots:
    void PvAI();
    void PvP();
    void on_Exit_clicked();
    void on_Options_clicked();
    void on_PlayerSetup_clicked();
    void on_Confirm_clicked(string p1, string p2);
    void on_AIvAI_clicked();
};

#endif // STARTWINDOW_H
