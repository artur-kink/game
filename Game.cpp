#include <iostream>

#include "Game.hpp"


Game::Game(){
    gameRunning = false;
    offsetX = 350;
    offsetY = 0;

    debug = false;

    //Enable glog logging
    FLAGS_log_dir = ".";
    FLAGS_logtostderr = true;
    google::InitGoogleLogging("game");
    LOG(INFO) << "Initialized logging\n";
}

/**
 * Initialize game
 */
uint32_t Game::init(){

    sdlWindow = NULL;
    sdlRenderer = NULL;

    LOG(INFO) << "Initializing SDL\n";
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        LOG(ERROR) << "SDL_Init Error: " << SDL_GetError() << "\n";
        return 1;
    }
    LOG(INFO) << "SDL Initialized\n";

    LOG(INFO) << "Creating Window\n";
    sdlWindow = SDL_CreateWindow("Game", 100, 100, 1024, 768, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (sdlWindow == NULL){
        LOG(ERROR) << "SDL_CreateWindow: " << SDL_GetError() << "\n";
        SDL_Quit();
        return 2;
    }
    LOG(INFO) << "Window Created\n";

    sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED);
    if (sdlRenderer == NULL){
        SDL_DestroyWindow(sdlWindow);
        LOG(ERROR) << "SDL_CreateRenderer: " << SDL_GetError() << "\n";
        SDL_Quit();
        return 3;
    }

    LOG(INFO) << "Initializing TTF\n";
    if(TTF_Init()){
        LOG(ERROR) << "TTF_Init: " << SDL_GetError() << "\n";
        return 5;
    }
    LOG(INFO) << "TTF Initialized\n";

    if(Drawer::instance()->init(sdlRenderer)){
        LOG(ERROR) << "Drawer::init(): failed" << "\n";
        return 6;
    }
    LOG(INFO) << "Initialized\n";
    return 0;
}

void Game::cleanup(){

    Drawer::instance()->cleanup();

    LOG(INFO) << "Cleaning up\n";

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
    LOG(INFO) << "Cleanup done\n";
}

void Game::start(){
    LOG(INFO) << "Starting\n";
    gameRunning = true;
    run();
    LOG(INFO) << "Done run\n";
    cleanup();
}

void Game::stop(){
    LOG(INFO) << "Stopping" << std::endl;
    gameRunning = false;
}

void Game::run(){

    CarryTimer timer(*GameTime::instance());
    Timer fpsTimer(*GameTime::instance());

    updateCounter = 0;
    uint32_t currentUpdateCounter = 0;
    fpsCounter = 0;
    uint32_t currentFpsCounter = 0;

    player = new PlayerEntity();
    engine.addEntity(player);
    engine.setPlayer(player);

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
    if(keys[SDL_SCANCODE_LSHIFT]){
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
    }else{
        uint8_t direction = 0;
        if(keys[SDL_SCANCODE_UP] || keys[SDL_SCANCODE_W]){
            direction = PlayerEntity::Up;
        }else if(keys[SDL_SCANCODE_DOWN] || keys[SDL_SCANCODE_S]){
            direction = PlayerEntity::Down;
        }

        if(keys[SDL_SCANCODE_LEFT] || keys[SDL_SCANCODE_A]){
            direction |= PlayerEntity::Left;
        }else if(keys[SDL_SCANCODE_RIGHT] || keys[SDL_SCANCODE_D]){
            direction |= PlayerEntity::Right;
        }
        
        ((PlayerEntity*)player)->setMoveDirection(direction);
    }

    if(keys[SDL_SCANCODE_SPACE]){
        ((PlayerEntity*)player)->performAction();
    }

    if(keys[SDL_SCANCODE_TAB])
        debug = !debug;

    engine.update();
}

void Game::draw(){
    SDL_RenderClear(sdlRenderer);

    for(uint32_t y = 0; y < engine.map->height; y++){
        for(uint32_t x = 0; x < engine.map->width; x++){
            Tile& tile =  engine.map->getTile(x, y);
            int32_t drawX = TILE_WIDTH*x + offsetX;
            int32_t drawY = TILE_HEIGHT*y + offsetY;
            Drawer::instance()->drawTile(tile.layers[0], drawX, drawY);

            if(debug){
                char coords[20];
                sprintf(coords, "(%d,%d)", x,y);
                Drawer::instance()->drawText(coords, drawX+8, drawY+6); 
            }
        }
    }

    //Draw Entities
    Drawer::instance()->setOffset(offsetX, offsetY);
    for(uint32_t i = 0; i < engine.entities.size(); i++){
        Entity* entity = engine.entities.at(i);
        entity->draw();
    }

    char updatesString[20];
    sprintf(updatesString, "FPS: %d", fpsCounter);
    Drawer::instance()->drawText(updatesString, 1, 1); 
    sprintf(updatesString, "UPS: %d", updateCounter);
    Drawer::instance()->drawText(updatesString, 1, 14); 

    SDL_RenderPresent(sdlRenderer);
    SDL_Delay(1); 
}
