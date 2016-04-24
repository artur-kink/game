#ifndef _TILE_HPP
#define _TILE_HPP

#include <cstdint>

#define TILE_WIDTH 32
#define TILE_HEIGHT 32

#define NUM_LAYERS 3

class Tile{
protected:

public:

    enum TileAttributes{
        Blocked = 1
    };

    uint16_t layers[NUM_LAYERS];
    uint8_t attributes;


    bool isBlocked();
    void setBlocked(bool val = true);

};

#endif
