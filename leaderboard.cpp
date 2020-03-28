#include "leaderboard.h"
#include "ui_leaderboard.h"

leaderboard::leaderboard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::leaderboard)
{
    ui->setupUi(this);
    setWindowTitle("Leaderboard");
    ui->tableWidget->setColumnCount(2);
    QStringList columnTitles;
    columnTitles << "Name" << "Score";
    ui->tableWidget->setHorizontalHeaderLabels(columnTitles);
}
<<<<<<< Updated upstream

leaderboard::~leaderboard()
{
    delete ui;
}

void leaderboard::showLeaderboard() {
    int rownum;
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    rownum = ui->tableWidget->rowCount() - 1;
    ui->tableWidget->setItem(rownum, NAME, new QTableWidgetItem("DRU"));
    ui->tableWidget->setItem(rownum, _SCORE, new QTableWidgetItem("15"));
=======

leaderboard::~leaderboard()
{
    delete ui;
>>>>>>> Stashed changes
}

void leaderboard::showLeaderboard() {
    int rownum;
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    rownum = ui->tableWidget->rowCount() - 1;
    ui->tableWidget->setItem(rownum, 0, new QTableWidgetItem("DRU"));
    ui->tableWidget->setItem(rownum, 1, new QTableWidgetItem("15"));
}
