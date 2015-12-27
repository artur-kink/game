#include "World.hpp"

World::World(){

    maps = new Map**[100];
    for(uint32_t i = 0; i < 100; i++){
        maps[i] = new Map*[100];
        for(uint32_t j = 0; j < 100; j++){
            maps[i][j] = 0;
        }
    }
    maps[0][0] = new Map(12,12);
}

Tile& World::getTile(int32_t x, int32_t y){
    return maps[0][0]->map[y][x];
}
