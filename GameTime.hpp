#ifndef _GAMETIME_HPP
#define _GAMETIME_HPP

#include "GET_Time.hpp"

#include "SDL2/SDL_timer.h"

class GameTime:public Time{
private:
    static GameTime* time;
    GameTime();

    uint64_t frameTime;
public:

    static GameTime* instance();
    void updateFrameTime();
    
    uint64_t getSystemTime();
    virtual uint64_t getTime();
};

#endif
