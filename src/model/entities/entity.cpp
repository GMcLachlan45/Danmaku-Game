#include "entity.h"

Entity::Entity(int id, int x, int y, float theta){
    std::cout<< x<< " uh " << y << std::endl;

    entityId = id;
    posX = x;
    posY = y;
    angle = theta;

    std::cout<< posX<< " hmmmm " << posY << std::endl;
};

Entity::~Entity(){};


void Entity::move(){};
void Entity::move(InputHandler * input, float delta){
    int deltaX = 0;
    int deltaY = 0;
    deltaX += 400 * ((int) input->right - (int) input->left);
    deltaY += 400 * ((int) input->up - (int) input->down);
    if(input->shift){
        deltaX/=2;
        deltaY/=2;
    }
    posX += deltaX;
    posY += deltaY;

};

int Entity::getX(){return posX;};
int Entity::getY(){return posY;};