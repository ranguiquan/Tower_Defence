#include "enemy3.h"
#include <QPixmap>
#include "config.h"

Enemy3::Enemy3()
{
    this->icon = new QPixmap;
    this->icon->load(":/pictures/enemy/enemy4.png");
    this->position.setX(100);
    this->position.setY(500);
    direction_x = 1;
    direction_y = 0;
    this->width = ENEMY_4_WIDTH;
    this->height = ENEMY_4_HEIGHT;
    this->life = ENEMY_4_LIFE;
    this->velocity = ENEMY_4_VELOCITY;
}
