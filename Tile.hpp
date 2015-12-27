#ifndef _TILE_HPP
#define _TILE_HPP

#include <cstdint>

#define NUM_LAYERS 3

class Tile{
protected:

public:
    uint16_t layers[NUM_LAYERS];
    bool blocked;

};

#endif
