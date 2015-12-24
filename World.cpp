#include "World.hpp"

World::World(){

    maps = new Map**[100];
    for(uint32_t i = 0; i < 100; i++){
        maps[i] = new Map*[100];
        for(uint32_t j = 0; j < 100; j++){
            maps[i][j] = 0;
        }
    }

}

int32_t World::getTile(int32_t x, int32_t y){
    return 1;
}
