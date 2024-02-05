#ifndef GAME_H
#define GAME_H

#include <random>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <thread>
#include "food.h"
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  ~Game();
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

  void create_normal_foods();
  void create_poison_foods();
  void destroy_poison_foods();

 private:
  Snake snake;
  std::vector<NormalFood> normal_food;
  std::vector<PoisonFood> poison_food;

  std::vector<std::thread> _threads;
  std::mutex food_mutex;
  std::condition_variable _condition_normal_food;
  std::condition_variable _condition_poison_food;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;
  std::uniform_int_distribution<int> random_sleep;

  int score{0};

  void Update();
};

#endif