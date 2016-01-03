#include <iostream>

#include "Game.hpp"


Game::Game(){
    gameRunning = false;
    offsetX = 350;
    offsetY = 0;

    debug = true;
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

    player = new Entity(0, 0);
    engine.addEntity(player);

    while(gameRunning){
        GameTime::instance()->updateFrameTime();

        //Update at 60fps
        if(timer.resetOnElapsed(16)){
            currentUpdateCounter++;
            //std::cout << "Update Time: " << GameTime::instance()->getTime() << std::endl;

            processEvents();

            update();
        }
        
        //Calculate fps and ups
        if(fpsTimer.resetOnElapsed(1000)){
            fpsCounter = currentFpsCounter;
            currentFpsCounter = 0;

            updateCounter = currentUpdateCounter;
            currentUpdateCounter = 0;

            //std::cout << "FPS: " << fpsCounter << std::endl;
            //std::cout << "UPS: " << updateCounter << std::endl;
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
    Controls::instance()->update();

    const uint8_t* keys = SDL_GetKeyboardState(NULL);
    if(keys[SDL_SCANCODE_UP] || keys[SDL_SCANCODE_W]){
        offsetY-=5;
    }else if(keys[SDL_SCANCODE_DOWN] || keys[SDL_SCANCODE_S]){
        offsetY+=5;
    }

    if(keys[SDL_SCANCODE_LEFT] || keys[SDL_SCANCODE_A]){
        offsetX-=5;
    }else if(keys[SDL_SCANCODE_RIGHT] || keys[SDL_SCANCODE_D]){
        offsetX+=5;
    }

    if(keys[SDL_SCANCODE_TAB])
        debug = !debug;

    int32_t tileX, tileY;
    getTile(Controls::instance()->mouseX, Controls::instance()->mouseY, tileX, tileY);
    if(Controls::instance()->wasMouseButtonClicked(Controls::MOUSE_LEFT)){
        player->x = tileX;
        player->y = tileY;
    }
}


void Game::getTile(int32_t x, int32_t y, int32_t& rx, int32_t& ry){
    // Mouse coords to tile coords from http://gamedev.stackexchange.com/questions/34787/how-to-convert-mouse-coordinates-to-isometric-indexes
    float multiplier = 1.0/(2.0*(float)TILE_WIDTH_HALF*(float)TILE_HEIGHT_HALF);
    rx = round((multiplier*((float)x * (float)TILE_HEIGHT_HALF + (float)y * (float)TILE_WIDTH_HALF + (-offsetX*TILE_HEIGHT_HALF - offsetY*TILE_WIDTH_HALF))));
    ry = round((multiplier*((float)x * (-(float)TILE_HEIGHT_HALF) + (float)y * (float)TILE_WIDTH_HALF + (offsetX*TILE_HEIGHT_HALF - offsetY*TILE_WIDTH_HALF))));
    rx--;
}

void Game::draw(){
    SDL_RenderClear(sdlRenderer);

    int32_t tileX, tileY;
    getTile(Controls::instance()->mouseX, Controls::instance()->mouseY, tileX, tileY);

    for(uint32_t y = 0; y < 12; y++){
        for(uint32_t x = 0; x < 12; x++){
            Tile& tile =  engine.world.getTile(x, y);
            SDL_Rect src;
            if(tileX == x && tileY == y){
                src.x = 128;
                src.y = 128;
                src.w = TILE_WIDTH;
                src.h = TILE_HEIGHT;
            }else{
                src.x = (tile.layers[0]%8)*64;
                src.y = (tile.layers[0]/8)*64;
                src.w = TILE_WIDTH;
                src.h = TILE_HEIGHT;
            }

            SDL_Rect dest;
            dest.x = TILE_WIDTH_HALF*x - (y*TILE_WIDTH_HALF) + offsetX;
            dest.y = y*TILE_HEIGHT_HALF + x*TILE_HEIGHT_HALF + offsetY;
            dest.w = TILE_WIDTH;
            dest.h = TILE_HEIGHT;
            SDL_RenderCopy(sdlRenderer, tilesTexture, &src, &dest);

            if(debug){
                char coords[20];
                sprintf(coords, "(%d,%d)", x,y);
                Drawer::instance()->drawText(coords, dest.x+8, dest.y+6); 
            }
        }
    }

    //Draw temp player
    SDL_Rect pSrc;
    pSrc.x = pSrc.y = 192;
    pSrc.w = TILE_WIDTH;
    pSrc.h = TILE_HEIGHT;
    SDL_Rect pDest;
    pDest.x = TILE_WIDTH_HALF*player->x - (player->y*TILE_WIDTH_HALF) + offsetX;
    pDest.y = player->y*TILE_HEIGHT_HALF + player->x*TILE_HEIGHT_HALF + offsetY;
    pDest.w = TILE_WIDTH;
    pDest.h = TILE_HEIGHT;
    SDL_RenderCopy(sdlRenderer, tilesTexture, &pSrc, &pDest);


    char updatesString[20];
    sprintf(updatesString, "FPS: %d", fpsCounter);
    Drawer::instance()->drawText(updatesString, 1, 1); 
    sprintf(updatesString, "UPS: %d", updateCounter);
    Drawer::instance()->drawText(updatesString, 1, 14); 

    if(debug){
        char mousePos[20];
        sprintf(mousePos, "%d,%d -> %d,%d", Controls::instance()->mouseX, Controls::instance()->mouseY, tileX, tileY);
        Drawer::instance()->drawText(mousePos, 1, 28);
    }

    SDL_RenderPresent(sdlRenderer);
    SDL_Delay(1); 
}
