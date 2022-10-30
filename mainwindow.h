#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QDateTime>
#include <QBitArray>

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

    void diable_cards(uint card);

    void uncheck_cards(uint card1, uint card2);

    uint find_bit_index(uint card);

private:
    Ui::MainWindow *ui;
    uint playerMove{0};
    bool gameStarted{false};
    uint cardArr =  0x0000;
    int numberOfMove = 0;       // should we change the type to uint too?
    int numberOfOpenCard = 0;
};
#endif // MAINWINDOW_H
