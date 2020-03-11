#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(W_WIDTH, W_HEIGHT);
    w.show();

    return a.exec();
}
