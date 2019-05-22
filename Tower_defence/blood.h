#ifndef BLOOD_H
#define BLOOD_H
#include "gameobject.h"
#include "enemy.h"
#include "mypoint.h"
#include <QProgressBar>

class Blood: public QProgressBar
{
    Q_OBJECT
public:
    Blood(Enemy *parent);
    void show(QPainter *p);
private:
    Enemy *parent;
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

#endif // BLOOD_H
