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
        glm::vec2 direction(0.0f, 0.0f);
        if(keys[SDL_SCANCODE_UP] || keys[SDL_SCANCODE_W]){
            direction.y = -1.0f;
        }else if(keys[SDL_SCANCODE_DOWN] || keys[SDL_SCANCODE_S]){
            direction.y = 1.0f;
        }

        if(keys[SDL_SCANCODE_LEFT] || keys[SDL_SCANCODE_A]){
            direction.x = -1.0f;
        }else if(keys[SDL_SCANCODE_RIGHT] || keys[SDL_SCANCODE_D]){
            direction.x = 1.0f;
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

    Drawer::instance()->startDraw();

    int32_t startX = player->position.x - 512/2 + 16;
    int32_t startY = player->position.y - 384/2 + 16;

    if(startX < 0)
        startX = 0;
    if(startY < 0)
        startY = 0;

    if(startX > engine.map->width*TILE_SIZE - 512)
        startX = engine.map->width*TILE_SIZE - 512;
    if(startY > engine.map->height*TILE_SIZE - 384)
        startY = engine.map->height*TILE_SIZE - 384;

    Drawer::instance()->setOffset(-startX, -startY);

    uint32_t tileStartX = startX/TILE_SIZE;
    uint32_t tileStartY = startY/TILE_SIZE;
    uint32_t tileEndX = tileStartX + 512/TILE_SIZE + 1;
    uint32_t tileEndY = tileStartY + 384/TILE_SIZE + 1;

    if(tileEndX > engine.map->width)
        tileEndX = engine.map->width;
    if(tileEndY > engine.map->height)
        tileEndY = engine.map->height;

    int mouseTileX = (Controls::instance()->mouseX / 2 + startX) / TILE_SIZE;
    int mouseTileY = (Controls::instance()->mouseY / 2 + startY) / TILE_SIZE;

    for(uint32_t y = tileStartY; y < tileEndY; y++){
        for(uint32_t x = tileStartX; x < tileEndX; x++){
            Tile& tile =  engine.map->getTile(x, y);
            int32_t drawX = TILE_SIZE*x;
            int32_t drawY = TILE_SIZE*y;

            if(mouseTileY == y && mouseTileX == x){
                Drawer::instance()->drawTile(0, drawX, drawY);
            }else
                Drawer::instance()->drawTile(tile.layers[0], drawX, drawY);

            if(debug){
                char coords[20];
                sprintf(coords, "(%d,%d)", x,y);
                Drawer::instance()->drawText(coords, drawX+8, drawY+6); 
            }
        }
    }

    //Draw Entities
    for(uint32_t i = 0; i < engine.entities.size(); i++){
        Entity* entity = engine.entities.at(i);
        entity->draw();
    }

    char updatesString[20];
    sprintf(updatesString, "FPS: %d", fpsCounter);
    Drawer::instance()->drawText(updatesString, 1, 1); 
    sprintf(updatesString, "UPS: %d", updateCounter);
    Drawer::instance()->drawText(updatesString, 1, 14); 

    Drawer::instance()->finishDraw();
    SDL_Delay(1); 
}
