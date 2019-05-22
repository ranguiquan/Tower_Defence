#include "blood.h"
#include <QPainter>
#include <QtDebug>

Blood::Blood(Enemy *parent)
{
    this->parent=parent;
    setMinimum(0);
    setMaximum(100);
    rect = QRect(parent->getPosition_x(), parent->getPosition_y()-10, 60, 15);
    textRect = QRect(parent->getPosition_x(), parent->getPosition_y()-10, 60, 15);
    buttomMap = QPixmap(":/pictures/enemy/radius_back.png");
    fillMap = QPixmap(":/pictures/enemy/radius_front.png");
    f = QFont("Microsoft YaHei", 10, QFont::Bold);
}

void Blood::show(QPainter *p)
{
    if(parent->getDamage()||parent->isChosen)
    {
        k = (double)(value() - minimum()) / (maximum()-minimum());
        x = (int)(rect.width() * k);
        fillRect = rect.adjusted(0, 0, x-rect.width(), 0);
        //画进度条
        rect.moveTo(parent->getPosition_x(), parent->getPosition_y()-10);
        textRect.moveTo(parent->getPosition_x(), parent->getPosition_y()-10);
        fillRect.moveTo(parent->getPosition_x(), parent->getPosition_y()-10);
        p->drawPixmap(rect, buttomMap);
        p->drawPixmap(fillRect, fillMap);

        //画文字
        p->setFont(f);
        p->setPen(QColor("#555555"));
        p->drawText(textRect, Qt::AlignCenter, valueStr);
        valueStr = QString("%1%").arg(QString::number(value()));
        this->setValue(100*(parent->getLife())/(parent->getOriginalLife()));
    }
}
