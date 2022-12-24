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
#include <QMessageBox>
#include "card.h"

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

    void game_ended_handler();

    void on_cardCheckBox_1_clicked(bool checked);
    void on_cardCheckBox_2_clicked(bool checked);
    void on_cardCheckBox_3_clicked(bool checked);
    void on_cardCheckBox_4_clicked(bool checked);
    void on_cardCheckBox_5_clicked(bool checked);
    void on_cardCheckBox_6_clicked(bool checked);
    void on_cardCheckBox_7_clicked(bool checked);
    void on_cardCheckBox_8_clicked(bool checked);
    void on_cardCheckBox_9_clicked(bool checked);
    void on_cardCheckBox_10_clicked(bool checked);
    void on_cardCheckBox_11_clicked(bool checked);
    void on_cardCheckBox_12_clicked(bool checked);
    void on_cardCheckBox_13_clicked(bool checked);
    void on_cardCheckBox_14_clicked(bool checked);
    void on_cardCheckBox_15_clicked(bool checked);
    void on_cardCheckBox_16_clicked(bool checked);

private:
    Ui::MainWindow *ui;
    bool gameStarted{false};
    Card* card = new Card;
    QMessageBox msgBox;
    bool player_win = true;
};
#endif // MAINWINDOW_H
