#ifndef GAME_ENTITY
#define GAME_ENTITY

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "./../../controller/InputHandler.h"


class GameEntity{//////////////////////TODO CHANGES
    unsigned int entityId;
    unsigned int spriteId;

    int posX, posY;
    float width, height; // gives the scaling 
    float angle; ///angle expressed in rads

    public:
        GameEntity(int id, int x, int y, float theta);
        ~GameEntity();

        void move();
        void move(bool * input , float delta);

        // getters

        int getX();
        int getY();
        glm::mat4 getTransformationMatrix();
};

#endif