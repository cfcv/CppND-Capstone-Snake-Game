#include "food.h"

const std::tuple<int,int,int,int> NormalFood::color_rgba = std::make_tuple(255,255,0,0);
const std::tuple<int,int,int,int> PoisonFood::color_rgba = std::make_tuple(255,0,0,0);

bool Food::checkCell(int x, int y){
    // Check if there is already a food in this cell
    if(this->position.x == x && this->position.y == y){
        return true;
    }
    return false;
}

void NormalFood::eatBy(Snake &s){
      // Grow snake and increase speed.
      s.GrowBody();
      s.speed += 0.02;
}

void PoisonFood::eatBy(Snake &s){
    // kills the snake
    s.alive = false;
}