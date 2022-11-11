#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QDateTime>
#include <QBitArray>
#include <cstdlib>
#include <iostream>
#include <random>
#include <chrono>
#include <algorithm>
#include <array>
#include <QCheckBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_goToGameBtn_clicked();

    void on_startBtn_clicked();

    void updateCountdown();

    void on_pauseBtn_clicked();

    void on_resumeBtn_clicked();

    void mapping_card_value();

    void change_card_availability(bool);

    bool is_matched_cards(uint card1, uint card2);

    void disable_cards(uint card1, uint card2);

    void uncheck_cards(uint card1, uint card2);

    uint find_bit_index(uint card);

    void add_random_images();

    void get_checkbox_ID(uint card);

    void reset_index();

private:
    Ui::MainWindow *ui;
    uint playerMove{0};
    bool gameStarted{false};
    uint cardArr =  0x0000;
    int numberOfMove = 0;       // should we change the type to uint too?
    int numberOfOpenCard = 0;
    uint oldCardArr = 0x0000;
    uint indexBitCardArr = 0;
    uint indexOpenCard = 0;
    uint indexCard1 = 0;
    uint indexCard2 = 0;
    std::array<QString, 16> appendStyleSheet;
    QCheckBox *checkbox = new QCheckBox("", this);
};
#endif // MAINWINDOW_H
