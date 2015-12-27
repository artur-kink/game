#ifndef _GAME_HPP
#define _GAME_HPP

#include "GameTime.hpp"
#include "Drawer.hpp"
#include "Controls.hpp"
#include "World.hpp"

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

class Game{
private:
    bool gameRunning;

    SDL_Window* sdlWindow;
    SDL_Renderer* sdlRenderer;
    SDL_Texture* tilesTexture;

    uint32_t fpsCounter;
    uint32_t updateCounter;


    World* world;

    int32_t offsetX, offsetY;

    bool debug;


    int32_t pX, pY;
public:

    Game();

    uint32_t init();

    void start();
    void run();
    void stop();
 
    void processEvents();
    void update();
    void draw();

    void cleanup();

    void getTile(int32_t x, int32_t y, int32_t& rx, int32_t& ry);
};

#endif
