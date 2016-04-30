#ifndef _SPRITE_HPP
#define _SPRITE_HPP

#include "SDL2/SDL.h"
#include <vector>

class SpriteBase{
public:
    char* name;
};

class Sprite : public SpriteBase{
public:
    SDL_Rect rect;
    SDL_Texture *texture;
};

class SpriteSet : public SpriteBase{
public:
    std::vector<SpriteBase*> sprites;

    SpriteBase* getSprite(const char* name){
        for(uint32_t i = 0; i < sprites.size(); i++){
            if(sprites[i]->name && strcmp(name, sprites[i]->name) == 0)
                return sprites[i];
        }
        return NULL;
    }
};

#endif
