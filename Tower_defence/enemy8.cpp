#include "enemy8.h"
#include <QPixmap>
#include "config.h"

Enemy8::Enemy8()
{
    this->icon = new QPixmap;
    this->icon->load(":/pictures/enemy/enemy9.png");
    this->position.setX(100);
    this->position.setY(500);
    direction_x = 1;
    direction_y = 0;
    this->width = ENEMY_9_WIDTH;
    this->height = ENEMY_9_HEIGHT;
    this->life = ENEMY_9_LIFE;
    this->velocity = ENEMY_9_VELOCITY;
}
