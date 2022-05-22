#include "Game.h"

Game::Game() 
    : enemies(), player(0,0,0,0){};
Game::~Game(){};

void Game::update_game(InputHandler * input, float delta){
    //update player
    player.move(input, delta);
    std::cout<<player.getX() << " " << player.getY() << std::endl;
    //update enemies
};
