#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWidget>

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
    change_card_availability(false);
}

void MainWindow::on_startBtn_clicked()
{
    ui->moveNumber->display((int)playerMove);
    gameStarted = true;
    change_card_availability(true);
}

void MainWindow::updateCountdown()
{
    if (gameStarted)
    {
        playTime = playTime.addSecs(-1);
        mapping_card_value();
    }
    QString timerText = playTime.toString("mm:ss");
    ui->timerDisplay->setText(timerText);
    ui->outputLabel->setText(QString::number(cardArr));
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

void MainWindow::mapping_card_value()
{
    int oldCardArr = cardArr;

    //update card Arr
    if (ui->cardCheckBox->checkState()){
        cardArr |= 1UL << 0;
    }
    else {
        cardArr &= ~(1UL << 0);
    }

    if (ui->cardCheckBox_2->checkState()){
        cardArr |= 1UL << 1;
    }
    else {
        cardArr &= ~(1UL << 1);
    }

    if (ui->cardCheckBox_3->checkState()){
        cardArr |= 1UL << 2;
    }
    else {
        cardArr &= ~(1UL << 2);
    }

    if (ui->cardCheckBox_4->checkState()){
        cardArr |= 1UL << 3;
    }
    else {
        cardArr &= ~(1UL << 3);
    }

    if (ui->cardCheckBox_5->checkState()){
        cardArr |= 1UL << 4;
    }
    else {
        cardArr &= ~(1UL << 4);
    }

    if (ui->cardCheckBox_6->checkState()){
        cardArr |= 1UL << 5;
    }
    else {
        cardArr &= ~(1UL << 5);
    }

    if (ui->cardCheckBox_7->checkState()){
        cardArr |= 1UL << 6;
    }
    else {
        cardArr &= ~(1UL << 6);
    }

    if (ui->cardCheckBox_8->checkState()){
        cardArr |= 1UL << 7;
    }
    else {
        cardArr &= ~(1UL << 7);
    }

    if (ui->cardCheckBox_9->checkState()){
        cardArr |= 1UL << 8;
    }
    else {
        cardArr &= ~(1UL << 8);
    }

    if (ui->cardCheckBox_10->checkState()){
        cardArr |= 1UL << 9;
    }
    else {
        cardArr &= ~(1UL << 9);
    }

    if (ui->cardCheckBox_11->checkState()){
        cardArr |= 1UL << 10;
    }
    else {
        cardArr &= ~(1UL << 10);
    }

    if (ui->cardCheckBox_12->checkState()){
        cardArr |= 1UL << 11;
    }
    else {
        cardArr &= ~(1UL << 11);
    }

    if (ui->cardCheckBox_13->checkState()){
        cardArr |= 1UL << 12;
    }
    else {
        cardArr &= ~(1UL << 12);
    }

    if (ui->cardCheckBox_14->checkState()){
        cardArr |= 1UL << 13;
    }
    else {
        cardArr &= ~(1UL << 13);
    }

    if (ui->cardCheckBox_15->checkState()){
        cardArr |= 1UL << 14;
    }
    else {
        cardArr &= ~(1UL << 14);
    }

    if (ui->cardCheckBox_16->checkState()){
        cardArr |= 1UL << 15;
    }
    else {
        cardArr &= ~(1UL << 15);
    }

    //handle move count
    oldCardArr ^= cardArr;
    for(; oldCardArr>0;)
    {
        if(oldCardArr%2)
        {
            numberOfMove++;             // need testing for the moveCount value
            numberOfOpenCard++;
        }
        oldCardArr = oldCardArr >> 1;
        if(numberOfOpenCard >= 2)
        {
            numberOfOpenCard = 0;
//            is_matched_cards(card1, card2); // to be added
        }
    }
    ui->moveNumber->display(numberOfMove/2); // temporary fix to display the correct value of moveCount
};

void MainWindow::change_card_availability(bool state)
{
    ui->cardCheckBox->setCheckable(state);
    ui->cardCheckBox_2->setCheckable(state);
    ui->cardCheckBox_3->setCheckable(state);
    ui->cardCheckBox_4->setCheckable(state);
    ui->cardCheckBox_5->setCheckable(state);
    ui->cardCheckBox_6->setCheckable(state);
    ui->cardCheckBox_7->setCheckable(state);
    ui->cardCheckBox_8->setCheckable(state);
    ui->cardCheckBox_9->setCheckable(state);
    ui->cardCheckBox_10->setCheckable(state);
    ui->cardCheckBox_11->setCheckable(state);
    ui->cardCheckBox_12->setCheckable(state);
    ui->cardCheckBox_13->setCheckable(state);
    ui->cardCheckBox_14->setCheckable(state);
    ui->cardCheckBox_15->setCheckable(state);
    ui->cardCheckBox_16->setCheckable(state);
};

bool MainWindow::is_matched_cards(uint card1, uint card2)
{
    //todo: compare card if match
};

void MainWindow::diable_cards(uint card)
{
    //todo: disable card
};

void MainWindow::uncheck_cards(uint card1, uint card2)
{
    //todo: uncheck the two cards that have just been opened by the player
};
