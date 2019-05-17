#include "enemy2.h"
#include <QPixmap>
#include "config.h"

Enemy2::Enemy2()
{
    this->icon = new QPixmap;
    this->icon->load(":/pictures/enemy/enemy3.png");
    this->position.setX(100);
    this->position.setY(500);
    direction_x = 1;
    direction_y = 0;
    this->width = ENEMY_3_WIDTH;
    this->height = ENEMY_3_HEIGHT;
    this->life = ENEMY_3_LIFE;
    this->velocity = ENEMY_3_VELOCITY;
}
