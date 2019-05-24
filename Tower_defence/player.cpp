#include "player.h"
#include <QPixmap>
#include "config.h"

Player::Player()
{
    this->icon = new QPixmap;
    this->icon->load(":/pictures/enemy_test.png");
    this->position.setX(700);
    this->position.setY(200);

    this->width = PLAYER_1_WIDTH;
    this->height = PLAYER_1_HEIGHT;
    this->life = PLAYER_1_LIFE;
    this->money = PLAYER_1_MONEY;

}


