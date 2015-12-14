#include "GameTime.hpp"

GameTime* GameTime::time = NULL;

GameTime::GameTime(){
    updateFrameTime();
}

GameTime* GameTime::instance(){
    if(time == NULL){
        time = new GameTime();
    }
    return time;
}

void GameTime::updateFrameTime(){
    frameTime = getSystemTime();
}

uint64_t GameTime::getSystemTime(){
    return (uint64_t)SDL_GetTicks();
}

uint64_t GameTime::getTime(){
    return frameTime;
}
