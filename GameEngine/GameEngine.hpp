#ifndef _GAMEENGINE_HPP
#define _GAMEENGINE_HPP

#include "World.hpp"
#include "Entity.hpp"
#include "Action.hpp"

#include <vector>

#include "glog/logging.h"

class GameEngine{
protected:
    std::vector<Entity*> entities;

    std::vector<Action*> actionQueue;

    static GameEngine* gameEngine;
public:
    World world;

    GameEngine();

    GameEngine* instance();

    void update();
    void addEntity(Entity* entity);


    void addAction(Action* action);
};

#endif
