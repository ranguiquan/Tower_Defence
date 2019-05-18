#include "enemy5.h"
#include <QPixmap>
#include "config.h"

Enemy5::Enemy5()
{
    this->icon = new QPixmap;
    this->icon->load(":/pictures/enemy/enemy6.png");
    this->position.setX(100);
    this->position.setY(500);
    direction_x = 1;
    direction_y = 0;
    this->width = ENEMY_6_WIDTH;
    this->height = ENEMY_6_HEIGHT;
    this->life = ENEMY_6_LIFE;
    this->velocity = ENEMY_6_VELOCITY;
}
