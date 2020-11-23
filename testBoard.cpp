//Main for testing Board

#include <iostream>

#include "boardwindow.h"
#include "startwindow.h"
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StartWindow start;
    start.showFullScreen();
    start.setStyleSheet("StartWindow {border-image: url(:/Images/startBackground.png);}");
    return a.exec();
}
