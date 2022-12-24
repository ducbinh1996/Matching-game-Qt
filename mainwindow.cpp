#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWidget>

QTimer *timer = new QTimer();
QTime playTime(0,2,00);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);                                  // default widget is startUpPage
    ui->stackedWidget_2->setCurrentIndex(1);                                // default widget is inGame
    connect(timer, SIGNAL(timeout()), this, SLOT(updateCountdown()));
    connect(ui->stackedWidget_2, SIGNAL(mousePress(QMouseEvent *event)), this, SLOT(mouseClicked(QMouseEvent *event)));
    timer->start(1000);
    card->initialize(ui);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete card;
}

void MainWindow::on_goToGameBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);                                  // move to page_2 (index 1) in stackedWidget
    card->change_card_availability(false);
}

void MainWindow::on_startBtn_clicked()
{
    if(gameStarted==false)
    {
        ui->moveNumber->display(0);
        card->add_random_images();
        gameStarted = true;
        card->change_card_availability(true);
        ui->startBtn->setVisible(false);
    }
    card->set_started_status(true);
}

void MainWindow::updateCountdown()
{
    if (playTime == QTime(0,0,0))
    {
        player_win = false;
        game_ended_handler();
    }
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
    card->set_started_status(false);
}


void MainWindow::on_resumeBtn_clicked()
{
    gameStarted = true;
    ui->stackedWidget_2->setCurrentIndex(1);
    card->set_started_status(true);
}

void MainWindow::game_ended_handler()
{
    if(player_win)
    {
        msgBox.setIconPixmap(QPixmap(":win.jpg")); // to do: print the move count, the remain time,...
        msgBox.exec();
    }
    else
    {
        msgBox.setIconPixmap(QPixmap(":lose.jpg")); // to do: print the move count, the remain time,...
        msgBox.exec();
    }
    timer->stop();
}

void MainWindow::on_cardCheckBox_1_clicked(bool checked)
{
    if(card->card_handler(1, checked))
    {
        game_ended_handler();
    }
}

void MainWindow::on_cardCheckBox_2_clicked(bool checked)
{
    if(card->card_handler(2, checked))
    {
        game_ended_handler();
    }
}

void MainWindow::on_cardCheckBox_3_clicked(bool checked)
{
    if(card->card_handler(3, checked))
    {
        game_ended_handler();
    }
}

void MainWindow::on_cardCheckBox_4_clicked(bool checked)
{
    if(card->card_handler(4, checked))
    {
        game_ended_handler();
    }
}

void MainWindow::on_cardCheckBox_5_clicked(bool checked)
{
    if(card->card_handler(5, checked))
    {
        game_ended_handler();
    }
}

void MainWindow::on_cardCheckBox_6_clicked(bool checked)
{
    if(card->card_handler(6, checked))
    {
        game_ended_handler();
    }
}

void MainWindow::on_cardCheckBox_7_clicked(bool checked)
{
    if(card->card_handler(7, checked))
    {
        game_ended_handler();
    }
}

void MainWindow::on_cardCheckBox_8_clicked(bool checked)
{
    if(card->card_handler(8, checked))
    {
        game_ended_handler();
    }
}

void MainWindow::on_cardCheckBox_9_clicked(bool checked)
{
    if(card->card_handler(9, checked))
    {
        game_ended_handler();
    }
}

void MainWindow::on_cardCheckBox_10_clicked(bool checked)
{
    if(card->card_handler(10, checked))
    {
        game_ended_handler();
    }
}

void MainWindow::on_cardCheckBox_11_clicked(bool checked)
{
    if(card->card_handler(11, checked))
    {
        game_ended_handler();
    }
}

void MainWindow::on_cardCheckBox_12_clicked(bool checked)
{
    if(card->card_handler(12, checked))
    {
        game_ended_handler();
    }
}

void MainWindow::on_cardCheckBox_13_clicked(bool checked)
{
    if(card->card_handler(13, checked))
    {
        game_ended_handler();
    }
}

void MainWindow::on_cardCheckBox_14_clicked(bool checked)
{
    if(card->card_handler(14, checked))
    {
        game_ended_handler();
    }
}

void MainWindow::on_cardCheckBox_15_clicked(bool checked)
{
    if(card->card_handler(15, checked))
    {
        game_ended_handler();
    }
}

void MainWindow::on_cardCheckBox_16_clicked(bool checked)
{
    if(card->card_handler(16, checked))
    {
        game_ended_handler();
    }
}
