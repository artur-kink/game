#include <iostream>

#include "Game.hpp"


Game::Game(){
    gameRunning = false;
}

/**
 * Initialize game
 */
uint32_t Game::init(){

    sdlWindow = NULL;
    sdlRenderer = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    sdlWindow = SDL_CreateWindow("Game", 100, 100, 1024, 768, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (sdlWindow == NULL){
        std::cout << "SDL_CreateWindow: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 2;
    }

    sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED);
    if (sdlRenderer == NULL){
        SDL_DestroyWindow(sdlWindow);
        std::cout << "SDL_CreateRenderer: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 3;
    }

    tilesTexture = IMG_LoadTexture(sdlRenderer, "tiles.png");
    if (tilesTexture == NULL){
        std::cout << "IMG_LoadTexture: " << SDL_GetError() << std::endl;
        return 4;
    }

    if(TTF_Init()){
        std::cout << "TTF_Init: " << SDL_GetError() << std::endl;
        return 5;
    }

    if(Drawer::instance()->init(sdlRenderer)){
        std::cout << "Drawer::init(): failed" << std::endl;
        return 6;
    }
    return 0;
}

void Game::cleanup(){

    Drawer::instance()->cleanup();

    std::cout << "Cleaning up\n";
    if(tilesTexture){
        SDL_DestroyTexture(tilesTexture);
    }

    if(sdlRenderer){
        SDL_DestroyRenderer(sdlRenderer);
        sdlRenderer = NULL; 
    }

    if(sdlWindow){
        SDL_DestroyWindow(sdlWindow);
        sdlWindow = NULL;
    }

    TTF_Quit();
    SDL_Quit();
    std::cout << "Cleanup done\n";
}

void Game::start(){
    std::cout << "Starting\n";
    gameRunning = true;
    run();
    std::cout << "Done run\n";
    cleanup();
}

void Game::stop(){
    std::cout << "Stopping" << std::endl;
    gameRunning = false;
}

void Game::run(){

    CarryTimer timer(*GameTime::instance());
    Timer fpsTimer(*GameTime::instance());

    updateCounter = 0;
    uint32_t currentUpdateCounter = 0;
    fpsCounter = 0;
    uint32_t currentFpsCounter = 0;

    std::cout << "Map time\n";
    map = new Map(100,100);
    std::cout << "Map time\n";
    while(gameRunning){
        GameTime::instance()->updateFrameTime();

        //Update at 60fps
        if(timer.resetOnElapsed(16)){
            currentUpdateCounter++;
            std::cout << "Update Time: " << GameTime::instance()->getTime() << std::endl;

            processEvents();

            update();
        }
        
        //Calculate fps and ups
        if(fpsTimer.resetOnElapsed(1000)){
            fpsCounter = currentFpsCounter;
            currentFpsCounter = 0;

            updateCounter = currentUpdateCounter;
            currentUpdateCounter = 0;

            std::cout << "FPS: " << fpsCounter << std::endl;
            std::cout << "UPS: " << updateCounter << std::endl;
        }
        currentFpsCounter++;
    
        //Draw
        draw();
    }
}

void Game::processEvents(){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_WINDOWEVENT:
                switch(event.window.event){
                    case SDL_WINDOWEVENT_CLOSE:
                    gameRunning = false;
                    break;
                }
                break; //Break window events
        }
    }
}

void Game::update(){
}

void Game::draw(){
    SDL_RenderClear(sdlRenderer);

    int x = 0;
    int y = 0;
    SDL_GetMouseState(&x, &y);
    
    for(int j = 0; j < map->height; j++){
        for(int i = 0; i < map->width; i++){
            SDL_Rect src;
            src.x = 64;
            src.y = 64;
            src.w = 64;
            src.h = 64;
    
            SDL_Rect dest;
            dest.x = 64*i + (j%2)*32;
            dest.y = j*16;
            dest.w = 64;
            dest.h = 64;
            SDL_RenderCopy(sdlRenderer, tilesTexture, &src, &dest);
        }
        
    }

    char updatesString[20];
    sprintf(updatesString, "FPS: %d", fpsCounter);
    Drawer::instance()->drawText(updatesString, 1, 1); 
    sprintf(updatesString, "UPS: %d", updateCounter);
    Drawer::instance()->drawText(updatesString, 1, 14); 

    SDL_RenderPresent(sdlRenderer);
    SDL_Delay(1); 
}
