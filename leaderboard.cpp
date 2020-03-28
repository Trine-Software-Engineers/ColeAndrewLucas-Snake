#include "leaderboard.h"
#include "ui_leaderboard.h"

#include <QInputDialog>
#include <QFile>
#include <QDebug>

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

leaderboard::~leaderboard()
{
    delete ui;
}
int lscore;
void leaderboard::setScore(int newscore) {
    lscore = newscore;
}

void leaderboard::showLeaderboard() {
    leaderboard board;
    board.exec();
    int rownum;
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    rownum = ui->tableWidget->rowCount() - 1;
    ui->tableWidget->setItem(rownum, 0, new QTableWidgetItem("DRU"));
    ui->tableWidget->setItem(rownum, 1, new QTableWidgetItem(QString::number(lscore)));
}

struct LeaderboardRow {
    QString name;
    int score;
};

void LeaderboardUpdate()
{
    QFile file("leaderboard.csv");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << file.errorString();
//        return 1;
    }

    //    QStringList nameList;
    //    int scoreList[10];
    QVector<LeaderboardRow> leaderboard;
    while (!file.atEnd())
    {
        QByteArray line = file.readLine();
        LeaderboardRow row;
        row.name = line.split(',').first();
        row.score = line.split(',').at(1).toInt();
        leaderboard.append(row);
//        nameList.append(line.split(',').first());
//        scoreList.append( line.split(',').at(1).toInt() );
    }
//    file.close();

    int topScore = 0;
    for (int i = 0; i < leaderboard.size(); ++i)
    {
        if (leaderboard.at(i).score > topScore)
        {
            topScore = leaderboard.at(i).score;
        }
    }

//    qDebug() << nameList;
    if (lscore > topScore)
    {
        bool ok;
        QString name = QInputDialog::getText(0, "New High Score!",
                                                 "Player Name:", QLineEdit::Normal,
                                                 "", &ok);
        for (int i = 0; i < leaderboard.size(); ++i)
        {
            if (leaderboard.at(i).score < lscore)
            {
                LeaderboardRow newRow;
                newRow.name = name;
                newRow.score = lscore;
                leaderboard.insert(i, newRow);
                leaderboard.pop_back();
                break;
            }
        }
    }



//    QFile outfile("leaderboard.csv");
    QTextStream out(&file);

    if (file.open(QIODevice::ReadWrite))
//        return;
    {
        for (int i = 0; i < leaderboard.size(); ++i)
        {
            out << leaderboard.at(i).name << "," << QString::number(leaderboard.at(i).score) << endl;
        }
    }
    out.flush();
    file.close();

//    if (ok && !text.isEmpty())
//        textLabel->setText(text);
}
