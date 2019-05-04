#include "enemy.h"
#include <QPixmap>
#include "config.h"

Enemy::Enemy()
{
    this->icon = new QPixmap;
    this->icon->load(":/pictures/enemy_test.png");
    this->position.setX(100);
    this->position.setY(500);
    direction_x = 1;
    direction_y = 0;
    this->width = ENEMY_1_WIDTH;
    this->height = ENEMY_1_HEIGHT;
    this->life = ENEMY_1_LIFE;
    this->velocity = ENEMY_1_VELOCITY;

}
