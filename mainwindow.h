#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QTimer>

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

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    const int W_WIDTH = 400;
    const int W_HEIGHT = 400;

protected:
    void keyPressEvent(QKeyEvent *e);
};



#endif // MAINWINDOW_H
