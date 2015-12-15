#include "Map.hpp"

Map::Map(uint32_t w, uint32_t h){
    width = w;
    height = h;
    map = new int*[h];
    for(uint32_t i = 0; i < h; i++){
        map[i] = new int[w];
        for(uint32_t j = 0; j < w; j++){
            map[i][j] = 1;
        }
    }
}
