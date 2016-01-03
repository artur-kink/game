#include "GameEngine.hpp"

GameEngine::GameEngine(){

}

void GameEngine::update(){
    for(uint32_t i = 0; i < entities.size(); i++){
        entities.at(i)->update();
    }
}

void GameEngine::addEntity(Entity* entity){
    entities.push_back(entity);
}
