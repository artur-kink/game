#include "Game.hpp"

#include <iostream>

int main(int argc, char** argv){
    Game game;
    if(game.init() == 0)
        game.start();
    std::cout << "Terminating main...\n";
}
