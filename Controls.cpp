#include "Controls.hpp"

Controls* Controls::controls = NULL;

Controls::Controls(){
    mouseButtonState[MOUSE_LEFT] = BUTTON_UP; 
    mouseButtonState[MOUSE_RIGHT] = BUTTON_UP; 
}

Controls* Controls::instance(){
    if(controls == NULL)
        controls = new Controls();
    return controls;
}

void Controls::update(){

    SDL_PumpEvents();

    int x, y;
    uint32_t mouseState = SDL_GetMouseState(&x, &y);
    mouseX = x;
    mouseY = y;

    updateMouseButtonState(MOUSE_LEFT, mouseState & SDL_BUTTON(SDL_BUTTON_LEFT));
    updateMouseButtonState(MOUSE_RIGHT, mouseState & SDL_BUTTON(SDL_BUTTON_RIGHT));
}

void Controls::updateMouseButtonState(MOUSE_BUTTON button, bool isPressed){
    if(isPressed){
        if(!isMouseButtonDown(button))
            mouseButtonState[button] = BUTTON_PRESSED;
        else
            mouseButtonState[button] = BUTTON_DOWN;
    }else{
        if(isMouseButtonDown(button))
            mouseButtonState[button] = BUTTON_RELEASED;
        else
            mouseButtonState[button] = BUTTON_UP;
    }
}

bool Controls::isMouseButtonDown(MOUSE_BUTTON button){
    return mouseButtonState[button] & BUTTON_DOWN;
}

bool Controls::wasMouseButtonPressed(MOUSE_BUTTON button){
    return mouseButtonState[button] == BUTTON_PRESSED;
}

bool Controls::wasMouseButtonReleased(MOUSE_BUTTON button){
    return mouseButtonState[button] == BUTTON_RELEASED;
}
