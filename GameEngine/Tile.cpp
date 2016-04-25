#include "Tile.hpp"


void Tile::setAttribute(uint32_t attr, bool val){
    if(val)
        attributes |= attr;
    else
        attributes &= !(attr);
}

bool Tile::isBlocked(){
    return attributes & Blocked;
}

void Tile::setBlocked(bool val){
    setAttribute(Blocked, val);
}

bool Tile::isArable(){
    return attributes & Arable;
}

void Tile::setArable(bool val){
    setAttribute(Arable, val);
}

bool Tile::isPlowed(){
    return attributes & Plowed;
}

void Tile::setPlowed(bool val){
    layers[0] = 126;
    setAttribute(Plowed, val);
}

bool Tile::isWater(){
    return attributes & Water;
}

void Tile::setWater(bool val){
    setAttribute(Water, val);
}
