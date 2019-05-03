#include "tower.h"
#include <QPixmap>
#include <config.h>

Tower::Tower(string name, bool isInstanlized)
//只有通过鼠标事件才能生成实例化的防御塔（尚不确定的想法）
{
    if(!isInstanlized){
        if(name.compare("attacker") == 0){
            this->damage = ATTACKER_DAMAGE;
            this->icon = new QPixmap;
            icon->load(":/pictures/tower_test.png");
            width = ATTACKER_WIDTH;
            height = ATTACKER_HEIGHT;

            isActivated = false;
            isChosen = false;


        }else{

        }
    }else{

    }
}
Tower::~Tower(){
    int i;
    for(i = 0; i < enemies.size(); i++){
        delete enemies[i];
    }
}
