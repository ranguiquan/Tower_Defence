#include "enemy9.h"
#include <QPixmap>
#include "config.h"

Enemy9::Enemy9()
{
    this->icon = new QPixmap;
    this->icon->load(":/pictures/enemy/enemy10.png");
    this->position.setX(100);
    this->position.setY(500);
    direction_x = 1;
    direction_y = 0;
    this->width = ENEMY_10_WIDTH;
    this->height = ENEMY_10_HEIGHT;
    this->life = ENEMY_10_LIFE;
    this->velocity = ENEMY_10_VELOCITY;
}
