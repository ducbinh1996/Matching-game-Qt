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
#include <QThread>

class Card
{
public:
    void initialize(Ui::MainWindow *ui);
    bool get_card_state();
    void disable_cards(uint card1, uint card2);
    void change_all_cards_availability(bool);
    bool is_matched_cards(uint card1, uint card2);
    void card_compare(uint card1, uint card2);
    void card_handler(uint cardId, bool status);
    void add_random_images();
private:
    Ui::MainWindow *ui;
    std::unordered_map<int, QCheckBox*> checkbox_map;
    int num_opened_cards = 0;
    int pre_opened_card_id = 0; //0 mean invalid
    std::array<QString, 16> appendStyleSheet;
};

#endif // CARD_H
