#include "scene.h"
#include <QPixmap>
#include "config.h"
#include <QDebug>
#include <math.h>
#include "tool.h"
#include <QtGlobal>
#include <QLabel>
#include <QWidget>
#include <QProgressBar>
#include <QApplication>
#include <QTimer>
#include "blood.h"
#include "playerinfo.h"


Scene::Scene()
{
    background = new QPixmap;
    background->load(":/pictures/background/main.png");
    mapname=":/pictures/background/main.png";
    player = new Player;
    player_life = new PlayerInfo(player,"life");
    player_money = new PlayerInfo(player,"money");
    //player应当放在setscene函数里面，但是如果放进去程序无法运行

}

Scene::~Scene(){
}

void Scene::setScene(QString map_name){
    QApplication::setQuitOnLastWindowClosed(false);
    secondCounter = 0.0;
    manualMod = false;
    mapname=map_name;
    delete background;
    background=new QPixmap;
    background->load(map_name);
    Tower* displayedTower = new Tower("attacker", false);
    displayedTower->setGameObject(ATTACKER_WIDTH/2+LEFT, MAINWINDOW_HEIGHT-DOWN-ATTACKER_HEIGHT/2);
    displayMenuOfTowers.push_back(displayedTower);

    displayedTower = new Tower("attacker1", false);
    displayedTower->setGameObject(ATTACKER_WIDTH+ATTACKER1_WIDTH/2+LEFT, MAINWINDOW_HEIGHT-DOWN-ATTACKER1_HEIGHT/2);
    displayMenuOfTowers.push_back(displayedTower);

    displayedTower = new Tower("attacker2", false);
    displayedTower->setGameObject(ATTACKER_WIDTH+ATTACKER1_WIDTH+ATTACKER2_WIDTH/2+LEFT, MAINWINDOW_HEIGHT-DOWN-ATTACKER2_HEIGHT/2);
    displayMenuOfTowers.push_back(displayedTower);

    displayedTower = new Tower("attacker3", false);
    displayedTower->setGameObject(ATTACKER_WIDTH+ATTACKER1_WIDTH+ATTACKER2_WIDTH+ATTACKER3_WIDTH/2+LEFT, MAINWINDOW_HEIGHT-DOWN-ATTACKER3_HEIGHT/2);
    displayMenuOfTowers.push_back(displayedTower);

    displayedTower = new Tower("attacker4", false);
    displayedTower->setGameObject(ATTACKER_WIDTH+ATTACKER1_WIDTH+ATTACKER2_WIDTH+ATTACKER3_WIDTH+ATTACKER4_WIDTH/2+LEFT, MAINWINDOW_HEIGHT-DOWN-ATTACKER4_HEIGHT/2);
    displayMenuOfTowers.push_back(displayedTower);

}

void Scene::clearScene()
{
    savedscene=0;
    for(int i = 0; i < bullets.size(); i++){
        delete bullets[i];
        bullets.erase(bullets.begin() + i);
        i--;
    }
    for(int i = 0; i < enemies.size(); i++){
        delete enemies[i];
        enemies.erase(enemies.begin() + i);
        i--;
    }
    for(int i = 0; i < towers.size(); i++){
        delete towers[i];
        towers.erase(towers.begin() + i);
        i--;
    }
    for(int i = 0; i < displayMenuOfTowers.size(); i++){
        delete displayMenuOfTowers[i];
        displayMenuOfTowers.erase(displayMenuOfTowers.begin() + i);
        i--;
    }
    for(int i = 0; i < bloods.size(); i++){
        delete bloods[i];
        bloods.erase(bloods.begin() + i);
        i--;
    }
 //   delete player;如果加上这句话没办法第二次quit，应该和上面是同一问题
    delete background;
    background=new QPixmap;
    background->load(":/pictures/background/main.png");
    mapname=":/pictures/background/main.png";
}

void Scene::saveScene()
{
    delete background;
    background=new QPixmap;
    background->load(":/pictures/background/main.png");
    mapname1=mapname;
    mapname=":/pictures/background/main.png";
}

void Scene::returntoScene()
{
    delete background;
    background=new QPixmap;
    background->load(mapname1);
    mapname=mapname1;
}

void Scene::show(QPainter* p){

    //qDebug() << "bullets remain: " << bullets.size()<<endl;

    int i;
    secondCounter += 1.0/FPS;
    //画背景
    //qDebug()<<"p->drawPixmap"<<endl;
    p->drawPixmap(0,0,MAINWINDOW_WIDTH, MAINWINDOW_HEIGHT,*background);

    if(mapname!=":/pictures/background/main.png")
    {
        player_life->show(p);
        player_money->show(p);
    }

    //仇恨管理一定要在开火管理之前，否则会导致bug
    //qDebug()<<"processor_hatredControll()"<<endl;
    processor_hatredControll();

    //处理塔的开火状态
    //qDebug()<<"towers[i]->handleCoolDown()"<<endl;
    for(i = 0; i < towers.size(); i++){
        towers[i]->handleCoolDown();
    }
    //qDebug()<<"processor_Tower_rotate()"<<endl;
    processor_Tower_rotate();
    //必须要先处理冷却，再处理旋转，因为冷却函数把所有已冷却的塔设置成可开火
    //塔旋转处理器把未旋转到位、以冷却的塔设置成不可开火

    //qDebug()<<"processor_Move()"<<endl;
    processor_Move();
    //qDebug()<<"creator_bullets()"<<endl;
    creator_bullets();
    //qDebug()<<"processor_damageConfirm()"<<endl;
    processor_damageConfirm();
    //qDebug()<<"enemy_generator()"<<endl;
    if(((secondCounter - int(secondCounter/frequency)*frequency) >= 0.0) && ((secondCounter - int(secondCounter/frequency)*frequency) < 1.0/FPS)){
         enemy_generator();
    }
    //qDebug()<<"object_delete()"<<endl;
    object_delete();

    if(mapname!=":/pictures/background/main.png")
    {
        //qDebug()<<"towers[i]->show(p)"<<endl;
        for(i = 0; i < towers.size(); i++){
            towers[i]->show(p);
        }

        //qDebug()<<"displayMenuOfTowers[i]->show(p)"<<endl;
        for(i = 0; i < displayMenuOfTowers.size(); i++){
            displayMenuOfTowers[i]->show(p);
        }

        //qDebug()<<"dragedTower[i]->show(p)"<<endl;
        for(i = 0; i < dragedTower.size(); i++){
            dragedTower[i]->show(p);
        }

        //qDebug()<<"enemies[i]->show(p)"<<endl;
        for(i = 0; i < enemies.size(); i++){
            enemies[i]->show(p);
        }

        //qDebug()<<"bloods[i]->show(p)"<<endl;
        for(i=0;i<bloods.size();i++)
        {
            bloods[i]->show(p);
        }

        //qDebug()<<"bullets[i]->show(p)"<<endl;
        for(i = 0; i < bullets.size(); i++){
            bullets[i]->show(p);
        }
    }
}


void Scene::processor_mousePressEvent(QMouseEvent *e){
    int i;
    if(e->button() == Qt::LeftButton && manualMod == false){
        for(i = 0; i < towers.size(); i++){
            if(towers[i]->isMouseEventInIt(e)){
                towers[i]->setChosen(true);
                towers[i]->setRotateReady(true);
                this->manualMod = true;

            }
        }
        for(i = 0; i < displayMenuOfTowers.size(); i++){
            if(displayMenuOfTowers[i]->isMouseEventInIt(e)){
                int j;
                for(j = 0; j <dragedTower.size(); j++){
                    delete dragedTower[j];
                }
                dragedTower.clear();
                Tower* tmp = new Tower(displayMenuOfTowers[i]->getType(), false);
                tmp->setGameObject(e->x(), e->y());
                this->dragedTower.push_back(tmp);
                return;
            }
        }
        int j = 0;
        for(j = 0; j < dragedTower.size(); j++){
            dragedTower[j]->setActivated(true);
            if(player->getMoney()<dragedTower[j]->getDamage()){
                //金币不足
                QMessageBox::warning(NULL, "warning", "No Money!");
                break;
            }
            else {
                towers.push_back(dragedTower[j]);

                player->setMoney(player->getMoney()-dragedTower[j]->getPrice());
                //玩家金币减少
            }

        }
        dragedTower.clear();
        int k=0;
        for(k=0;k<enemies.size();k++)
        {
            if(enemies[k]->isMouseEventInIt(e))
            {
                enemies[k]->isChosen=1;
            }
        }
    }else if(e->button() == Qt::LeftButton && manualMod == true){
        this->mouseLeftPressed = true;
    }else if(e->button() == Qt::RightButton){
        for(i = 0; i <dragedTower.size(); i++){
            Tower* tmp = dragedTower[i];
            dragedTower.remove(i,1);
            i--;
            delete tmp;
        }
        for(i = 0; i < towers.size(); i++){
            towers[i]->setChosen(false);
        }
        manualMod = false;

    }
}
void Scene::processor_mouseReleseEvent(QMouseEvent *e){
    if(e->button() == Qt::LeftButton){
        this->mouseLeftPressed = false;
    }
}
void Scene::processor_mouseMoveEvent(QMouseEvent *e){
    this->mouseMoveEventPoint.setByMouseEvent(e);
    int i;
    for(i = 0; i < dragedTower.size(); i++){
        dragedTower[i]->setGameObject(e->x(), e->y());
    }
}
void Scene::processor_keyPressEvent(QKeyEvent *e){
    if(e->key()==Qt::Key_0){
        delete towers[0];
        towers.erase(towers.begin());
    }
}


float Scene::distance(MyPoint a, MyPoint b){
    float x = pow(a.x()-b.x(),2);
    float y = pow(a.y()-b.y(),2);
    float ans = pow(x+y,0.5);
    return ans;
}


void Scene::processor_hatredControll(){
    int i,j;
    for(i = 0; i < towers.size(); i++){
        for(j = 0; j < enemies.size(); j++){
            float dis = distance(towers[i]->getPosition(), enemies[j]->getPosition());
            int index = towers[i]->hatred.indexOf(enemies[j]);
            if(dis<= towers[i]->get_discovery_range()
                    && index==-1 && enemies[j]->getLife() > 0){
                towers[i]->hatred.push_back(enemies[j]);
                //qDebug()<<"add to hatred\n";
            }
            if(index != -1 &&(dis > towers[i]->get_discovery_range() || enemies[j]->getLife() <= 0)){
                towers[i]->hatred.erase(towers[i]->hatred.begin()+index);
            }
        }
    }
}
void Scene::creator_bullets()
{
    int i;
    for(i = 0; i < towers.size(); i++){
        //qDebug()<<"hatred.isEmpty"<<towers[i]->hatred.isEmpty()<<endl;
        if(!towers[i]->hatred.isEmpty()
                && towers[i]->isFireReady()
                && towers[i]->getRotateReady()
                && !towers[i]->getIsChosen()){
            //有仇恨目标、冷却完成、旋转完成，进行开火，同时重置开火属性。
            Enemy* target = towers[i]->hatred[0];
            towers[i]->fireCool();
            Bullet* b = new Bullet(towers[i], target);
            bullets.push_back(b);
            //qDebug()<<"bullet created\n";
        }else if(towers[i]->getIsChosen()
                 && towers[i]->isFireReady()
                 && towers[i]->getRotateReady()
                 && mouseLeftPressed
                 && manualMod){
            towers[i]->fireCool();
            //qDebug()<<"angel"<<towers[i]->getAngle();
            Bullet* b = new Bullet(towers[i], Tool::angel_to_vector(towers[i]->getAngle()));
            bullets.push_back(b);
        }
    }
}

void Scene::processor_Move(){
    int i;
    for(i = 0; i < enemies.size(); i++){
        float xPre = enemies[i]->getPosition().x();
        float yPre = enemies[i]->getPosition().y();
        float x = xPre + enemies[i]->get_velocity()*enemies[i]->get_direction_x()/FPS;
        float y = yPre + enemies[i]->get_velocity()*enemies[i]->get_direction_y()/FPS;
        enemies[i]->setGameObject(x, y);
    }
    for(i = 0; i < bullets.size(); i++){
        float xPre = bullets[i]->getPosition().x();
        float yPre = bullets[i]->getPosition().y();
        float x = xPre + bullets[i]->get_velocity()*bullets[i]->get_direction_x()/FPS;
        float y = yPre + bullets[i]->get_velocity()*bullets[i]->get_direction_y()/FPS;
        bullets[i]->setGameObject(x, y);
    }

}

void Scene::processor_damageConfirm(){
    int i, j;
    for(i = 0; i < enemies.size(); i++){
        for(j = 0; j < bullets.size(); j++){
            if(enemies[i]->isMyPointInIt(bullets[j]->getPosition())){
                enemies[i]->setDamaged(true);
                enemies[i]->setLife(enemies[i]->getLife() - bullets[j]->getDamage());
                if(enemies[i]->get_velocity()>0)
                    enemies[i]->setVelocity(enemies[i]->get_velocity()-bullets[j]->getSlower());
                else enemies[i]->setVelocity(0);
                delete bullets[j];
                bullets.erase(bullets.begin()+j);
                j--;
            }
        }

    }
}
void Scene::processor_Tower_rotate(){
    int i;
    for(i = 0; i < towers.size(); i++){
        MyPoint vec_aim;
        float angle_aim;
        MyPoint aim;
        if(!towers[i]->hatred.isEmpty() && !towers[i]->getIsChosen()){
            aim = (towers[i]->hatred[0]->getPosition());
            MyPoint pole(towers[i]->getPosition());
            vec_aim.setX(aim.x()-pole.x());
            vec_aim.setY(aim.y()-pole.y());
            angle_aim = Tool::vector_to_angle(vec_aim);
        }else if(towers[i]->getIsChosen() && manualMod){
            aim.setX(this->mouseMoveEventPoint.x());
            aim.setY(this->mouseMoveEventPoint.y());
        }
        MyPoint pole(towers[i]->getPosition());
        vec_aim.setX(aim.x()-pole.x());
        vec_aim.setY(aim.y()-pole.y());
        angle_aim = Tool::vector_to_angle(vec_aim);
        if((!towers[i]->hatred.isEmpty() && !towers[i]->getIsChosen())
                || towers[i]->getIsChosen()){
            if(abs(angle_aim - towers[i]->getAngle()) > towers[i]->get_velocity_rotaion()/FPS
                    &&abs(angle_aim - towers[i]->getAngle()) - 360 < -towers[i]->get_velocity_rotaion()/FPS){
                //缓慢旋转中
                if(abs(angle_aim - towers[i]->getAngle()) <= 180){
                        towers[i]->setAngle(towers[i]->getAngle()
                                    + Tool::sign(angle_aim - towers[i]->getAngle())//这是一个符号函数，算方向的
                                    * towers[i]->get_velocity_rotaion()/FPS);
                        if(!towers[i]->getIsChosen()){
                            towers[i]->setRotateReady(false);
                        }
                }else{
                        towers[i]->setAngle(towers[i]->getAngle()
                                    - Tool::sign(angle_aim - towers[i]->getAngle())//这是一个符号函数，算方向的
                                    * towers[i]->get_velocity_rotaion()/FPS);
                        if(!towers[i]->getIsChosen()){
                            towers[i]->setRotateReady(false);
                        }

                }

            }else{
                //能转到，爽
                towers[i]->setAngle(angle_aim);
                towers[i]->setRotateReady(true);
            }
        }
    }
}


void Scene::enemy_generator()
{
    int a,b;
    Enemy* tmp;
    Blood *blood;
    b=qrand()%6;//设置一次生成的敌人个数，敌人个数不超过6
    for(int i=0;i<b;i++)
    {
        a=qrand()%10;//设置生成的敌人种类，种类数为10，根据case数控制敌人出现频率
        switch (a)
        {
        case 1:
        case 2:
        case 3:
        case 4:tmp = new Enemy("Enemy");break;
        case 5:
        case 6:
        case 7:
        case 8:tmp = new Enemy("Enemy1");break;
        case 9:
        case 10:
        case 11:tmp = new Enemy("Enemy2");break;
        case 12:
        case 13:
        case 14:tmp = new Enemy("Enemy3");break;
        case 15:
        case 16:
        case 17:tmp = new Enemy("Enemy4");break;
        case 18:
        case 19:tmp = new Enemy("Enemy5");break;
        case 20:
        case 21:tmp = new Enemy("Enemy6");break;
        case 23:
        case 24:tmp = new Enemy("Enemy7");break;
        case 25:
        case 26:tmp = new Enemy("Enemy8");break;
        case 0:tmp = new Enemy("Enemy9");break;
        }

        tmp->setGameObject(LEFT,100+i*100);
        enemies.push_back(tmp);


        blood=new Blood(tmp);
        bloods.push_back(blood);
    }
}

void Scene::object_delete()
{
    for(int i = 0; i < enemies.size(); i++)
    {

        if(((enemies[i])->getLife())<=0)
        {

            for(int j = 0; j < towers.size(); j++){
                int index = towers[j]->hatred.indexOf(enemies[i]);
                if(index != -1){
                    towers[j]->hatred.erase(towers[j]->hatred.begin() + index);
                }
            }
            delete enemies[i];
            delete bloods[i];
            enemies.erase(enemies.begin() + i);
            bloods.erase(bloods.begin()+i);
            i--;
            if(i < 0){continue;}
        }
        if(((enemies[i])->getPosition_x())>=(LEFT+BACK_GROUND_WIDTH-ENEMY_1_WIDTH/2))
        {
            for(int j = 0; j < towers.size(); j++){
                int index = towers[j]->hatred.indexOf(enemies[i]);
                if(index != -1){
                    towers[j]->hatred.erase(towers[j]->hatred.begin() + index);
                }
            }
            if(enemies[i]->type.compare("Enemy") == 0)
                player->setLife(player->getLife()-PLAYER_ENEMY1_LIFE_LOSE);
            else if(enemies[i]->type.compare("Enemy1") == 0)
                player->setLife(player->getLife()-PLAYER_ENEMY2_LIFE_LOSE);
            else if(enemies[i]->type.compare("Enemy2") == 0)
                player->setLife(player->getLife()-PLAYER_ENEMY3_LIFE_LOSE);
            else if(enemies[i]->type.compare("Enemy3") == 0)
                player->setLife(player->getLife()-PLAYER_ENEMY4_LIFE_LOSE);
            else if(enemies[i]->type.compare("Enemy4") == 0)
                player->setLife(player->getLife()-PLAYER_ENEMY5_LIFE_LOSE);
            else if(enemies[i]->type.compare("Enemy5") == 0)
                player->setLife(player->getLife()-PLAYER_ENEMY6_LIFE_LOSE);
            else if(enemies[i]->type.compare("Enemy6") == 0)
                player->setLife(player->getLife()-PLAYER_ENEMY7_LIFE_LOSE);
            else if(enemies[i]->type.compare("Enemy7") == 0)
                player->setLife(player->getLife()-PLAYER_ENEMY8_LIFE_LOSE);
            else if(enemies[i]->type.compare("Enemy8") == 0)
                player->setLife(player->getLife()-PLAYER_ENEMY9_LIFE_LOSE);
            else if(enemies[i]->type.compare("Enemy9") == 0)
                player->setLife(player->getLife()-PLAYER_ENEMY10_LIFE_LOSE);
            //不同enemy到达基地，玩家生命损失不同
            delete enemies[i];
            delete bloods[i];
            enemies.erase(enemies.begin() + i);
            bloods.erase(bloods.begin()+i);
            i--;
            if(i < 0){continue;}
        }
    }

    for(int i = 0; i < bullets.size(); i++){
        if(bullets[i]->getPosition_x() < LEFT
                        || bullets[i]->getPosition_x() > LEFT+BACK_GROUND_WIDTH
                        || bullets[i]->getPosition_y() < LEFT
                        || bullets[i]->getPosition_y() > TOP+BACK_GROUND_HEIGHT)
        {
            //qDebug()<<"删除子弹"<<endl;
            delete bullets[i];
            bullets.erase(bullets.begin() + i);
            i--;
        }
    }

    if(player->getLife()<=0)
    {
       //游戏结束，失败
       lose=1;
    }
}

void Scene::money_add(int a){
    player->setMoney(player->getMoney()+a);
}
