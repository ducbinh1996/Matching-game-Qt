#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWidget>

QTimer *timer = new QTimer();
QTime playTime(0,1,59);

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

MainWindow::~MainWindow() // destructor of MainWindow
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
        ui->moveNumber->display((int)playerMove);
        card->add_random_images();
        gameStarted = true;
        card->change_card_availability(true);
        ui->startBtn->setVisible(false);
    }

}

void MainWindow::updateCountdown()
{
    if (gameStarted)
    {
        playTime = playTime.addSecs(-1);
    }

    if(game_ended() || debug) // open all the cards, or debug is true (just to reproduce winning the game)
    {
        msgBox.setIconPixmap(QPixmap(":win.jpg")); // to do: print the move count, the remain time,...
        msgBox.exec();
        cardArr = 0;          // reset the value so it doesn't keep openning the msgBox
        debug = false;
        gameStarted = false;
    }

    QString timerText = playTime.toString("mm:ss");
    ui->timerDisplay->setText(timerText);
    ui->outputLabel->setText(QString::number(cardArr));
    ui->moveNumber->display(card->get_move_count());
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

uint MainWindow::find_bit_index(uint card)
{
    uint index = log(card)/log(2) + 1; // logarit with base 2 can be calculated from natural logarit of 2
    return index;
}

void MainWindow::reset_index()
{
    indexCard1 = 0;
    indexCard2 = 0;
    qDebug("---RESET INDEXES: DONE!---");
}

bool MainWindow::game_ended()
{
    if (cardArr == 0xFFFF)
    {
        return true;
    }
    else
    {
        return false;
    }
}


void MainWindow::on_pushButton_clicked()
{
    debug = true; // to reproduce when we win the game
}

void MainWindow::on_cardCheckBox_1_clicked(bool checked)
{
    card->card_handler(1, checked);
}

void MainWindow::on_cardCheckBox_2_clicked(bool checked)
{
    card->card_handler(2, checked);
}

void MainWindow::on_cardCheckBox_3_clicked(bool checked)
{
    card->card_handler(3, checked);
}

void MainWindow::on_cardCheckBox_4_clicked(bool checked)
{
    card->card_handler(4, checked);
}

void MainWindow::on_cardCheckBox_5_clicked(bool checked)
{
    card->card_handler(5, checked);
}

void MainWindow::on_cardCheckBox_6_clicked(bool checked)
{
    card->card_handler(6, checked);
}

void MainWindow::on_cardCheckBox_7_clicked(bool checked)
{
    card->card_handler(7, checked);
}

void MainWindow::on_cardCheckBox_8_clicked(bool checked)
{
    card->card_handler(8, checked);
}

void MainWindow::on_cardCheckBox_9_clicked(bool checked)
{
    card->card_handler(9, checked);
}

void MainWindow::on_cardCheckBox_10_clicked(bool checked)
{
    card->card_handler(10, checked);
}

void MainWindow::on_cardCheckBox_11_clicked(bool checked)
{
    card->card_handler(11, checked);
}

void MainWindow::on_cardCheckBox_12_clicked(bool checked)
{
    card->card_handler(12, checked);
}

void MainWindow::on_cardCheckBox_13_clicked(bool checked)
{
    card->card_handler(13, checked);
}

void MainWindow::on_cardCheckBox_14_clicked(bool checked)
{
    card->card_handler(14, checked);
}

void MainWindow::on_cardCheckBox_15_clicked(bool checked)
{
    card->card_handler(15, checked);
}

void MainWindow::on_cardCheckBox_16_clicked(bool checked)
{
    card->card_handler(16, checked);
}
