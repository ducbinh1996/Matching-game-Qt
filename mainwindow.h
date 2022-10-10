#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QDateTime>

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

private:
    Ui::MainWindow *ui;
    uint playerMove{0};
    bool gameStarted{false};
};
#endif // MAINWINDOW_H
