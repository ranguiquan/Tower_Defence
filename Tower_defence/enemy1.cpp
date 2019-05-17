#include "enemy1.h"
#include <QPixmap>
#include "config.h"

Enemy1::Enemy1()
{
    this->icon = new QPixmap;
    this->icon->load(":/pictures/enemy/enemy2.png");
    this->position.setX(100);
    this->position.setY(500);
    direction_x = 1;
    direction_y = 0;
    this->width = ENEMY_2_WIDTH;
    this->height = ENEMY_2_HEIGHT;
    this->life = ENEMY_2_LIFE;
    this->velocity = ENEMY_2_VELOCITY;
}
