#include "gameobject.h"
#include <math.h>
GameObject::GameObject(): icon()
{
    icon = new QPixmap;
    icon->load(":/pictures/tower_test.png");

    width = 100;
    height = 100;
}
GameObject::~GameObject(){
    //delete icon;
}
void GameObject::setGameObject(float x, float y){

    position.setX(x);
    position.setY(y);
}
void GameObject::show(QPainter* p){
    //对象的position是中心坐标,要转换
    p->drawPixmap(this->position.x()-width/2, this->position.y()-height/2, width, height, *icon);
}
bool GameObject::isMouseEventInIt(QMouseEvent *e){
    if(abs(e->x()-position.x()) < width/2 && abs(e->y()-position.y()) < height/2){
        return true;
    }else{return false;}
}
bool GameObject::isMyPointInIt(MyPoint p){
    if(abs(p.x()-position.x()) < width/2 && abs(p.y()-position.y()) < height/2){
        return true;
    }else{return false;}
}
