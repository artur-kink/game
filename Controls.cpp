#include "Controls.hpp"

Controls* Controls::controls = NULL;

Controls::Controls(){
    
}

Controls* Controls::instance(){
    if(controls == NULL)
        controls = new Controls();
    return controls;
}

void Controls::update(){
    int x, y;
    SDL_GetMouseState(&x, &y);
    mouseX = x;
    mouseY = y;
}
