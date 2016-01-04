#include "Action.hpp"

MoveAction::MoveAction(uint16_t e, int32_t x, int32_t y){
    actionId = ACTION_MOVE;
    entity = e;
    this->x = x;
    this->y = y;
}
