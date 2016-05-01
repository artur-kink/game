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

    if(movingDirection != glm::vec2(0.0f)){
        if(movingDirection.y == -1.0f){
            if(position.y-1 >= 0 && !GameEngine::instance()->map->getPointTile(position.x, (position.y-1)).isBlocked() &&
               !GameEngine::instance()->map->getPointTile((position.x+width), (position.y-1)).isBlocked()){
                position.y--;
            }
        }else if(movingDirection.y == 1.0f){
            if(position.y+1 < GameEngine::instance()->map->height*TILE_SIZE && !GameEngine::instance()->map->getPointTile(position.x, (position.y+1+height)).isBlocked() &&
               !GameEngine::instance()->map->getPointTile((position.x+width), (position.y+1+height)).isBlocked()){
                position.y++;
            }
        }

        if(movingDirection.x == -1.0f){
            if(position.x-1 >= 0 && !GameEngine::instance()->map->getPointTile((position.x-1),position.y).isBlocked() &&
               !GameEngine::instance()->map->getPointTile((position.x-1), (position.y+height)).isBlocked()){
                position.x--;
            }
        }else if(movingDirection.x == 1.0f){
            if(position.x+1 < GameEngine::instance()->map->width*TILE_SIZE && !GameEngine::instance()->map->getPointTile((position.x+1+width),position.y).isBlocked() &&
               !GameEngine::instance()->map->getPointTile((position.x+1+width), (position.y+height)).isBlocked()){
                position.x++;
            }
        }
    }

    if(inAction && actionTimer.hasElapsed(600)){
        inAction = false;
        if(GameEngine::instance()->map->getPointTile(position.x, position.y).isArable()){
            GameEngine::instance()->map->getPointTile(position.x, position.y).setPlowed();
        }
    }

}

void PlayerEntity::setMoveDirection(glm::vec2 dir){
    if(dir != glm::vec2(0.0f)){
        if(dir.x == -1.0f)
            direction = MoveDirection::Left;
        else if(dir.x == 1.0f)
            direction = MoveDirection::Right;
        else if(dir.y == -1.0f)
            direction = MoveDirection::Up;
        else if(dir.y == 1.0f)
            direction = MoveDirection::Down;
    }

    if (inAction == false && movingDirection != dir){
        movingDirection = dir;
        animationFrame = 0;
        animationTimer.reset();
    }
}

void PlayerEntity::performAction(){
    setMoveDirection(glm::vec2(0.0f, 0.0f));
    inAction = true;
    animationTimer.reset();
    animationFrame = 0;
    actionTimer.reset();
}

void PlayerEntity::draw(){

    SpriteSet* characterSet = static_cast<SpriteSet*>(Drawer::instance()->getSprite("character"));
    if(movingDirection != glm::vec2(0.0f) || inAction){
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
    Drawer::instance()->drawSprite(static_cast<Sprite*>(drawSet->sprites[animationFrame]), position.x, position.y);
}
