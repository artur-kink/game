#ifndef _PLAYERENTITY_HPP
#define _PLAYERENTITY_HPP

#include "Entity.hpp"
#include "../GameEngine.hpp"

class PlayerEntity:public Entity{
public:
    enum MoveDirection{
        None = 0,
        Up = 1,
        Down = 2,
        Left = 4,
        Right = 8
    };

    uint8_t direction;

    uint32_t width;
    uint32_t height;

    PlayerEntity();
    virtual void update();

    void setMoveDirection(uint8_t dir);
};

#endif
