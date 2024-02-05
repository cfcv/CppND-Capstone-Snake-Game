#ifndef FOOD_H
#define FOOD_H

#include<tuple>
#include "snake.h"
#include "SDL.h"

class Food {
    public:
        virtual void eatBy(Snake &s) = 0;
        bool checkCell(int x, int y);
        SDL_Point position;
};

class PoisonFood : public Food {
    public:
        void eatBy(Snake &s);

        static const std::tuple<int,int,int,int> color_rgba;
};

class NormalFood: public Food{
    public:
        void eatBy(Snake &s);

        static const std::tuple<int,int,int,int> color_rgba;
};

// class SuperFood : public Food {

// };

#endif