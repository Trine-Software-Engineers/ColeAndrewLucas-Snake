#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QTimer>
#include <QDebug>
#include <QKeyEvent>
#include <random>
#include "QDateTime"
#include <QApplication>
#include <QMessageBox>
#include <QVector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    virtual void paintEvent(QPaintEvent *event);
public slots:
    void myfunction();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_lcdNumber_overflow();

private:
    Ui::MainWindow *ui;
    QTimer *timer;


protected:
    void keyPressEvent(QKeyEvent *e);

};

void GameOverBox();
void addSegment();
void StartBox();

static const int W_WIDTH = 600;
static const int W_HEIGHT = 600;
static QString snakeHeadDirection = "DOWN"; // direction snake is going
static
int applex = 0; // x coordinate of apple
static int appley = 0; // y coordinate of apple
static
char lastinput = 'S'; //last valid input that the snake will take, starts snake going down
static bool playing = true; //game still playing
static int MSbetweenFrames; //time between frames in milliseconds
static bool SpawnApple = true; //game needs to spawn apple next frame
static int score = 1;
int getRand(int min, int max, unsigned int seed);

struct segment{
    //current position of snake
    int cx = W_WIDTH / 2;
    int cy = W_HEIGHT / 2;

    //past position of snake
    int px;
    int py;
};

static QVector<segment> snake;



#endif // MAINWINDOW_H
