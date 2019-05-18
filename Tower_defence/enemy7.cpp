#include "enemy7.h"
#include <QPixmap>
#include "config.h"

Enemy7::Enemy7()
{
    this->icon = new QPixmap;
    this->icon->load(":/pictures/enemy/enemy8.png");
    this->position.setX(100);
    this->position.setY(500);
    direction_x = 1;
    direction_y = 0;
    this->width = ENEMY_8_WIDTH;
    this->height = ENEMY_8_HEIGHT;
    this->life = ENEMY_8_LIFE;
    this->velocity = ENEMY_8_VELOCITY;
}
