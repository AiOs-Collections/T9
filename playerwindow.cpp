#include "playerwindow.h"
#include "ui_playerwindow.h"

PlayerWindow::PlayerWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlayerWindow)
{
    ui->setupUi(this);
}

PlayerWindow::~PlayerWindow()
{
    delete ui;
}
