#include "game.h"
#include "food.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)),
      random_sleep(3, 8) {
}

Game::~Game(){
  std::cout << "Game destructor" << std::endl;
  this->snake.alive = false;
  std::cout << "snake condition: " << this->snake.alive << std::endl;
  std::cout << "destructor trying to lock:" << std::endl;
  std::unique_lock<std::mutex> uniq_lock(this->food_mutex);
  if(!this->normal_food.empty()){
    this->normal_food.erase(this->normal_food.begin());
    std::cout << "clear normal food" << std::endl;
  }
  else {
    std::cout << "normal food was already empty" << std::endl;
  }

  if(!this->poison_food.empty()){
    this->poison_food.erase(this->poison_food.begin());
    std::cout << "clear poison food" << std::endl;
  } 
  else {
    std::cout << "poison food was already cleared" << std::endl;
  }

  std::cout << "destructor trying to unlock" << std::endl;
  uniq_lock.unlock();
  std::cout << "destructor unlocked" << std::endl;
  this->_condition_normal_food.notify_all(); //notity all threads sleeping that the game is over
  this->_condition_poison_food.notify_all(); //notity all threads sleeping that the game is over
  for(std::thread &t: this->_threads){
    // std::cout << "join thread " << t.get_id() << std::endl;
    std::cout << "join thread " << std::endl;
    t.join();
    std::cout << "joined" << t.get_id() << std::endl;
  }
}

void Game::destroy_poison_foods(){
  std::cout << "create poison food destroyer thread"  << std::this_thread::get_id() << std::endl;
  while(true){
    // sleep for a random time
    int sleep_s = this->random_sleep(engine);
    std::cout << "sleeping for " << sleep_s << "s" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(sleep_s));
    std::cout << "poison food destroyer thread: try to lock " << std::this_thread::get_id() << std::endl;
    std::unique_lock<std::mutex> uniq_lock(this->food_mutex);
    if(!this->poison_food.empty()){
      this->poison_food.erase(this->poison_food.begin());
      this->_condition_poison_food.notify_one();
    } 

    if(!this->snake.alive){
      break;
    }  
  }
  std::cout << "Killing poison destroyer thread: " << std::this_thread::get_id() << std::endl;
}

void Game::create_poison_foods(){
  std::cout << "create poison thread"  << std::this_thread::get_id() << std::endl;
  while(true){
    std::cout << "poison thread: check if snake is alive " << std::this_thread::get_id() << std::endl;
    // if(!this->snake.alive){
    //   std::cout << "snake dead in poison thread " << std::this_thread::get_id() << std::endl;
    //   break;
    // }

    std::cout << "poison thread: try to lock " << std::this_thread::get_id() << std::endl;
    std::unique_lock<std::mutex> uniq_lock(this->food_mutex);
    this->_condition_poison_food.wait(uniq_lock, [this]{return poison_food.empty();});
    // wait until food is consumed and place another one
    // snake could be dead while we waited so recheck:
    if(!this->snake.alive){
      std::cout << "snake dead in poison thread 2 " << std::this_thread::get_id() << std::endl;
      break;      
    }
    int x, y;
    std::cout << "wake up, creating new poison food! " << std::this_thread::get_id() << std::endl;
    while (true) {
      x = random_w(engine);
      y = random_h(engine);
      // Check that the location is not occupied by a snake item before placing
      // food.
      if(!this->normal_food.empty() && !this->normal_food[0].checkCell(x,y)){
        if (!snake.SnakeCell(x, y)) {
          SDL_Point p;
          p.x = x;
          p.y = y;
          PoisonFood f;
          f.position = p;
          this->poison_food.push_back(f);
          break;
        }
      }
      if (!snake.SnakeCell(x, y)) {
        SDL_Point p;
        p.x = x;
        p.y = y;
        PoisonFood f;
        f.position = p;
        this->poison_food.push_back(f);
        break;
      }
    }
  }
  std::cout << "Killing poison thread: " << std::this_thread::get_id() << std::endl;
}

void Game::create_normal_foods(){
  std::cout << "created thread: " << std::this_thread::get_id() << std::endl;
  while(true){
    std::cout << "thread: check if snake is alive " << std::this_thread::get_id() << std::endl;
    // if(!this->snake.alive){
    //   std::cout << "snake dead in thread " << std::this_thread::get_id() << std::endl;
    //   break;
    // }

    std::cout << "thread: try to lock " << std::this_thread::get_id() << std::endl;
    std::unique_lock<std::mutex> uniq_lock(this->food_mutex);
    this->_condition_normal_food.wait(uniq_lock, [this]{return normal_food.empty();});
    // wait until food is consumed and place another one
    // snake could be dead while we waited so recheck:
    if(!this->snake.alive){
      std::cout << "snake dead in thread 2 " << std::this_thread::get_id() << std::endl;
      return;      
    }
    int x, y;
    std::cout << "wake up, creating new food! " << std::this_thread::get_id() << std::endl;
    while (true) {
      x = random_w(engine);
      y = random_h(engine);
      // Check that the location is not occupied by a snake item before placing
      // food.
      if (!snake.SnakeCell(x, y)) {
        SDL_Point p;
        p.x = x;
        p.y = y;
        NormalFood f;
        f.position = p;
        this->normal_food.push_back(f);
        break;
      }
    }
  }
  std::cout << "Killing thread: " << std::this_thread::get_id() << std::endl;
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  std::cout << "creating threads" << std::endl;
  this->_threads.emplace_back(std::thread(&Game::create_normal_foods, this));
  this->_threads.emplace_back(std::thread(&Game::create_poison_foods, this));
  this->_threads.emplace_back(std::thread(&Game::destroy_poison_foods, this));
  
  // lock to render foods (read from vectors and avoid data race)
  std::unique_lock<std::mutex> uniq_lock(this->food_mutex, std::defer_lock);
  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();
    uniq_lock.lock();
    renderer.Render(snake, this->normal_food, this->poison_food);
    uniq_lock.unlock();

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      this->normal_food[0].position.x = x;
      this->normal_food[0].position.y = y;
      return;
    }
  }
}

void Game::Update() {
  if (!snake.alive) return;
  // std::cout << "snake update" << std::endl;
  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // check normal food
  // std::cout << "try to lock inside update" <<  std::endl;
  std::lock_guard<std::mutex> lck(this->food_mutex);
  // std::cout << "lock inside update succeeded" <<  std::endl;
  if(!this->normal_food.empty()){
    NormalFood food = this->normal_food[0];

    // Check if there's food over here
    if (food.position.x == new_x && food.position.y == new_y) {
      score++;
      // remove food from vector and notify thread so it can wake up and create another food
      std::cout << "consuming food!" << std::endl;
      food.eatBy(snake);

      this->normal_food.erase(this->normal_food.begin());
      this->_condition_normal_food.notify_one();

    }
  }
  if(!this->poison_food.empty()){
    PoisonFood pfood = this->poison_food[0];

    // Check if there's food over here
    if (pfood.position.x == new_x && pfood.position.y == new_y) {
      score++;
      // remove food from vector and notify thread so it can wake up and create another food
      std::cout << "consuming poison food!" << std::endl;
      pfood.eatBy(snake);

      this->poison_food.erase(this->poison_food.begin());
      this->_condition_poison_food.notify_one();

    }
  }
  // std::cout << "lock update outside scope" << std::endl;
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }