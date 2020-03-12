#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QKeyEvent>
#include <random>
#include "QDateTime"
#include <QApplication>
#include <QMessageBox>
#include <QVector>
#include <QPushButton>
#include <QSize>


QString snakeHeadDirection = "DOWN"; // direction snake is going

int applex = 0; // x coordinate of apple
int appley = 0; // y coordinate of apple

char lastinput = 'S'; //last valid input that the snake will take, starts snake going down
bool playing = true; //game still playing
int MSbetweenFrames; //time between frames in milliseconds
bool SpawnApple = true; //game needs to spawn apple next frame

int score = 1;

struct segment{
    //current position of snake
    int cx;
    int cy;

    //past position of snake
    int px;
    int py;
};

QVector<segment> snake;

int getRand(int min, int max, unsigned int seed);
void GameOverBox();
void addSegment();
void StartBox();

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),

    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setMinimumSize(W_WIDTH, W_HEIGHT);
    setFixedSize(W_WIDTH, W_HEIGHT);
    //setup time between frames
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this,SLOT(myfunction()));
    addSegment();
    StartBox();
    timer->start(MSbetweenFrames);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter( this);

    //only draw frame if "playing"
    if(playing)
    {
        //draw snake
        int temp = 0;
        while(temp < snake.size())
        {
            painter.setBrush( Qt::black );
            painter.drawRect(snake[temp].cx, snake[temp].cy, 10, 10);
            temp++;
        }

        //spawn new apple
        if(SpawnApple)
        {
            //spawn apple in random location
            applex = getRand(1,28,1) * 10;
            appley = getRand(1,28,2) * 10;

            //make sure apple isn't in snake
            temp = 0;
            while(temp < snake.size())
            {
                //if apple spawns in snake, try another random location until apple is not in snake
                if(applex == snake[temp].cx && appley == snake[temp].cy)
                {
                    applex = getRand(1,28,1) * 10;
                    appley = getRand(1,28,2) * 10;
                    temp = 0;
                }
                temp++;
            }
            SpawnApple = false;
        }

        //draw apple
        painter.setBrush( Qt::red );
        painter.drawRect(applex, appley, 10, 10);
    }
}

//called every "MSbetweenFrames"
void MainWindow::myfunction()
{
    //mark current location as past location for each segment
    int temp = 0;
    while(temp < snake.size())
    {
        snake[temp].px = snake[temp].cx;
        snake[temp].py = snake[temp].cy;
        temp++;
    }

    //move snake head by last valid input
    if(lastinput == 'W')
    {
        snake[0].cy += -10;
        snakeHeadDirection = "UP";
    }
    else if(lastinput == 'S')
    {
        snake[0].cy += 10;
        snakeHeadDirection = "DOWN";
    }
    else if(lastinput == 'A')
    {
        snake[0].cx += -10;
        snakeHeadDirection = "LEFT";
    }
    else
    {
        snake[0].cx += 10;
        snakeHeadDirection = "RIGHT";
    }


    //if snake head hits wall, end game
    if(snake[0].cx >= QWidget::width() || snake[0].cx < 0 || snake[0].cy >= QWidget::height() || snake[0].cy < 0)
    {
        playing = false;
        GameOverBox();
    }


    //if snake head eats apple
    if(snake[0].cx == applex && snake[0].cy == appley)
    {
        SpawnApple = true;
        score += 1;
        addSegment();
    }

    //move rest of snake
    temp = 1;
    while(temp < snake.size())
    {
        snake[temp].cx = snake[temp - 1].px;
        snake[temp].cy = snake[temp - 1].py;
        temp++;
    }

    //if snake head runs into snake tail, end game
    temp = 1;
    while(temp < snake.size())
    {
        if(snake[0].cx == snake[temp].cx && snake[0].cy == snake[temp].cy)
        {
            playing = false;
            GameOverBox();
        }
        temp++;
    }

    //update frame
    update();
}

//runs every time any key is pressed
void MainWindow::keyPressEvent(QKeyEvent *e)
{
    //get input
    char currentinput = char(e->key());

    //check for valid input
    if(currentinput == 'W' || currentinput == 'S' || currentinput == 'A' || currentinput == 'D')
    {
        //don't allow snake to go backwards
        if(snakeHeadDirection == "UP"       && currentinput == 'S') return;
        if(snakeHeadDirection == "LEFT"     && currentinput == 'D') return;
        if(snakeHeadDirection == "DOWN"     && currentinput == 'W') return;
        if(snakeHeadDirection == "RIGHT"    && currentinput == 'A') return;

        //assign new direction
        lastinput = currentinput;
    }
}

//grab random number between two values. Also takes a seed as input.
int getRand(int min, int max, unsigned int seed){
    unsigned int ms = static_cast<unsigned>(QDateTime::currentMSecsSinceEpoch()) + seed;
    std::mt19937 gen(ms);
    std::uniform_int_distribution<> uid(min, max);
    return uid(gen);
}

void GameOverBox()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Game Over!");
    msgBox.setText("Your snake was: " + QString::number(score) + " segments long!\nThank you for playing. Do you want to play again?");
    msgBox.setStandardButtons(QMessageBox::Yes);
    msgBox.addButton(QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);

    //if they want to play again, reset game
    if(msgBox.exec() == QMessageBox::Yes)
    {
        //remove snake segments
        int temp = snake.size();
        while(temp > 0)
        {
            snake.pop_back();
            temp--;
        }
        addSegment();

        playing = true;
        score = 1;
        snake[0].cx = 10;
        snake[0].cy = 10;
        lastinput = 'S';
        SpawnApple = true;


    }
    //else quit
    else
    {
      QApplication::quit();
    }
}

void StartBox()
{
    qDebug() << "MsgBox opened";
    QMessageBox msgBox;
    msgBox.setWindowTitle("Snake Game");
    msgBox.setText("Select your difficulty");


    /*
    msgBox.addButton(QMessageBox::Yes);
    msgBox.addButton(QMessageBox::No);
    msgBox.addButton(QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Yes);


    msgBox.setButtonText(QMessageBox::Yes, ("Slug"));
    msgBox.setButtonText(QMessageBox::No, ("Worm"));
    msgBox.setButtonText(QMessageBox::Cancel, ("Python"));
*/
    QAbstractButton *slugButton = msgBox.addButton("Slug", QMessageBox::ActionRole);
    QAbstractButton *wormButton = msgBox.addButton("Worm", QMessageBox::ActionRole);
    QAbstractButton *pythonButton = msgBox.addButton("Python", QMessageBox::ActionRole);

    msgBox.exec();

    if(msgBox.clickedButton() == slugButton)
    {
        MSbetweenFrames = 100;

    }
    else if(msgBox.clickedButton() == wormButton)
    {
        MSbetweenFrames = 75;

    }
    else if(msgBox.clickedButton() == pythonButton)
    {
        MSbetweenFrames = 50;

    }

}

void addSegment()
{
    segment newsegment;
    snake.push_back(newsegment);
}

