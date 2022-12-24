#ifndef CARD_H
#define CARD_H
#include "ui_mainwindow.h"
#include <QMainWindow>
#include <QBitArray>
#include <cstdlib>
#include <iostream>
#include <random>
#include <chrono>
#include <algorithm>
#include <array>
#include <QCheckBox>
#include <QMessageBox>

class Card
{
public:
    ~Card()
    {
        delete ui;
    }

    void initialize(Ui::MainWindow *ui);
    bool get_card_state();
    void disable_cards(uint card1, uint card2);
    void change_card_availability(bool);
    bool is_matched_cards(uint card1, uint card2);
    void card_compare(uint card1, uint card2);
    bool card_handler(uint cardId, bool status);
    void add_random_images();
    void set_started_status(bool);
private:
    bool game_started = false;
    Ui::MainWindow *ui;
    std::unordered_map<int, QCheckBox*> checkbox_map;
    int num_open_cards = 0;
    int pre_open_card = 0; //0 mean invalid
    std::array<QString, 16> appendStyleSheet;
    int player_move = 0;
    uint total_pair = 0;
};

#endif // CARD_H
