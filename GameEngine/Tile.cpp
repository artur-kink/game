#include "Tile.hpp"

bool Tile::isBlocked(){
    return attributes & Blocked;
}

void Tile::setBlocked(bool val){
    attributes |= Blocked;
}
