#include "Entity.h"

GameEntity::GameEntity(int id, int x, int y, float theta){
    entityId = id;
    posX = x;
    posY = y;
    angle = theta;

};

GameEntity::~GameEntity(){};


void GameEntity::move(){};
void GameEntity::move(bool *input, float delta){
    std::cout << input[0]<< " "
    << input[1]<< " "
    << input[2]<< " "
    << input[3]<< " "
    << input[4]<< " " <<std::endl;


    int deltaX = 0;
    int deltaY = 0;
    deltaX += 400 * ((int) input[3] - (int) input[2]);
    deltaY += 400 * ((int) input[0] - (int) input[1]);
    if(input[4]){
        deltaX/=2;
        deltaY/=2;
    }
    posX += deltaX;
    posY += deltaY;


    
};

int GameEntity::getX(){return this->posX;};
int GameEntity::getY(){return this->posY;};

glm::mat4 GameEntity::getTransformationMatrix(){

        std::cout << posX<< " "<< posY <<std::endl;
    glm::mat4 trans = glm::translate(glm::mat4(), glm::vec3(posX, posY, 0));

    // glm::mat4 rot = glm::rotate(angle, glm::vec3(0,0,1));
    // glm::mat4 scale = glm::scale(glm::vec3(1.0f, 1.0f, 1.0f));
    return //scale*rot*
    trans;

};