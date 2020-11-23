#include "pausewindow.h"
#include "sidewidget.h"
#include "ui_sidewidget.h"

sideWidget::sideWidget(QWidget *parent, string p1, string p2) :
    QWidget(parent),
    ui(new Ui::sideWidget)
{
    ui->setupUi(this);
    ui->Player1Name->setText(QString::fromStdString(p1));
    ui->Player2Name->setText(QString::fromStdString(p2));
    ui->Player->setText(QString::fromStdString(p1));
    ui->Turn->setNum(0);
    ui->Player1NA->setNum(12);
    ui->Player2NA->setNum(12);
    ui->Player1ND->setNum(0);
    ui->Player2ND->setNum(0);
    ui->Score->setNum(0);
    isPaused=false;
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
}

sideWidget::~sideWidget()
{
    delete ui;
}

void sideWidget::on_pause_clicked()
{
    if(isPaused==false)
    {
        PauseWindow* p = new PauseWindow(b->getBoard()->getwdg());
        p->setSS();
        if(b->getBS()+80>200)
        {
            p->setGeometry(0, 0,
                       b->getBS()+80, b->getBS()+80);
        }
        if(b->getBS()+80<=200)
        {
            p->setGeometry(0, 0, 200, 200);
            b->setMinimumSize(220,220);
            b->getBoard()->setMinimumSize(200,200);
            b->getFrame()->setMinimumSize(220, 220);
            b->getBoard()->getwdg()->setMinimumSize(200,200);
            b->getBoard()->resize(200, 200);
            b->getFrame()->resize(220, 220);
            b->getBoard()->getwdg()->resize(200,200);
        }
        p->setSide(this);
        isPaused=true;
        p->show();
    }
    if(b->isVisible()==false)
    {
        b->show();
    }
}

void sideWidget::closeEvent (QCloseEvent *event)
{
    b->close();
}

void sideWidget::themeChange(){
    b->ThemeChange();
    switch(b->getTheme())
    {
    case 0: setStyleSheet("sideWidget{background-color: rgb(136,136,136);}"
                          "QLabel{color: rgb(255,255,255);}");
            break;
    case 1: setStyleSheet("sideWidget{background-color: rgb(170, 255, 255);}"
                          "QLabel{color: rgb(94, 0, 141);}");
            break;
    }
}
