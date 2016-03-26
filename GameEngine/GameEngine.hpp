#ifndef _GAMEENGINE_HPP
#define _GAMEENGINE_HPP

#include "World.hpp"
#include "Entities/Entities.hpp"
#include "Action.hpp"

#include <vector>

#include "glog/logging.h"

class GameEngine{
protected:

    std::vector<Action*> actionQueue;

    static GameEngine* gameEngine;

    Entity* player;
public:
    std::vector<Entity*> entities;

    World world;

    GameEngine();

    static GameEngine* instance();

    void update();
    void doTurn();
    void addEntity(Entity* entity);


    void addAction(Action* action);

    Entity* getPlayer();
    void setPlayer(Entity* p);
};

#endif
