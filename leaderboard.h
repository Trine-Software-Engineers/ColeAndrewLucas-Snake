#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <QString>


class Leaderboard
{
public:
    Leaderboard();

private:
    QString filename = "leaderboard.json";

    QString readFile();
};

#endif // HIGHSCORE_H
