#ifndef _PLAYERENTITY_HPP
#define _PLAYERENTITY_HPP

#include "Entity.hpp"

class PlayerEntity:public Entity{
public:
    PlayerEntity();

    /** Player turns are handled manually in the engine. */
    virtual void turn(){};
};

#endif
