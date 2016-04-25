#ifndef _TILE_HPP
#define _TILE_HPP

#include <cstdint>

#define TILE_WIDTH 32
#define TILE_HEIGHT 32

#define NUM_LAYERS 3

class Tile{
private:
    uint32_t attributes;

public:

    enum TileAttributes{
        Blocked = 0x01,
        Arable = 0x02,
        Plowed = 0x04,
        Water = 0x08
    };

    uint16_t layers[NUM_LAYERS];

    void setAttribute(uint32_t attr, bool val = true);

    bool isBlocked();
    void setBlocked(bool val = true);

    bool isArable();
    void setArable(bool val = true);

    bool isPlowed();
    void setPlowed(bool val = true);

    bool isWater();
    void setWater(bool val = true);
};

#endif
