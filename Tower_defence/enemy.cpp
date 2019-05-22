#include "enemy.h"
#include <QPixmap>
#include "config.h"

Enemy::Enemy(string name)
{
    this->damage = false;
    if(name.compare("Enemy") == 0)
    {
        this->icon = new QPixmap;
        this->icon->load(":/pictures/enemy/enemy1.png");
        this->position.setX(100);
        this->position.setY(500);
        direction_x = 1;
        direction_y = 0;
        this->width = ENEMY_1_WIDTH;
        this->height = ENEMY_1_HEIGHT;
        this->life = ENEMY_1_LIFE;
        this->originalLife=ENEMY_1_LIFE;
        this->velocity = ENEMY_1_VELOCITY;
       }
    else if(name.compare("Enemy1") == 0)
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
        this->originalLife=ENEMY_2_LIFE;
        this->velocity = ENEMY_2_VELOCITY;
    }
    else if(name.compare("Enemy2") == 0)
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
        this->originalLife=ENEMY_3_LIFE;
        this->velocity = ENEMY_3_VELOCITY;
    }
    else if(name.compare("Enemy3") == 0)
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
        this->originalLife=ENEMY_4_LIFE;
        this->velocity = ENEMY_4_VELOCITY;
    }
    else if(name.compare("Enemy4") == 0)
    {
        this->icon = new QPixmap;
        this->icon->load(":/pictures/enemy/enemy5.png");
        this->position.setX(100);
        this->position.setY(500);
        direction_x = 1;
        direction_y = 0;
        this->width = ENEMY_5_WIDTH;
        this->height = ENEMY_5_HEIGHT;
        this->life = ENEMY_5_LIFE;
        this->originalLife=ENEMY_5_LIFE;
        this->velocity = ENEMY_5_VELOCITY;
    }
    else if(name.compare("Enemy5") == 0)
    {
        this->icon = new QPixmap;
        this->icon->load(":/pictures/enemy/enemy6.png");
        this->position.setX(100);
        this->position.setY(500);
        direction_x = 1;
        direction_y = 0;
        this->width = ENEMY_6_WIDTH;
        this->height = ENEMY_6_HEIGHT;
        this->life = ENEMY_6_LIFE;
        this->originalLife=ENEMY_6_LIFE;
        this->velocity = ENEMY_6_VELOCITY;
    }
    else if(name.compare("Enemy6") == 0)
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
        this->originalLife=ENEMY_7_LIFE;
        this->velocity = ENEMY_7_VELOCITY;
    }
    else if(name.compare("Enemy7") == 0)
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
        this->originalLife=ENEMY_8_LIFE;
        this->velocity = ENEMY_8_VELOCITY;
    }
    else if(name.compare("Enemy8") == 0)
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
        this->originalLife=ENEMY_9_LIFE;
        this->velocity = ENEMY_9_VELOCITY;
    }
    else if(name.compare("Enemy9") == 0)
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
        this->originalLife=ENEMY_10_LIFE;
        this->velocity = ENEMY_10_VELOCITY;
    }
}
