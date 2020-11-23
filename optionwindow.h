#ifndef OPTIONS_H
#define OPTIONS_H


#include "pausewindow.h"
#include "startwindow.h"
#include <QMainWindow>
#include <iostream>
#include <QMouseEvent>

namespace Ui {
class OptionWindow;
}

class OptionWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit OptionWindow(QWidget *parent = nullptr, StartWindow * sw = nullptr, PauseWindow * pw = nullptr);
    ~OptionWindow();
    void setStartWindow(StartWindow* sw){w=sw;}
    void setPauseWindow(PauseWindow* pw){p=pw;}
    void changeTheme();
private slots:
    void on_Display_clicked();

    void on_Audio_clicked();

    void on_Apply_clicked();

    void on_Quit_clicked();

    void on_Option3Check_stateChanged(int arg1);

    void on_Option4Check_stateChanged(int arg1);

    void on_Option2Slider_valueChanged(int value);

    void on_Option1Slider_valueChanged(int value);

    void closeEvent (QCloseEvent *event);


private:
    Ui::OptionWindow *ui;
    //void mousePressEvent(QMouseEvent *event);
    //void mouseMoveEvent(QMouseEvent *event);
    PauseWindow *p;
    StartWindow *w;
    int m_nMouseClick_X_Coordinate;
    int m_nMouseClick_Y_Coordinate;
    int option1;
    int option2;
    bool option3;
    bool option4;
    int theme;
    int tabtarget;

};

#endif // OPTIONS_H
