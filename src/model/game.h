#include <vector>
#include "entities/entity.h"
#include "../controller/process.h"

class Game{
        enum state{menu, playing};
        std::vector<Entity> enemies;
        Entity player;
        // class Field{
        //     int size =4000;
        //     public:
        //         Player *player;
        // };

    public:
        //Probably stuff like the stage and the array of  entities
        //score too as well as lives and other integers
        //And game states too.
        Game();
        ~Game();
        void update_game(InputHandler *input, float delta);
};