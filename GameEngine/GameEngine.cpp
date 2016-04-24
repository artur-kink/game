#include "GameEngine.hpp"

GameEngine* GameEngine::gameEngine = NULL;

GameEngine::GameEngine(){
    gameEngine = this;
}

GameEngine* GameEngine::instance(){
    return gameEngine;
}

void GameEngine::update(){
    for(uint32_t i = 0; i < entities.size(); i++){
        entities.at(i)->update();
    }
}

void GameEngine::addEntity(Entity* entity){
    LOG(INFO) << "Added entity\n";
    entities.push_back(entity);
    entity->entityId = entities.size()-1;
}

Entity* GameEngine::getPlayer(){
    return player;
}

void GameEngine::setPlayer(Entity* p){
    player = p;
}
