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
    add_random_images();
    gameStarted = true;
    change_card_availability(true);

    is_matched_cards(1,1); // just to print out styleSheet of cardCheckBox_1
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
    oldCardArr = cardArr;

    //update card Arr
    if (ui->cardCheckBox_1->checkState()){
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
        indexBitCardArr = oldCardArr ^= cardArr;
        indexOpenCard = find_bit_index(indexBitCardArr);

        qDebug("numberOfMove %d", numberOfMove);
        qDebug("indexBitCardArr %d", indexBitCardArr);
        qDebug("indexOpenCard %d", indexOpenCard);
        if(numberOfMove%2 == 0)
        {
            ui->moveNumber->display(numberOfMove/2);
            indexCard2 = indexOpenCard;
            // to do: add a sleep function, maybe create a new one, or (learn to) use QThread
            uncheck_cards(indexCard1,indexCard2);
            qDebug("---uncheck_cards: DONE!---");
        }
        else
        {
            indexCard1 = indexOpenCard;
        }

        qDebug("Card 1: %d", indexCard1);
        qDebug("Card 2: %d", indexCard2);
        qDebug("---Finish a move---");
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
        qDebug("---Finish a move---");
    }
};

void MainWindow::change_card_availability(bool state)
{
    ui->cardCheckBox_1->setCheckable(state);
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

    qDebug() << "styleSheet of cardCheckBox_1: " << ui->cardCheckBox_1->styleSheet(); // this is what we will compare to check whether 2 cards is matched or not
};

void MainWindow::diable_cards(uint card)
{
    //todo: disable card
};

void MainWindow::uncheck_cards(uint card1, uint card2)
{
    // todo: find a better way to convert string to qobject (qcheckbox)
    if (card1 == 1 || card2 == 1)
    {
        ui->cardCheckBox_1->setChecked(false);
    }

    if (card1 == 2 || card2 == 2)
    {
        ui->cardCheckBox_2->setChecked(false);
    }

    if (card1 == 3 || card2 == 3)
    {
        ui->cardCheckBox_3->setChecked(false);
    }

    if (card1 == 4 || card2 == 4)
    {
        ui->cardCheckBox_4->setChecked(false);
    }

    if (card1 == 5 || card2 == 5)
    {
        ui->cardCheckBox_5->setChecked(false);
    }

    if (card1 == 6 || card2 == 6)
    {
        ui->cardCheckBox_6->setChecked(false);
    }

    if (card1 == 7 || card2 == 7)
    {
        ui->cardCheckBox_7->setChecked(false);
    }

    if (card1 == 8 || card2 == 8)
    {
        ui->cardCheckBox_8->setChecked(false);
    }

    if (card1 == 9 || card2 == 9)
    {
        ui->cardCheckBox_9->setChecked(false);
    }

    if (card1 == 10 || card2 == 10)
    {
        ui->cardCheckBox_10->setChecked(false);
    }

    if (card1 == 11 || card2 == 11)
    {
        ui->cardCheckBox_11->setChecked(false);
    }

    if (card1 == 12 || card2 == 12)
    {
        ui->cardCheckBox_12->setChecked(false);
    }

    if (card1 == 13 || card2 == 13)
    {
        ui->cardCheckBox_13->setChecked(false);
    }

    if (card1 == 14 || card2 == 14)
    {
        ui->cardCheckBox_14->setChecked(false);
    }

    if (card1 == 15 || card2 == 15)
    {
        ui->cardCheckBox_15->setChecked(false);
    }

    if (card1 == 16 || card2 == 16)
    {
        ui->cardCheckBox_16->setChecked(false);
    }

};

uint MainWindow::find_bit_index(uint card)
{
    uint index = log(card)/log(2) + 1; // logarit with base 2 can be calculated from natural logarit of 2
    return index;
}

void MainWindow::add_random_images()
{
    // todo: randomly add 8 images to 16 checkboxes
    // the idea should be: 1, Create an Qstring array of 16 items, goes from card_1.jpg, card_1.jpg, card_2.jpg, card_2.jpg,... to card_8.jpg
    //                     2, Shuffle the array
    //                     3, Add each array item to the styleSheet

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    QString defaultStyleSheet = "QCheckBox {spacing: 5px;}"
                                "QCheckBox::indicator {width: 150px; height: 150px;}"
                                "QCheckBox::indicator:unchecked {image: url(:cardBack.jpg);}";

    // step 1

    for (int i = 0; i < 8; i++)
    {
        appendStyleSheet[2*i]   = "QCheckBox::indicator:checked {image: url(:card_" + QString::number(i+1) + ".jpg);}";
        appendStyleSheet[2*i+1] = "QCheckBox::indicator:checked {image: url(:card_" + QString::number(i+1) + ".jpg);}";
    }

    qDebug("---styleSheet before shuffle---");
    for (int i = 0; i < 16; i++)
    {
       qDebug() << "index: " << i << appendStyleSheet[i];
    }

    // Step 2

    shuffle(appendStyleSheet.begin(), appendStyleSheet.end(), std::default_random_engine(seed));

    qDebug("---styleSheet after shuffle---");
    for (int i = 0; i < 16; i++)
    {
       qDebug() << "index: " << i << appendStyleSheet[i];
    }

    // Step 3 (need to find a quicker way to do this)

    ui->cardCheckBox_1->setStyleSheet(defaultStyleSheet + appendStyleSheet[0]);
    ui->cardCheckBox_2->setStyleSheet(defaultStyleSheet + appendStyleSheet[1]);
    ui->cardCheckBox_3->setStyleSheet(defaultStyleSheet + appendStyleSheet[2]);
    ui->cardCheckBox_4->setStyleSheet(defaultStyleSheet + appendStyleSheet[3]);

    ui->cardCheckBox_5->setStyleSheet(defaultStyleSheet + appendStyleSheet[4]);
    ui->cardCheckBox_6->setStyleSheet(defaultStyleSheet + appendStyleSheet[5]);
    ui->cardCheckBox_7->setStyleSheet(defaultStyleSheet + appendStyleSheet[6]);
    ui->cardCheckBox_8->setStyleSheet(defaultStyleSheet + appendStyleSheet[7]);

    ui->cardCheckBox_9->setStyleSheet(defaultStyleSheet + appendStyleSheet[8]);
    ui->cardCheckBox_10->setStyleSheet(defaultStyleSheet + appendStyleSheet[9]);
    ui->cardCheckBox_11->setStyleSheet(defaultStyleSheet + appendStyleSheet[10]);
    ui->cardCheckBox_12->setStyleSheet(defaultStyleSheet + appendStyleSheet[11]);

    ui->cardCheckBox_13->setStyleSheet(defaultStyleSheet + appendStyleSheet[12]);
    ui->cardCheckBox_14->setStyleSheet(defaultStyleSheet + appendStyleSheet[13]);
    ui->cardCheckBox_15->setStyleSheet(defaultStyleSheet + appendStyleSheet[14]);
    ui->cardCheckBox_16->setStyleSheet(defaultStyleSheet + appendStyleSheet[15]);
}

