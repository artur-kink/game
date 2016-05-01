#ifndef _ENTITY_HPP
#define _ENTITY_HPP

#include <cstdint>
#include "glog/logging.h"
#include <glm/vec2.hpp>

class Entity{
protected:

public:
    uint16_t entityId;

    glm::vec2 position;

    Entity();
    Entity(int32_t sX, int32_t sY);
    
    virtual void update() = 0;
    virtual void draw() = 0;
};

#endif
