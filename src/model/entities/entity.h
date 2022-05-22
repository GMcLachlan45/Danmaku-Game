#include "../../controller/InputHandler.h"
class Entity{
    int entityId;
    int posX, posY;
    float angle;
    public:
        Entity(int id, int x, int y, float theta);
        ~Entity();

        void move();
        void move(InputHandler * input, float delta);

        // getters
        int getX();
        int getY();
};