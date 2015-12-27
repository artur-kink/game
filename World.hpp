#ifndef _WORLD_HPP
#define _WORLD_HPP

#include "Map.hpp"

#include <vector>

/**
 * A world is a collection of Maps creating the larger world.
 */
class World{
protected:

    Map*** maps;
public:
    World();

    Tile& getTile(int32_t x, int32_t y);
    
};

#endif
