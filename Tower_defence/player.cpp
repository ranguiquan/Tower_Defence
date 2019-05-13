#include "player.h"
#include <QPixmap>
#include "config.h"

Player::Player()
{
    this->icon = new QPixmap;
    this->icon->load(":/pictures/enemy_test.png");
    this->position.setX(200);
    this->position.setY(100);

    this->width = PLAYER_1_WIDTH;
    this->height = PLAYER_1_HEIGHT;
    this->life = PLAYER_1_LIFE;

}
