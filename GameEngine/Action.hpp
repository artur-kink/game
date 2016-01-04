#ifndef _ACTION_HPP
#define _ACTION_HPP

#include <cstdint>

enum ActionIds{
    ACTION_MOVE = 1,
    ACTION_NUM = 2
};

class Action{
public:
    uint16_t actionId;
};

class MoveAction:public Action{
public:
    uint16_t entity;
    int32_t x, y;    
    
    MoveAction(uint16_t e, int32_t x, int32_t y);

};

#endif
