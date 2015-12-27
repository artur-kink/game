#ifndef _CONTROLS_HPP
#define _CONTROLS_HPP

#include "SDL2/SDL.h"

#include <cstdint>

class Controls{
private:
    static Controls* controls;

    Controls();
public:
    static Controls* instance();

    int32_t mouseX;
    int32_t mouseY;

    void update();

};

#endif
