#include "Map.hpp"

Map::Map(uint32_t w, uint32_t h){
    width = w;
    height = h;
    map = new Tile*[h];
    srand(0);
    for(uint32_t i = 0; i < h; i++){
        map[i] = new Tile[w];
        for(uint32_t j = 0; j < w; j++){
            if (rand() % 6 == 0){
                map[i][j].layers[0] = 210;
                map[i][j].setBlocked(true);
                map[i][j].setWater(true);
            }else if(rand()%2 == 0){
                map[i][j].layers[0] = 9;
                map[i][j].setArable(true);
            }else{
                map[i][j].layers[0] = 240;
            }
        }
    }
}

Tile& Map::getTile(uint32_t x, uint32_t y){
    return map[y][x];
}

Tile& Map::getPointTile(uint32_t x, uint32_t y){
    return getTile(x/TILE_SIZE, y/TILE_SIZE);
}
