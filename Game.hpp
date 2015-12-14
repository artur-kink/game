#ifndef _GAME_HPP
#define _GAME_HPP

#include "GameTime.hpp"

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

class Game{
private:
    bool gameRunning;

    SDL_Window* sdlWindow;
    SDL_Renderer* sdlRenderer;
    SDL_Texture* tilesTexture;

    TTF_Font* font;


    uint32_t fpsCounter;
    uint32_t updateCounter;

public:

    Game();

    uint32_t init();

    void start();
    void run();
 
    void processEvents();
    void update();
    void draw();

    void cleanup();

};

#endif
