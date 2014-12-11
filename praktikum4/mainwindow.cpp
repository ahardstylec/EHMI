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
    qint64 size;
    QFile myFile("data/CanTraceFile.txt");
    if (myFile.open(QIODevice::ReadOnly)){
        size = myFile.size();  //when file does open.
        myFile.close();
    }
    ui->playPosition->setMaximum(size/64);
    ui->playPosition->setMinimum(0);

    connect(canParser.m_Timer, SIGNAL(timeout()), this, SLOT(updateTimer));
    connect(&canParser, SIGNAL(Speed(qreal)), ui->lcdKmh, SLOT(display(qreal)));
    connect(&canParser, SIGNAL(RPM(qreal)), ui->lcdRpm, SLOT(display(qreal)));
    connect(&canParser, SIGNAL(Pedal(qreal)), ui->lcdGaspedal, SLOT(display(qreal)));
    connect(&canParser, SIGNAL(LenkradWinkel(int)), ui->lcdSteering, SLOT(display(int)));
    connect(&canParser, SIGNAL(Temperature(qreal)), ui->lcdTemperature, SLOT(display(qreal)));
    connect(&canParser, SIGNAL(Blinker(int)), this, SLOT(displayBlinker(int)));
    connect(ui->changePlaySpeed, SIGNAL(valueChanged(int)), &canParser, SLOT(SetTimeout(int)));
    connect(ui->playPosition, SIGNAL(sliderMoved(int)), this, SLOT(setTime(int)));
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
    time = time.addSecs(1);
    ui->lcdTimer->display(time.toString("hh:mm:ss"));
}

void MainWindow::setTime(int sec){
    time = time.addSecs(sec);
    ui->lcdTimer->display( time.toString("hh:mm:ss"));
    canParser.setTime(sec);
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
