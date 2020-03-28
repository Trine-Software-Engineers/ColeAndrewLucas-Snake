#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <QDialog>

namespace Ui {
class leaderboard;
}

class leaderboard : public QDialog
{
    Q_OBJECT

public:
    explicit leaderboard(QWidget *parent = nullptr);
    ~leaderboard();
<<<<<<< Updated upstream



public slots:
=======
>>>>>>> Stashed changes
    void showLeaderboard();

private:
    Ui::leaderboard *ui;
<<<<<<< Updated upstream

    enum Column {
        NAME, _SCORE
    };
};



=======
};

>>>>>>> Stashed changes
#endif // LEADERBOARD_H
