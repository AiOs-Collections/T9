#ifndef SIDEWIDGET_H
#define SIDEWIDGET_H

#include <QWidget>
#include "boardwindow.h"
namespace Ui {
class sideWidget;
}

class sideWidget : public QWidget
{
    Q_OBJECT

public:
    explicit sideWidget(QWidget *parent = nullptr, string p1 = "Player 1", string p2 = "Player2");
    ~sideWidget();
    BoardWindow* getBoardWindow(){return b;}
    void togglePause(){ if(isPaused==true){
                            isPaused=false;}
                        else if(isPaused==false){
                            isPaused=true;};}
    bool getIsPaused(){return isPaused;}
    void setBoardWindow(BoardWindow* board){b=board;}
    void themeChange();
    Ui::sideWidget* getUI(){return ui;}

private:
    Ui::sideWidget *ui;
    BoardWindow* b;
    bool isPaused;

private slots:
    void on_pause_clicked();
    void closeEvent (QCloseEvent *event);
};

#endif // SIDEWIDGET_H
