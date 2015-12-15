#ifndef _DRAWER_HPP
#define _DRAWER_HPP

#include <iostream>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

class Drawer{
private:

    static Drawer* drawer;
    SDL_Renderer* sdlRenderer;
    TTF_Font* font;

    Drawer();
public:
    static Drawer* instance();

    uint32_t init(SDL_Renderer* renderer);

    void drawText(const char* text, int32_t x, int32_t y);
    
    void cleanup();
};

#endif
