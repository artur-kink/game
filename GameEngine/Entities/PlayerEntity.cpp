#include "PlayerEntity.hpp"

PlayerEntity::PlayerEntity():Entity(0, 0){
    width = 24;
    height = 24;

}

void PlayerEntity::update(){
    if(direction != MoveDirection::None){
        if(direction & MoveDirection::Up){
            if(y-1 >= 0 && !GameEngine::instance()->world.getTile(x/32, (y-1)/32).isBlocked() &&
               !GameEngine::instance()->world.getTile((x+width)/32, (y-1)/32).isBlocked()){
                y--;
            }
        }else if(direction & MoveDirection::Down){
            if(y+1 < 11*32 && !GameEngine::instance()->world.getTile(x/32, (y+1+height)/32).isBlocked() &&
               !GameEngine::instance()->world.getTile((x+width)/32, (y+1+height)/32).isBlocked()){
                y++;
            }
        }

        if(direction & MoveDirection::Left){
            if(x-1 >= 0 && !GameEngine::instance()->world.getTile((x-1)/32,y/32).isBlocked() &&
               !GameEngine::instance()->world.getTile((x-1)/32, (y+height)/32).isBlocked()){
                x--;
            }
        }else if(direction & MoveDirection::Right){
            if(x+1 < 11*32 && !GameEngine::instance()->world.getTile((x+1+width)/32,y/32).isBlocked() &&
               !GameEngine::instance()->world.getTile((x+1+width)/32, (y+height)/32).isBlocked()){
                x++;
            }
        }
    }
}

void PlayerEntity::setMoveDirection(uint8_t dir){
    direction = dir;
}
