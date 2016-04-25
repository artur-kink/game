#ifndef _PLAYERENTITY_HPP
#define _PLAYERENTITY_HPP

#include "Entity.hpp"
#include "../GameEngine.hpp"
#include "../../GameTime.hpp"
#include "../../Graphics/Drawer.hpp"

class PlayerEntity:public Entity{
public:
    enum MoveDirection{
        None = 0,
        Up = 1,
        Down = 2,
        Left = 4,
        Right = 8
    };

    Timer animationTimer;
    uint8_t animationFrame;

    uint8_t direction;
    uint8_t movingDirection;

    uint32_t width;
    uint32_t height;

    PlayerEntity();
    virtual void update();
    virtual void draw();

    void setMoveDirection(uint8_t dir);
    void performAction();
};

#endif
