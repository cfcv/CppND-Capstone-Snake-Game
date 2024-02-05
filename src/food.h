#ifndef FOOD_H
#define FOOD_H

#include<string>
#include "snake.h"
#include "SDL.h"

// class Food {
//     public:
//         virtual void EatBy(Snake s) = 0;
//         std::string color;
//         SDL_Point position;
// };

// class Poison : public Food {

// };

class NormalFood{
    public:
        // NormalFood();
        // void EatBy(Snake s);

        std::string color;
        SDL_Point position;
};

// class SuperFood : public Food {

// };

#endif