#include "enemy6.h"
#include <QPixmap>
#include "config.h"

Enemy6::Enemy6()
{
    this->icon = new QPixmap;
    this->icon->load(":/pictures/enemy/enemy7.png");
    this->position.setX(100);
    this->position.setY(500);
    direction_x = 1;
    direction_y = 0;
    this->width = ENEMY_7_WIDTH;
    this->height = ENEMY_7_HEIGHT;
    this->life = ENEMY_7_LIFE;
    this->velocity = ENEMY_7_VELOCITY;
}
