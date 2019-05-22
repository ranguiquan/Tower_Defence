#include "blood.h"
#include <QPainter>

Blood::Blood(Enemy *parent)
{
    this->parent=parent;
    setMinimum(0);
    setMaximum(100);
//    setValue(parent->getOriginalLife());
}

void Blood::show(QPainter *p)
{
    if(parent->isChosen()||parent->getDamage())
    {
        QRect rect = QRect(parent->getPosition_x(), parent->getPosition_y()-10, 60, 15);
        QRect textRect = QRect(parent->getPosition_x(), parent->getPosition_y()-10, 60, 15);

        double k = (double)(value() - minimum()) / (maximum()-minimum());
        int x = (int)(rect.width() * k);
        QRect fillRect = rect.adjusted(0, 0, x-rect.width(), 0);

        QString valueStr = QString("%1%").arg(QString::number(value()));
        QPixmap buttomMap = QPixmap(":/pictures/enemy/radius_back.png");
        QPixmap fillMap = QPixmap(":/pictures/enemy/radius_front.png");

        //画进度条
        p->drawPixmap(rect, buttomMap);
        p->drawPixmap(fillRect, fillMap, fillRect);

        //画文字
        QFont f = QFont("Microsoft YaHei", 10, QFont::Bold);
        p->setFont(f);
        p->setPen(QColor("#555555"));
        p->drawText(textRect, Qt::AlignCenter, valueStr);

        this->setValue(100*(parent->getLife())/(parent->getOriginalLife()));
    }
}
