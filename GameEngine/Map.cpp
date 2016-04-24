#include "Map.hpp"

Map::Map(uint32_t w, uint32_t h){
    width = w;
    height = h;
    map = new Tile*[h];
    srand(0);
    for(uint32_t i = 0; i < h; i++){
        map[i] = new Tile[w];
        for(uint32_t j = 0; j < w; j++){
            if (rand() % 4 == 0){
                map[i][j].layers[0] = 210;
                map[i][j].setBlocked(true);
            }else
                map[i][j].layers[0] = 240;

            
        }
    }
}
