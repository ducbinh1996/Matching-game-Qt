#include "mainwindow.h"
#include "ui_mainwindow.h"

QTimer *timer = new QTimer();
QTime playTime(0,0,59);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);                                  // default widget is startUpPage
    ui->stackedWidget_2->setCurrentIndex(1);                                // default widget is inGame
    connect(timer, SIGNAL(timeout()), this, SLOT(updateCountdown()));
    timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_goToGameBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);                                  // move to page_2 (index 1) in stackedWidget
}

void MainWindow::on_startBtn_clicked()
{
    ui->moveNumber->display((int)playerMove);
    gameStarted = true;
}

void MainWindow::updateCountdown()
{
    if (gameStarted)
    {
        playTime = playTime.addSecs(-1);
    }
    QString timerText = playTime.toString("mm:ss");
    ui->timerDisplay->setText(timerText);
}

void MainWindow::on_pauseBtn_clicked()
{
    gameStarted = false;
    ui->stackedWidget_2->setCurrentIndex(0);
}


void MainWindow::on_resumeBtn_clicked()
{
    gameStarted = true;
    ui->stackedWidget_2->setCurrentIndex(1);
}

