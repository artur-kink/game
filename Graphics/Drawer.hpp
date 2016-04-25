#ifndef _DRAWER_HPP
#define _DRAWER_HPP

#include <iostream>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

#include "../GameEngine/Tile.hpp"

#include "glog/logging.h"

class Drawer{
private:

    static Drawer* drawer;
    SDL_Renderer* sdlRenderer;

    SDL_Texture* tilesTexture;
    SDL_Texture* spritesTexture;
    TTF_Font* font;

    int32_t offsetX, offsetY;

    Drawer();
public:
    static Drawer* instance();

    uint32_t init(SDL_Renderer* renderer);

    void setOffset(int32_t x, int32_t y);
    void drawSprite(uint32_t sprite, int32_t x, int32_t y);
    void drawTile(uint32_t tile, int32_t x, int32_t y);
    void drawText(const char* text, int32_t x, int32_t y);
    
    void cleanup();
};

#endif
