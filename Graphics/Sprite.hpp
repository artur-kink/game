#ifndef _SPRITE_HPP
#define _SPRITE_HPP

#include "SDL2/SDL.h"
#include <vector>

class SpriteBase{
public:
    const char* name;
};

class Sprite : public SpriteBase{
public:
    SDL_Rect rect;
    SDL_Texture *texture;
};

class SpriteSet : public SpriteBase{
public:
    std::vector<SpriteBase*> sprites;
};

#endif
