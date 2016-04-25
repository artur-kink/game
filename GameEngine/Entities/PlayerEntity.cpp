#include "PlayerEntity.hpp"

PlayerEntity::PlayerEntity():Entity(0, 0),animationTimer(*GameTime::instance()){
    width = 24;
    height = 24;
    direction = MoveDirection::Down;
}

void PlayerEntity::update(){
    if(movingDirection != MoveDirection::None){
        if(movingDirection & MoveDirection::Up){
            if(y-1 >= 0 && !GameEngine::instance()->map->getPointTile(x, (y-1)).isBlocked() &&
               !GameEngine::instance()->map->getPointTile((x+width), (y-1)).isBlocked()){
                y--;
            }
        }else if(movingDirection & MoveDirection::Down){
            if(y+1 < GameEngine::instance()->map->height*TILE_WIDTH && !GameEngine::instance()->map->getPointTile(x, (y+1+height)).isBlocked() &&
               !GameEngine::instance()->map->getPointTile((x+width), (y+1+height)).isBlocked()){
                y++;
            }
        }

        if(movingDirection & MoveDirection::Left){
            if(x-1 >= 0 && !GameEngine::instance()->map->getPointTile((x-1),y).isBlocked() &&
               !GameEngine::instance()->map->getPointTile((x-1), (y+height)).isBlocked()){
                x--;
            }
        }else if(movingDirection & MoveDirection::Right){
            if(x+1 < GameEngine::instance()->map->width*TILE_HEIGHT && !GameEngine::instance()->map->getPointTile((x+1+width),y).isBlocked() &&
               !GameEngine::instance()->map->getPointTile((x+1+width), (y+height)).isBlocked()){
                x++;
            }
        }
    }
}

void PlayerEntity::setMoveDirection(uint8_t dir){
    if(dir != None)
        direction = dir;
    if (movingDirection != dir){
        movingDirection = dir;
        animationFrame = 0;
        animationTimer.reset();
    }
}

void PlayerEntity::performAction(){
    if(GameEngine::instance()->map->getPointTile(x, y).isArable()){
        GameEngine::instance()->map->getPointTile(x, y).setPlowed();
    }
}

void PlayerEntity::draw(){

    if(movingDirection != MoveDirection::None){
        if(animationTimer.hasElapsed(200)){
            animationTimer.reset();
            animationFrame++;
            if(animationFrame > 2)
                animationFrame = 0;
        }
    }

    if(direction & MoveDirection::Up)
        Drawer::instance()->drawSprite(2 + animationFrame*10, x, y);
    else if(direction & MoveDirection::Left || direction & MoveDirection::Right)
        Drawer::instance()->drawSprite(1 + animationFrame*10, x, y);
    else if(direction & MoveDirection::Down)
        Drawer::instance()->drawSprite(0 + animationFrame*10, x, y);
}
