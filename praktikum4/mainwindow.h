#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "CanTraceParser.h"
#include <QTime>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QTime time;
    ~MainWindow();

private slots:
    void on_pushButton_toggled(bool checked);
    void displayBlinker(int);
    void updateTimer();
    void setTime(int);

private:
    Ui::MainWindow *ui;
    CanTraceParser canParser;
};

#endif // MAINWINDOW_H
