#include "Tile.hpp"

bool Tile::isBlocked(){
    return attributes & Blocked;
}

bool Tile::setBlocked(bool val){
    attributes |= Blocked;
}
