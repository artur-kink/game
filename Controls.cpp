#include "Controls.hpp"

Controls* Controls::controls = NULL;

Controls::Controls(){
    for(uint32_t i = 0; i < MOUSE_NUMBUTTONS; i++){
        mouseButtonState[i] = BUTTON_UP;
        mousePressedTime[i] = new Timer(*GameTime::instance());
    }

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
            {
            if(mousePressedTime[button]->getElapsedTime() < doublePressTime){
                mouseButtonState[button] = BUTTON_DOUBLEPRESSED;
            }else{
                mouseButtonState[button] = BUTTON_PRESSED;
            }
            mousePressedTime[button]->reset();
            }
        else
            mouseButtonState[button] = BUTTON_DOWN;
    }else{
        if(isMouseButtonDown(button))
            mouseButtonState[button] = BUTTON_RELEASED;
        else
            mouseButtonState[button] = BUTTON_UP;
    }
}

uint8_t Controls::getMouseButtonState(MOUSE_BUTTON button){
    return mouseButtonState[button];
}

bool Controls::isMouseButtonDown(MOUSE_BUTTON button){
    return mouseButtonState[button] & BUTTON_DOWN;
}

bool Controls::wasMouseButtonClicked(MOUSE_BUTTON button){
    return mouseButtonState[button] & BUTTON_PRESSED;
}

bool Controls::wasMouseButtonReleased(MOUSE_BUTTON button){
    return mouseButtonState[button] == BUTTON_RELEASED;
}

bool Controls::wasMouseButtonDoubleClicked(MOUSE_BUTTON button){
    return mouseButtonState[button] == BUTTON_DOUBLEPRESSED;
}
