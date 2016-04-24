#ifndef _ENTITY_HPP
#define _ENTITY_HPP

#include <cstdint>
#include "glog/logging.h"

class Entity{
protected:

public:
    uint16_t entityId;
    int32_t x, y;

    Entity();
    Entity(int32_t sX, int32_t sY);
    
    virtual void update();
};

#endif
