#include <QProgressBar>
#include "playerinfo.h"
#include "player.h"
#include "config.h"

PlayerInfo::PlayerInfo(Player * player, string infotype)
{
    this->player = player;
    this->type = infotype;
    setMinimum(0);
    if(type.compare("life") == 0){
        setMaximum(PLAYER_1_LIFE);
        rect = QRect(player->getPosition_x(),player->getPosition_y()-40, 120, 20);
        textRect = QRect(player->getPosition_x(),player->getPosition_y()-40, 120, 20);
    }
    else if(type.compare("money")==0){
        setMaximum(PLAYER_1_MONEY);
        rect = QRect(player->getPosition_x(),player->getPosition_y()-10, 120, 20);
        textRect = QRect(player->getPosition_x(),player->getPosition_y()-10, 120, 20);
    }


    buttomMap = QPixmap(":/pictures/enemy/radius_back.png");
    fillMap = QPixmap(":/pictures/enemy/radius_front.png");
    f = QFont("Microsoft YaHei", 10, QFont::Bold);
}


void PlayerInfo::show(QPainter *p)
{
    if(type.compare("life") == 0){
        this->setValue(player->getLife());
    }
    else if (type.compare("money") == 0) {
        this->setValue(player->getMoney());
    }


    k = (double)(value() - minimum()) / (maximum()-minimum());
    x = (int)(rect.width() * k);
    fillRect = rect.adjusted(0, 0, x-rect.width(), 0);
    //画进度条
    //rect.moveTo(player->getPosition_x(),player->getPosition_y()-10);
    //textRect.moveTo(player->getPosition_x(),player->getPosition_y()-10);
    //fillRect.moveTo(player->getPosition_x(),player->getPosition_y()-10);
    p->drawPixmap(rect, buttomMap);
    p->drawPixmap(fillRect, fillMap);

    //画文字
    p->setFont(f);
    p->setPen(QColor("#555555"));
    p->drawText(textRect, Qt::AlignCenter, valueStr);
    valueStr = QString::fromStdString(type)+QString(": %1").arg(QString::number(value()));


}

