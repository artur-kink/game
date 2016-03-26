#ifndef _DUMMYENEMY_HPP
#define _DUMMYENEMY_HPP

#include "Entity.hpp"

#include "../GameEngine.hpp"

class DummyEnemy:public Entity{

public:
    DummyEnemy();
    
    virtual void turn();
};

#endif
