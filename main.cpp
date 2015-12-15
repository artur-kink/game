#include "Game.hpp"

#include <iostream>
#include <signal.h>

Game game;

static void interrupt_handler(int signal){
    game.stop();    
}

int main(int argc, char** argv){

    if(signal(SIGINT, interrupt_handler) == SIG_ERR){
        return 1;
    }

    if(game.init() == 0)
        game.start();
    std::cout << "Terminating main...\n";
}
