#include "PlayerEntity.hpp"

PlayerEntity::PlayerEntity():Entity(0, 0),
    animationTimer(*GameTime::instance()),
    animationFrame(0),
    inAction(false),
    actionTimer(*GameTime::instance()){
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

    if(inAction && actionTimer.hasElapsed(600)){
        inAction = false;
        if(GameEngine::instance()->map->getPointTile(x, y).isArable()){
            GameEngine::instance()->map->getPointTile(x, y).setPlowed();
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
    inAction = true;
    animationTimer.reset();
    animationFrame = 0;
    actionTimer.reset();
}

void PlayerEntity::draw(){

    SpriteSet* characterSet = static_cast<SpriteSet*>(Drawer::instance()->getSprite("character"));
    if(movingDirection != MoveDirection::None || inAction){
        if(animationTimer.hasElapsed(200)){
            animationTimer.reset();
            animationFrame++;
            if(animationFrame > 2)
                animationFrame = 0;
        }
    }


    SpriteSet* drawSet = NULL;
    if(inAction){
        if(direction & MoveDirection::Up)
            drawSet = (SpriteSet*)characterSet->getSprite("action_up");
        else if(direction & MoveDirection::Left || direction & MoveDirection::Right)
            drawSet = (SpriteSet*)characterSet->getSprite("action_left");
        else if(direction & MoveDirection::Down)
            drawSet = (SpriteSet*)characterSet->getSprite("action_down");
    }else{
        if(direction & MoveDirection::Up)
            drawSet = (SpriteSet*)characterSet->getSprite("walk_up");
        else if(direction & MoveDirection::Left || direction & MoveDirection::Right)
            drawSet = (SpriteSet*)characterSet->getSprite("walk_left");
        else if(direction & MoveDirection::Down)
            drawSet = (SpriteSet*)characterSet->getSprite("walk_down");
    }
    Drawer::instance()->drawSprite(static_cast<Sprite*>(drawSet->sprites[animationFrame]), x, y);
}
