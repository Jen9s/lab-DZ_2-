#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSettings>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableView->setModel(model);
    ui->tableView->setSortingEnabled(true);
    ui->tableView->horizontalHeader()->setSortIndicatorShown(true);
    ui->tableView->setColumnWidth(0, 400);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Interactive);
    ui->tableView->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::row_counter = 0;

void MainWindow::on_pushButton_clicked()
{
    model->insertRow(row_counter);
    row_counter++;
}
