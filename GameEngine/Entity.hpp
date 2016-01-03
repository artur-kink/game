#ifndef _ENTITY_HPP
#define _ENTITY_HPP

#include <cstdint>

class Entity{
protected:

public:
    int32_t x, y;

    Entity();
    Entity(int32_t sX, int32_t sY);
    void update();

};

#endif
