#include "DummyEnemy.hpp"

DummyEnemy::DummyEnemy():Entity(0,0){

}

void DummyEnemy::turn(){
    // Follow player
    GameEngine* engine = GameEngine::instance();

    Entity * player = engine->getPlayer();
    
    int32_t my, mx = 0;
    if (player->x > x)
        mx = 1;
    else if(player->x < x)
        mx = -1;

    if (player->y > y)
        my = 1;
    else if(player->y < y)
        my = -1;

    MoveAction* action = new MoveAction(entityId, this->x + mx, this->y + my);
    engine->addAction(action);
}
