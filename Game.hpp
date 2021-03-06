#ifndef _GAME_HPP
#define _GAME_HPP

#include "GameTime.hpp"
#include "Graphics/Drawer.hpp"
#include "Controls.hpp"
#include "GameEngine/GameEngine.hpp"

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

#include "glog/logging.h"

class Game{
private:
    bool gameRunning;

    SDL_Window* sdlWindow;
    SDL_Renderer* sdlRenderer;

    uint32_t fpsCounter;
    uint32_t updateCounter;

    int32_t offsetX, offsetY;

    bool debug;


    GameEngine engine;
    Entity* player;
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
};

#endif
