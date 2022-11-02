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
    uint oldCardArr = cardArr;

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
    // note: click 2 cards too fast can lead to misdisplaying the numberOfMove. Need to be checked later

    if (oldCardArr < cardArr) // Open 2 cards means cardArr always > oldCardArr, which is a move and we can unchecked all the cards
    {
        qDebug("---Open a card which hasn't been opend---");
        qDebug("oldCardArr %d", oldCardArr);
        qDebug("cardArr %d", cardArr);
        numberOfMove++;
        qDebug("numberOfMove %d", numberOfMove);
        ui->moveNumber->display(numberOfMove/2);
        if(numberOfMove%2 == 0)
        {
            // to do: add a sleep function, maybe create a new one, or (learn to) use QThread
            uncheck_cards(1,1); // (1,1) is just random value to call the uncheck_cards() function
            qDebug("---uncheck_cards: DONE!---");
        }
    }
    else if (oldCardArr > cardArr && numberOfMove%2 == 1) // Close the opened card means cardArr < oldCardArr only when numberOfMove is odd number, which is a move and we can unchecked all the cards
    {
        qDebug("---Close a card which has been already opened---");
        qDebug("oldCardArr ->- %d", oldCardArr);
        qDebug("cardArr %d", cardArr);
        numberOfMove++;
        qDebug("numberOfMove %d", numberOfMove);
        ui->moveNumber->display(numberOfMove/2);
        if(numberOfMove%2 == 0)
        {
            // to do: add a sleep function, maybe create a new one, or (learn to) use QThread
            uncheck_cards(1,1); // (1,1) is just random value to call the uncheck_cards() function
            qDebug("---uncheck_cards: DONE!---");
        }
    }
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
    ui->cardCheckBox->setChecked(false); // temporary uncheck all the cards
    ui->cardCheckBox_2->setChecked(false);
    ui->cardCheckBox_3->setChecked(false);
    ui->cardCheckBox_4->setChecked(false);
    ui->cardCheckBox_5->setChecked(false);
    ui->cardCheckBox_6->setChecked(false);
    ui->cardCheckBox_7->setChecked(false);
    ui->cardCheckBox_8->setChecked(false);
    ui->cardCheckBox_9->setChecked(false);
    ui->cardCheckBox_10->setChecked(false);
    ui->cardCheckBox_11->setChecked(false);
    ui->cardCheckBox_12->setChecked(false);
    ui->cardCheckBox_13->setChecked(false);
    ui->cardCheckBox_14->setChecked(false);
    ui->cardCheckBox_15->setChecked(false);
    ui->cardCheckBox_16->setChecked(false);
};

uint MainWindow::find_bit_index(uint card)
{
    // todo: find bit index to be used as input for uncheck_cards()
    // return index;
}
