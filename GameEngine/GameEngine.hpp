#ifndef _GAMEENGINE_HPP
#define _GAMEENGINE_HPP

#include "World.hpp"
#include "Entities/Entities.hpp"

#include <vector>

#include "glog/logging.h"

class GameEngine{
protected:

    static GameEngine* gameEngine;

    Entity* player;
public:
    std::vector<Entity*> entities;

    World world;

    GameEngine();

    static GameEngine* instance();

    void update();
    void addEntity(Entity* entity);


    Entity* getPlayer();
    void setPlayer(Entity* p);
};

#endif
