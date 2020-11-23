#ifndef PAUSEWINDOW_H
#define PAUSEWINDOW_H

#include <QMainWindow>
#include <iostream>
#include "sidewidget.h"

namespace Ui {
class PauseWindow;
}

class PauseWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PauseWindow(QWidget *parent = nullptr);
    ~PauseWindow();
    void setSide(sideWidget* side){s = side;}
    void switchOO(){optionsOpened=false;}
    sideWidget* getSide(){return s;}
    void setSS();

private:
    Ui::PauseWindow *ui;
    sideWidget* s;
    int optionsOpened;

private slots:
    void RequestDraw();
    void Options();
    void ExitGame();
    void Resume();
    void on_ReturnTitle_clicked();
    void on_NewGame_clicked();
    void closeEvent (QCloseEvent *event);
};

#endif // PAUSEWINDOW_H
