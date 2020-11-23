#include "optionwindow.h"
#include "startwindow.h"
#include "ui_startwindow.h"

#include <QLineEdit>

StartWindow::StartWindow(QWidget *parent, bool fs) :
    QMainWindow(parent),
    ui(new Ui::StartWindow)
{
    ui->setupUi(this);
    p.load(":/Images/Title.png");
    theme=0;
    boardsize=640;
    soundlevel=100;
    musiclevel=100;
    fullscreen=fs;
    setTilesize();
    mutemusic=false;
    mutesound=false;
    player1name="Player 1";
    player2name="Player 2";
    centralWidget()->layout()->setAlignment(Qt::AlignCenter);
    ui->label->setPixmap(p.scaled(1100, 1100, Qt::KeepAspectRatio));
    ui->Buttonwidget->layout()->setAlignment(Qt::AlignHCenter);
}

StartWindow::~StartWindow()
{
    delete ui;
}

void StartWindow::PvAI()
{
    this->close();
    this->runBoard(1);

}

void StartWindow::PvP()
{
    this->close();
    this->runBoard(0);
}

void StartWindow::runBoard(int i)
{
    BoardWindow* b = new BoardWindow(nullptr, theme, tilesize, boardsize);
    sideWidget* s = new sideWidget(nullptr, player1name, player2name);
    s->setBoardWindow(b);
    b->move(340,150);
    s->move(900+(boardsize/4), 150);
    b->setAttribute(Qt::WA_QuitOnClose, false);
    transferPreferences(b);
    s->themeChange();
    b->getBoard()->setSWUI(s->getUI());
    Player* p1 = new Player(player1name, "white", b->getBoard());
    Player* p2 = new Player(player2name, "black", b->getBoard());
    b->getBoard()->addPlayer(p1);
    b->getBoard()->addPlayer(p2);
    b->getBoard()->setCurrentPlayer(p1);
    if(i==0) //PvP
    {
        p1->setType('p');
        p2->setType('p');
    }
    else if(i==1) //PvAI
    {
        p1->setType('p');
        p2->setType('a');
        AI * agent = new AI(p2);
        p2->setAgent(agent);
    }
    else if(i==2) //AIvAI
    {
        p1->setType('a');
        p2->setType('a');
        AI *agent = new AI(p1);
        p1->setAgent(agent);
        agent = new AI(p2);
        p2->setAgent(agent);

    }
    if(fullscreen==true)
    {
        b->showFullScreen();
    }
    else if(fullscreen==false)
    {
        b->showNormal();
        b->layout()->setSpacing(0);
        b->layout()->setMargin(0);
        b->layout()->setContentsMargins(0,0,0,0);
    }
    s->show();
}


void StartWindow::on_Exit_clicked()
{
    this->close();
}

void StartWindow::on_Options_clicked()
{
    if(optionsOpened==false)
    {
        OptionWindow * o = new OptionWindow(nullptr, this, nullptr);
        o->setAttribute(Qt::WA_QuitOnClose, false);
        optionsOpened=true;
        o->show();
    }
}

void StartWindow::on_Confirm_clicked(string p1, string p2)
{
    player1name=p1;
    player2name=p2;
}

void StartWindow::on_PlayerSetup_clicked()
{
    QWidget * playerenter = new QWidget;
    QLayout * l = new QHBoxLayout;
    playerenter->setLayout(l);
    playerenter->setStyleSheet("QWidget{background-color:rgba(0,0,0,0);}"
                               "QLabel{color:rgb(255,255,255);"
                               "font: 75 8pt 'Terminal';}"
                               "QPushButton{color:rgb(0, 0, 0);"
                               "background-color:rgba(200, 200, 200);"
                               "text-align: left;"
                               "font: 75 8pt 'Terminal';}"
                               "QPushButton:hover {background-color:rgba(255, 204, 19, 128);}"
                               "QLineEdit{color:rgb(255,255,255);}");
    QPushButton* confirm = new QPushButton(" Confirm", ui->Buttonwidget);
    QLineEdit* p1box = new QLineEdit("  ", ui->Buttonwidget);
    QLineEdit* p2box = new QLineEdit("  ", ui->Buttonwidget);
    QLabel* p1label = new QLabel("Player 1:", ui->Buttonwidget);
    QLabel* p2label = new QLabel("Player 2:", ui->Buttonwidget);
    ui->PlayerSetup->setText("");
    l->addWidget(confirm);
    connect(confirm, &QPushButton::clicked, this, [=]{on_Confirm_clicked(p1box->text().toStdString(), p2box->text().toStdString());});
    l->addWidget(p2box);
    l->addWidget(p2label);
    l->addWidget(p1box);
    l->addWidget(p1label);
    ui->Buttonwidget->layout()->replaceWidget(ui->PlayerSetup, playerenter);
}

void StartWindow::transferPreferences(BoardWindow * b)
{
    b->setBS(boardsize);
    b->setTS();
    b->setFS(fullscreen);
    b->setTheme(theme);
    b->setML(musiclevel);
    b->setSL(soundlevel);
    b->setMM(mutemusic);
    b->setMS(mutesound);
}

void StartWindow::LabelSize()
{
    if(fullscreen==true)
    {
        ui->label->setPixmap(p.scaled(1100/(theme+1), 1100/(theme+1), Qt::KeepAspectRatio));
    }
    if(fullscreen==false)
    {
         ui->label->setPixmap(p.scaled(500/(theme+1), 500/(theme+1), Qt::KeepAspectRatio));
    }
}

void StartWindow::themeChange()
{
    switch(theme)
    {
    case 0: p.load(":/Images/Title.png");
            this->setStyleSheet("StartWindow {border-image: url(:/Images/startBackground.png);}");
            ui->PvP->setStyleSheet("QPushButton {color:rgb(255, 255, 255);"
                                   "font: 75 14pt 'Terminal';"
                                   "background-color:rgba(255, 255, 255, 0);"
                                   "text-align: left;}"
                                   "QPushButton:hover {background-color:rgba(255, 204, 19, 128);}");
            ui->PvAI->setStyleSheet("QPushButton {color:rgb(255, 255, 255);"
                                   "font: 75 14pt 'Terminal';"
                                   "background-color:rgba(255, 255, 255, 0);"
                                   "text-align: left;}"
                                   "QPushButton:hover {background-color:rgba(255, 204, 19, 128);}");
            ui->PlayerSetup->setStyleSheet("QPushButton {color:rgb(255, 255, 255);"
                                   "font: 75 14pt 'Terminal';"
                                   "background-color:rgba(255, 255, 255, 0);"
                                   "text-align: left;}"
                                   "QPushButton:hover {background-color:rgba(255, 204, 19, 128);}");
            ui->Options->setStyleSheet("QPushButton {color:rgb(255, 255, 255);"
                                   "font: 75 14pt 'Terminal';"
                                   "background-color:rgba(255, 255, 255, 0);"
                                   "text-align: left;}"
                                   "QPushButton:hover {background-color:rgba(255, 204, 19, 128);}");
            ui->Exit->setStyleSheet("QPushButton {color:rgb(255, 255, 255);"
                                   "font: 75 14pt 'Terminal';"
                                   "background-color:rgba(255, 255, 255, 0);"
                                   "text-align: left;}"
                                   "QPushButton:hover {background-color:rgba(255, 204, 19, 128);}");
            setCursor(Qt::ArrowCursor);
            break;

    case 1: p.load(":/Images/CheckersTitle2.png");
            this->setStyleSheet("StartWindow {border-image: url(:/Images/startwindow2.png);}");
        ui->PvP->setStyleSheet("QPushButton{color:rgb(255, 204, 19);"
                               "font: 75 14pt 'Terminal';"
                               "background-color:rgba(255, 255, 255, 0);"
                               "text-align: left;}"
                               "QPushButton:hover{background-color:rgba(239, 79, 239, 128);}");
        ui->PvAI->setStyleSheet("QPushButton{color:rgb(255, 204, 19);"
                                "font: 75 14pt 'Terminal';"
                                "background-color:rgba(255, 255, 255, 0);"
                                "text-align: left;}"
                                "QPushButton:hover{background-color:rgba(239, 79, 239, 128);}");
        ui->PlayerSetup->setStyleSheet("QPushButton{color:rgb(255, 204, 19);"
                                       "font: 75 14pt 'Terminal';"
                                       "background-color:rgba(255, 255, 255, 0);"
                                       "text-align: left;}"
                                       "QPushButton:hover{background-color:rgba(239, 79, 239, 128);}");
        ui->Options->setStyleSheet("QPushButton{color:rgb(255, 204, 19);"
                                   "font: 75 14pt 'Terminal';"
                                   "background-color:rgba(255, 255, 255, 0);"
                                   "text-align: left;}"
                                   "QPushButton:hover{background-color:rgba(239, 79, 239, 128);}");
        ui->Exit->setStyleSheet("QPushButton{color:rgb(255, 204, 19);"
                                "font: 75 14pt 'Terminal';"
                                "background-color:rgba(255, 255, 255, 0);"
                                "text-align: left;}"
                                "QPushButton:hover{background-color:rgba(239, 79, 239, 128);}");
        setCursor(QCursor(QPixmap(":/Images/Cursor.png"),25,25));
            break;
    default:
            break;
    }
    LabelSize();
}

void StartWindow::on_AIvAI_clicked()
{
    this->close();
    this->runBoard(2);
}
