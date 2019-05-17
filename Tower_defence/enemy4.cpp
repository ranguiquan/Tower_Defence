#include "enemy4.h"
#include <QPixmap>
#include "config.h"

Enemy4::Enemy4()
{
    this->icon = new QPixmap;
    this->icon->load(":/pictures/enemy/enemy5.png");
    this->position.setX(100);
    this->position.setY(500);
    direction_x = 1;
    direction_y = 0;
    this->width = ENEMY_5_WIDTH;
    this->height = ENEMY_5_HEIGHT;
    this->life = ENEMY_5_LIFE;
    this->velocity = ENEMY_5_VELOCITY;
}
