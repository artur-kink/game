#include "GameEngine.hpp"

GameEngine* GameEngine::gameEngine = NULL;

GameEngine::GameEngine(){
    gameEngine = this;
}

GameEngine* GameEngine::instance(){
    return gameEngine;
}

void GameEngine::update(){

    if(actionQueue.size()){
        for(uint32_t i = 0; i < actionQueue.size(); i++){
            Action* action = actionQueue.at(i);
            if(action->actionId == ACTION_MOVE){
                MoveAction* moveAction = (MoveAction*)action;
                Entity* entity = entities.at(moveAction->entity);
                entity->x = moveAction->x;
                entity->y = moveAction->y;
            }
            delete action;
        }
        actionQueue.clear();
    }

    for(uint32_t i = 0; i < entities.size(); i++){
        entities.at(i)->update();
    }
}

void GameEngine::addEntity(Entity* entity){
    entities.push_back(entity);
    entity->entityId = entities.size()-1;
}


void GameEngine::addAction(Action* action){
    actionQueue.push_back(action);
}
