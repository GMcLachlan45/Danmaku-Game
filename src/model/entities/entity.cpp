#include "entity.h"

Entity::Entity(int id, int x, int y, float theta){
    entityId = id;
    posX = x;
    posY = y;
    angle = theta;
};

Entity::Entity(int id, int x, int y){
    Entity(id, x, y, 0);
};

Entity::~Entity(){};