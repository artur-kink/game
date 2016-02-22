#ifndef _PLAYERENTITY_HPP
#define _PLAYERENTITY_HPP

#include "Entity.hpp"

class PlayerEntity:public Entity{
public:
    PlayerEntity();

    virtual void turn(){};
};

#endif
