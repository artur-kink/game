#ifndef _GAMEENGINE_HPP
#define _GAMEENGINE_HPP

#include "World.hpp"
#include "Entity.hpp"

#include <vector>

class GameEngine{
protected:
    std::vector<Entity*> entities;

public:
    World world;

    GameEngine();

    void update();
    void addEntity(Entity* entity);
};

#endif
