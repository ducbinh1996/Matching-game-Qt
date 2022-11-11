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

    for (uint i = 0; i < 16; i++)
    {
       get_checkbox_ID(i+1);
       if (checkbox->checkState()){
           cardArr |= 1UL << i;         // if checkbox ID (i+1) is true then bit number (i) of cardArr is setted
       }
       else {
           cardArr &= ~(1UL << i);      // if checkbox ID (i+1) is false then bit number (i) of cardArr is unsetted
       }
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
            if (is_matched_cards(indexCard1, indexCard2))
            {
                disable_cards(indexCard1, indexCard2);
                qDebug("---IT'S A MATCH!!!---");
            }
            else
            {
                uncheck_cards(indexCard1,indexCard2);
                qDebug("---NOT A MATCH!!!---");
            }
            // to do: add a sleep function, maybe create a new one, or (learn to) use QThread
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
        qDebug("---Finish a move---");
    }
};

void MainWindow::change_card_availability(bool state)
{
    for (uint i = 0; i < 16; i++)
    {
        get_checkbox_ID(i+1);
        checkbox->setCheckable(state);
    }
};

bool MainWindow::is_matched_cards(uint card1, uint card2)
{
    //todo: compare card if match
    get_checkbox_ID(card1);
    QString compareStyleSheet = checkbox->styleSheet();

    get_checkbox_ID(card2);
    if (compareStyleSheet == checkbox->styleSheet())
    {
        return true;
    }
    else
    {
        return false;
    }
};

void MainWindow::disable_cards(uint card1, uint card2)
{
    //todo: disable card
    get_checkbox_ID(card1);
    checkbox->setChecked(true);
    checkbox->setEnabled(false);

    get_checkbox_ID(card2);
    checkbox->setChecked(true);
    checkbox->setEnabled(false);
};

void MainWindow::uncheck_cards(uint card1, uint card2)
{
    for (uint i = 0; i < 16; i++)
    {
       if (card1 == i + 1 || card2 == i + 1)
       {
           get_checkbox_ID(i+1);
           checkbox->setChecked(false);
       }
    }

    reset_index();
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

    // Step 3 (need to find a quicker way to do this -> DONE!)

    for (int i = 0; i < 16; i++)
    {
       get_checkbox_ID(i+1);
       checkbox->setStyleSheet(defaultStyleSheet + appendStyleSheet[i]);
    }
}

void MainWindow::get_checkbox_ID(uint card)
{
    switch(card)
    {
        case 1:
            checkbox = ui->cardCheckBox_1;
        break;

        case 2:
            checkbox = ui->cardCheckBox_2;
        break;

        case 3:
            checkbox = ui->cardCheckBox_3;
        break;

        case 4:
            checkbox = ui->cardCheckBox_4;
        break;

        case 5:
            checkbox = ui->cardCheckBox_5;
        break;

        case 6:
            checkbox = ui->cardCheckBox_6;
        break;

        case 7:
            checkbox = ui->cardCheckBox_7;
        break;

        case 8:
            checkbox = ui->cardCheckBox_8;
        break;

        case 9:
            checkbox = ui->cardCheckBox_9;
        break;

        case 10:
            checkbox = ui->cardCheckBox_10;
        break;

        case 11:
            checkbox = ui->cardCheckBox_11;
        break;

        case 12:
            checkbox = ui->cardCheckBox_12;
        break;

        case 13:
            checkbox = ui->cardCheckBox_13;
        break;

        case 14:
            checkbox = ui->cardCheckBox_14;
        break;

        case 15:
            checkbox = ui->cardCheckBox_15;
        break;

        case 16:
            checkbox = ui->cardCheckBox_16;
        break;
    }
}

void MainWindow::reset_index()
{
    indexCard1 = 0;
    indexCard2 = 0;
    qDebug("---RESET INDEXES: DONE!---");
}

