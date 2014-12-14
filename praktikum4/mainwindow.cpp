#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "CanTraceParser.h"
#include <QLCDNumber>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    canParser(this)
{
    ui->setupUi(this);
    canParser.SetFile("data/CanTraceFile.txt");
    qint64 size = 0;
    QFile myFile("data/CanTraceFile.txt");
    if (myFile.open(QIODevice::ReadOnly)){
        size = myFile.size();  //when file does open.
        myFile.close();
    }
    ui->playPosition->setMaximum(size/64);
    ui->playPosition->setMinimum(0);
    time_elapsed=0;
    time.setHMS(0,0,0,0);

    connect(canParser.m_Timer, SIGNAL(timeout()), this, SLOT(updateTimer()));
    connect(&canParser, SIGNAL(Speed(qreal)), ui->lcdKmh, SLOT(display(qreal)));
    connect(&canParser, SIGNAL(RPM(qreal)), ui->lcdRpm, SLOT(display(qreal)));
    connect(&canParser, SIGNAL(Pedal(qreal)), ui->lcdGaspedal, SLOT(display(qreal)));
    connect(&canParser, SIGNAL(LenkradWinkel(int)), ui->lcdSteering, SLOT(display(int)));
    connect(&canParser, SIGNAL(Temperature(qreal)), ui->lcdTemperature, SLOT(display(qreal)));
    connect(&canParser, SIGNAL(Blinker(int)), this, SLOT(displayBlinker(int)));
    connect(ui->changePlaySpeed, SIGNAL(valueChanged(int)), &canParser, SLOT(SetTimeout(int)));
    connect(ui->playPosition, SIGNAL(sliderMoved(int)), this, SLOT(setTime(int)));

    connect(&canParser, SIGNAL(Temperature(qreal)), ui->graphicsView->getTemperatureBarPtr(), SLOT(update(qreal)));
    connect(&canParser, SIGNAL(Blinker(int)), ui->graphicsView->getBlinkerLeftPtr(), SLOT(update(int)));
    connect(&canParser, SIGNAL(Blinker(int)), ui->graphicsView->getBlinkerRightPtr(), SLOT(update(int)));
}

void MainWindow::displayBlinker(int blinker){
    ui->checkBoxBlinkerLinks->setChecked(blinker == 1);
    ui->checkBoxBlinkerRechts->setChecked(blinker == -1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateTimer(){
    time_elapsed += 20;


    int h = time_elapsed/3600000;
    int s = time_elapsed/1000 < 60 ? time_elapsed/1000 : time_elapsed/1000 %60;
    int m = time_elapsed/60000 < 60 ? time_elapsed/60000 : time_elapsed/60000 % 60;
    int ms = time_elapsed < 1000 ? time_elapsed : time_elapsed % 1000;
    time.setHMS(h,m,s, ms);

    qDebug() << time_elapsed << " " << time.toString("hh:mm:ss") << endl;
    ui->lcdTimer->display(time.toString("hh:mm:ss"));
    ui->playPosition->setValue(time_elapsed);
}

void MainWindow::setTime(int msec){
    time_elapsed = msec;
    int h = time_elapsed/3600000;
    int s = time_elapsed/1000 < 60 ? time_elapsed/1000 : time_elapsed/1000 %60;
    int m = time_elapsed/60000 < 60 ? time_elapsed/60000 : time_elapsed/60000 % 60;
    int ms = time_elapsed < 1000 ? time_elapsed : time_elapsed % 1000;
    time.setHMS(h,m,s, ms);

    qDebug() << time_elapsed << " " << time.toString("hh:mm:ss") << endl;
    ui->lcdTimer->display(time.toString("hh:mm:ss"));
    canParser.setTime(time_elapsed);
}

void MainWindow::on_pushButton_toggled(bool checked)
{
    if (checked) {
        ui->pushButton->setText("Stop");
        canParser.Start();

    } else {
        ui->pushButton->setText("Start");
        canParser.Stop();
    }
}
