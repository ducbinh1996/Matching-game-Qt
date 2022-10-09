#include "mainwindow.h"
#include "ui_mainwindow.h"

QTimer *timer = new QTimer();
QTime playTime(0,20,0);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_goToGameBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(1); // move to page_2 (index 1) in stackedWidget
}

void MainWindow::on_startBtn_clicked()
{
    playerScore++;
    ui->scoreNumber->display((int)playerScore);
    if (!gameStarted)
    {
        connect(timer, SIGNAL(timeout()), this, SLOT(updateCountdown()));
        timer->start(1000);
        gameStarted = true;
    }
}

void MainWindow::updateCountdown()
{
    QString timerText = playTime.toString("mm:ss");
    ui->timerDisplay->setText(timerText);
    playTime = playTime.addSecs(-1);
}
