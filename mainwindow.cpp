#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_goToGameBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(1); // move to page_2 (index 1) in stackedWidget
}

