#ifndef PLAYERINFO_H
#define PLAYERINFO_H

#include <QProgressBar>
#include <QString>
#include "mypoint.h"
#include "player.h"

using namespace std;

class PlayerInfo : public QProgressBar
{
    //Q_OBJECT
public:
    PlayerInfo(Player * player,string type);
    void show(QPainter *p);
private:

    Player * player;
    string type;

    QRect rect;
    QRect textRect;
    QFont f;
    double k;
    int x;
    QRect fillRect;

    QString valueStr;
    QPixmap buttomMap;
    QPixmap fillMap;
};

#endif // PLAYERINFO_H
