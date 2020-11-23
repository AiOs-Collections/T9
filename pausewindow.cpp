#include "pausewindow.h"
#include "ui_pausewindow.h"
#include "startwindow.h"
#include "optionwindow.h"

PauseWindow::PauseWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PauseWindow)
{
    ui->setupUi(this);
    optionsOpened=false;
    ui->label->setPixmap(QPixmap(":/Images/pause.png"));
    this->setAttribute(Qt::WA_QuitOnClose, false);
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    this->setStyleSheet("PauseWindow {background: url(:/Images/pauseBackground.png);"
                        "border: 5px solid black; "
                        "border-radius: 30px;}");
}

PauseWindow::~PauseWindow()
{
    delete ui;
}

void PauseWindow::RequestDraw()
{
    std::cout << "Request Draw" << std::endl;
}

void PauseWindow::Options()
{
    if(optionsOpened==false)
    {
        OptionWindow * o = new OptionWindow(nullptr, nullptr, this);
        o->setAttribute(Qt::WA_QuitOnClose, false);
        optionsOpened=true;
        o->show();
    }
}

void PauseWindow::ExitGame()
{
    s->close();
    this->close();
    if(s->getIsPaused()==true)
    {
        s->togglePause();
    }
}

void PauseWindow::Resume()
{
    this->close();
    if(s->getIsPaused()==true)
    {
        s->togglePause();
    }
    s->getBoardWindow()->setMinimumSize(s->getBoardWindow()->getBS()+100, s->getBoardWindow()->getBS()+100);
    s->getBoardWindow()->getBoard()->setMinimumSize(80+s->getBoardWindow()->getBS(), 80+s->getBoardWindow()->getBS());
    s->getBoardWindow()->getFrame()->setMinimumSize(s->getBoardWindow()->getBS()+100, s->getBoardWindow()->getBS()+100);
    s->getBoardWindow()->getBoard()->resize(80+s->getBoardWindow()->getBS(), 80+s->getBoardWindow()->getBS());
    s->getBoardWindow()->getFrame()->resize(100+s->getBoardWindow()->getBS(), 100+s->getBoardWindow()->getBS());
}



void PauseWindow::on_ReturnTitle_clicked()
{
    std::cout << "Return to start window" << std::endl;
    s->getBoardWindow()->close();
    s->close();
    this->close();
    if(s->getIsPaused()==true)
    {
        s->togglePause();
    }
    StartWindow* w = new StartWindow(nullptr, s->getBoardWindow()->getFS());
    w->setTheme(s->getBoardWindow()->getTheme());
    w->setBS(s->getBoardWindow()->getBS());
    w->setTilesize();
    w->themeChange();
    if(s->getBoardWindow()->getFS()==true)
    {
        w->showFullScreen();
        w->LabelSize();
    }
    if(s->getBoardWindow()->getFS()==false)
    {
        w->show();
        w->LabelSize();
    }
    BoardWindow * b = s->getBoardWindow();
    s->getBoardWindow()->layout()->removeWidget(s->getBoardWindow());
    s->layout()->removeWidget(s);
    delete s;
    b=nullptr;
    delete b;
}

void PauseWindow::on_NewGame_clicked()
{
    BoardWindow* b2 = new BoardWindow(nullptr, s->getBoardWindow()->getTheme(),
                                      s->getBoardWindow()->getTS(), s->getBoardWindow()->getBS());
    sideWidget* s2 = new sideWidget(nullptr, s->getBoardWindow()->getBoard()->getPlayers().at(0)->getName(),
                                    s->getBoardWindow()->getBoard()->getPlayers().at(1)->getName())
            ;
    s2->setBoardWindow(b2);
    b2->move(340,150);
    s2->move(900+(s->getBoardWindow()->getBS()/4),150);
    b2->setAttribute(Qt::WA_QuitOnClose, false);
    this->close();
    BoardWindow * b = s->getBoardWindow();
    s->getBoardWindow()->close();
    s->close();
    b2->setFS(b->getFS());
    b2->getBoard()->setSWUI(s2->getUI());
    Player* pt1 = b->getBoard()->getPlayers().at(0);
    Player* pt2 = b->getBoard()->getPlayers().at(1);
    Player* p1 = new Player(pt1->getName(), "white", b2->getBoard());
    Player* p2 = new Player(pt2->getName(), "black", b2->getBoard());
    b2->getBoard()->addPlayer(p1);
    b2->getBoard()->addPlayer(p2);
    b2->getBoard()->setCurrentPlayer(p1);
    p1->setType(pt1->getType());
    p2->setType(pt2->getType());
    p1->setAgent(pt1->getAgent());
    p2->setAgent(pt2->getAgent());
    if(b2->getFS()==true)
    {
        b2->showFullScreen();
    }
    if(b2->getFS()==false)
    {
        b2->showNormal();
    }
    s2->show();
    s->getBoardWindow()->layout()->removeWidget(s->getBoardWindow());
    s2->themeChange();
    s->layout()->removeWidget(s);
    delete s;
    b=nullptr;
    delete b;
}

void PauseWindow::closeEvent (QCloseEvent *event)
{
    if(s->getIsPaused()==true)
    {
        s->togglePause();
    }
}

void PauseWindow::setSS()
{
    ui->label->setPixmap(QPixmap(":/Images/pause.png"));
    ui->label->setStyleSheet("background-color: rgba(0,0,0,0);");
    this->setAttribute(Qt::WA_QuitOnClose, false);
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    this->setStyleSheet("PauseWindow {background: url(:/Images/pauseBackground.png);"
                        "border: 5px solid black; "
                        "border-radius: 30px;}"
                        "QPushButton{background-color: rgb(200,200,200);}");
}
