#ifndef _TILE_HPP
#define _TILE_HPP

#include <cstdint>

#define TILE_WIDTH 64
#define TILE_HEIGHT 32

#define TILE_WIDTH_HALF TILE_WIDTH/2
#define TILE_HEIGHT_HALF TILE_HEIGHT/2

#define NUM_LAYERS 3

class Tile{
protected:

public:
    uint16_t layers[NUM_LAYERS];
    bool blocked;

};

#endif
