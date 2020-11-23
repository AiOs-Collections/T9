#include "optionwindow.h"
#include "ui_optionwindow.h"

OptionWindow::OptionWindow(QWidget *parent, StartWindow * sw, PauseWindow * pw) :
    QMainWindow(parent),
    ui(new Ui::OptionWindow)
{
    ui->setupUi(this);
    p = pw;
    w = sw;
    tabtarget=0;
    this->setAttribute(Qt::WA_QuitOnClose, false);
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    ui->Option1Label->setText("Board Size:  \t");
    ui->Option1Slider->setMinimum(0);
    ui->Option1Slider->setMaximum(80);
    ui->Option1Slider->setSingleStep(1);
    ui->Option1Slider->setPageStep(8);
    ui->Option2Label->setText("Minimum Window Size will be dependent on Board Size.");
    ui->Option2Slider->setHidden(true);
    ui->Option2Num->setHidden(true);
    ui->Option3Label->setText("Fullscreen:  \t");
    ui->Option3Check->setChecked(true);
    ui->Option4Label->setHidden(true);
    ui->Option4Check->setHidden(true);
    ui->ThemeBox->setHidden(false);
    ui->ThemeLabel->setHidden(false);
    if(pw!=nullptr)
    {
        BoardWindow * b = p->getSide()->getBoardWindow();
        ui->Option1Num->setNum(80+b->getBS());
        ui->Option1Slider->setSliderPosition(b->getBS()/8);
        ui->Option3Check->setChecked(b->getFS());
        ui->ThemeBox->setCurrentIndex(b->getTheme());
    }
    if(sw!=nullptr)
    {
        ui->Option1Num->setNum(80+w->getBS());
        ui->Option1Slider->setSliderPosition(w->getBS()/8);
        ui->Option3Check->setChecked(w->getFS());
        ui->ThemeBox->setCurrentIndex(w->getTheme());
    }
}

OptionWindow::~OptionWindow()
{
    delete ui;
}

void OptionWindow::on_Display_clicked()
{
    tabtarget=0;
    ui->Option1Label->setText("Board Size:  \t");
    ui->Option1Slider->setMinimum(0);
    ui->Option1Slider->setMaximum(80);
    ui->Option1Slider->setSingleStep(1);
    ui->Option1Slider->setPageStep(8);
    ui->Option2Label->setText("Minimum Window Size will be dependent on Board Size.");
    ui->Option2Slider->setHidden(true);
    ui->Option2Num->setHidden(true);
    ui->Option3Label->setText("Fullscreen:  \t");
    ui->Option4Label->setHidden(true);
    ui->Option4Check->setHidden(true);
    ui->ThemeBox->setHidden(false);
    ui->ThemeLabel->setHidden(false);
    if(p!=nullptr)
    {
        BoardWindow* b = p->getSide()->getBoardWindow();
        ui->Option1Num->setNum(80+b->getBS());
        ui->Option1Slider->setSliderPosition(b->getBS()/8);
        ui->Option3Check->setChecked(b->getFS());
        ui->ThemeBox->setCurrentIndex(b->getTheme());
    }
    if(w!=nullptr)
    {
        ui->Option1Num->setNum(80+w->getBS());
        ui->Option1Slider->setSliderPosition(w->getBS()/8);
        ui->Option3Check->setChecked(w->getFS());
        ui->ThemeBox->setCurrentIndex(w->getTheme());
    }
}

void OptionWindow::on_Audio_clicked()
{
    tabtarget=1;
    ui->Option1Label->setText("Sound:   \t");
    ui->Option2Label->setText("Music:   \t");
    ui->Option1Slider->setMinimum(1);
    ui->Option1Slider->setMaximum(100);
    ui->Option1Slider->setSingleStep(1);
    ui->Option1Slider->setPageStep(10);
    ui->Option2Slider->setHidden(false);
    ui->Option2Num->setHidden(false);
    ui->Option3Label->setText("Mute Sound:  \t");
    ui->Option4Label->setText("Mute Music:  \t");
    ui->Option4Label->setHidden(false);
    ui->Option4Check->setHidden(false);
    ui->ThemeBox->setHidden(true);
    ui->ThemeLabel->setHidden(true);
    if(w!=nullptr)
    {
        ui->Option1Num->setNum(w->getSL());
        ui->Option1Slider->setSliderPosition(w->getSL());
        ui->Option2Num->setNum(w->getML());
        ui->Option2Slider->setSliderPosition(w->getML());
        ui->Option3Check->setChecked(w->getMS());
        ui->Option4Check->setChecked(w->getMM());
    }
    if(p!=nullptr)
    {
        BoardWindow * b = p->getSide()->getBoardWindow();
        ui->Option1Num->setNum(b->getSL());
        ui->Option1Slider->setSliderPosition(b->getSL());
        ui->Option2Num->setNum(b->getML());
        ui->Option2Slider->setSliderPosition(b->getML());
        ui->Option3Check->setChecked(b->getMS());
        ui->Option4Check->setChecked(b->getMM());
    }
}

void OptionWindow::on_Apply_clicked()
{
    if(w!=nullptr)
    {
        switch(tabtarget)
        {
            case 0: if(option1!=w->getBS()) //Display
                    {
                        w->setBS(option1);
                        w->setTilesize();
                    }
                    if(option3!=w->getFS())
                    {
                        if(option3==0)
                        {
                            w->close();
                            w->setFS(false);
                            w->LabelSize();
                            w->showNormal();
                        }
                        if(option3==1)
                        {
                            w->close();
                            w->setFS(true);
                            w->LabelSize();
                            w->showFullScreen();
                        }
                    }
                    if(ui->ThemeBox->currentIndex() != w->getTheme())
                    {
                        w->setTheme(ui->ThemeBox->currentIndex());
                        w->themeChange();
                    }
                    break;
            case 1: if(option1!=w->getSL()) //Audio
                    {
                        w->setSL(option1);
                    }
                    if(option2!=w->getML())
                    {
                        w->setML(option2);
                    }
                    if(option3!=w->getMS())
                    {
                        if(option3==0)
                        {
                            w->setMS(false);
                        }
                        if(option3==1)
                        {
                            w->setMS(true);
                        }
                    }
                    if(option4!=w->getMM())
                    {
                        if(option4==0)
                        {
                            w->setMM(false);
                        }
                        if(option4==1)
                        {
                            w->setMM(true);
                        }
                    }
                    break;
            default:
                    break;
        }
    }
    if(p!=nullptr)
    {
        BoardWindow* b = p->getSide()->getBoardWindow();
        switch(tabtarget)
        {
            case 0: if(option1!=b->getBS()) //Display
                    {
                        b->setBS(option1);
                        b->setTS();
                        b->getBoard()->setBS(b->getBS());
                        b->getBoard()->setTS(b->getTS());
                        b->resize();
                        b->layout()->setSpacing(0);
                        b->layout()->setMargin(0);
                        b->layout()->setContentsMargins(0,0,0,0);
                        if(b->getBS()+80>200)
                        {
                            p->setGeometry(0, 0,
                                       b->getBS()+80, b->getBS()+80);
                        }
                        else if(b->getBS()+80<=200)
                        {
                            p->setGeometry(0,0,200,200);
                        }
                    }
                    if(option3!=b->getFS())
                    {
                        if(option3==0)
                        {
                            b->close();
                            b->setFS(false);
                            b->showNormal();
                            b->adjustSize();
                        }
                        if(option3==1)
                        {
                            b->close();
                            b->setFS(true);
                            b->showFullScreen();
                        }
                    }
                    if(ui->ThemeBox->currentIndex() != b->getTheme())
                    {
                        b->setTheme(ui->ThemeBox->currentIndex());
                        p->getSide()->themeChange();
                        p->setSS();
                    }
                    if(b->getFS()==false){
                        b->adjustSize();}
                    break;
            case 1: if(option1!=b->getSL()) //Audio
                    {
                        b->setSL(option1);
                    }
                    if(option2!=w->getML())
                    {
                        b->setML(option2);
                    }
                    if(option3!=b->getMS())
                    {
                        if(option3==0)
                        {
                            b->setMS(false);
                        }
                        if(option3==1)
                        {
                            b->setMS(true);
                        }
                    }
                    if(option4!=b->getMM())
                    {
                        if(option4==0)
                        {
                            b->setMM(false);
                        }
                        if(option4==1)
                        {
                            b->setMM(true);
                        }
                    }
                    break;
            default:
                    break;
        }
    }
}

void OptionWindow::on_Quit_clicked()
{
    if(w!=nullptr)
    {
        w->switchOO();
    }
    if(p!=nullptr)
    {
        p->switchOO();
    }
    this->close();
}

void OptionWindow::on_Option3Check_stateChanged(int arg1)
{
    option3=arg1;
}

void OptionWindow::on_Option4Check_stateChanged(int arg1)
{
    option4=arg1;
}

void OptionWindow::on_Option2Slider_valueChanged(int value)
{
    ui->Option2Num->setNum(value);
    option2=value;
}

void OptionWindow::on_Option1Slider_valueChanged(int value)
{
    if(tabtarget==0)
    {
        ui->Option1Num->setNum(80+(value*8));
        option1=value*8;
    }
    if(tabtarget==1)
    {
        ui->Option1Num->setNum(value);
        option1=value;
    }
}

void OptionWindow::closeEvent (QCloseEvent *event)
{
    if(w!=nullptr)
    {
        w->switchOO();
    }
    if(p!=nullptr)
    {
        p->switchOO();
    }
    this->close();
}
