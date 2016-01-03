#ifndef _CONTROLS_HPP
#define _CONTROLS_HPP

#include "SDL2/SDL.h"

#include "GET_Time.hpp"
#include "GameTime.hpp"

#include <iostream>
#include <cstdint>

class Controls{
public:
    enum MOUSE_BUTTON{
        MOUSE_LEFT = 0,
        MOUSE_RIGHT = 1,
        MOUSE_NUMBUTTONS = 2
    };

    enum BUTTON_STATE{
        BUTTON_UP = 0x00,
        BUTTON_DOWN = 0x01,
        BUTTON_RELEASED = 0x02, ///< BUTTON_UP bit is 0
        BUTTON_PRESSED = 0x03, ///< BUTTON_DOWN bit is 1
        BUTTON_DOUBLEPRESSED = 0x07 ///< BUTTON_DOWN and BUTTON_PRESSED bits are 1
    };

private:
    static Controls* controls;

    /** Current state of mouse button */
    uint8_t mouseButtonState[MOUSE_NUMBUTTONS];
    
    /** Time when mouse was last pressed */
    Timer* mousePressedTime[MOUSE_NUMBUTTONS];

    Controls();
    void updateMouseButtonState(MOUSE_BUTTON button, bool isPressed);

    uint32_t doublePressTime = 300;

public:
    static Controls* instance();

    int32_t mouseX;
    int32_t mouseY;


    void update();
    uint8_t getMouseButtonState(MOUSE_BUTTON button);
    bool isMouseButtonDown(MOUSE_BUTTON button);
    bool wasMouseButtonClicked(MOUSE_BUTTON button);
    bool wasMouseButtonReleased(MOUSE_BUTTON button);
    bool wasMouseButtonDoubleClicked(MOUSE_BUTTON button);

};

#endif
