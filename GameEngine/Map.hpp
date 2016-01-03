#ifndef _MAP_HPP
#define _MAP_HPP

#include <cstdint>
#include <stdlib.h>

#include "Tile.hpp"

class Map{
protected:

public:
    uint32_t width;
    uint32_t height;
    Tile** map;

    Map(uint32_t w, uint32_t h);
};

#endif
