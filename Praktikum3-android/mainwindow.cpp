#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

}

void MainWindow::on_pushButton_toggled(bool checked)
{
    if (checked) {
        std::cout << "button checked" << std::endl;
        ui->centralWidget->setStyleSheet("background-color:white");
        ui->pushButton->setStyleSheet("color:white; \
         background-color:black");

    } else {
        std::cout << "button clicked" << std::endl;
        ui->centralWidget->setStyleSheet("background-color:black;");
        ui->pushButton->setStyleSheet("color:black; \
        background-color:white");
    }
}
