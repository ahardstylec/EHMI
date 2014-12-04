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
    connect(&canParser, SIGNAL(Speed(qreal)), ui->lcdKmh, SLOT(display(qreal)));
}

MainWindow::~MainWindow()
{
    delete ui;
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
