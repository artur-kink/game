#include "Entity.hpp"

Entity::Entity(){
    position = glm::vec2(0.0f);
}

Entity::Entity(int32_t sX, int32_t sY){
    position.x = sX;
    position.y = sY;
}

void Entity::update(){

}
