#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "user.h"

int main() {
  constexpr std::size_t kFramesPerSecond{100};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  // ----- Read/create user -----
  std::string user_name;
  std::cout << "User name: ";
  std::cin >> user_name;

  User* current_user = user::getUserFromFile(user_name);

  if(current_user == nullptr){
    std::string choice; 
    std::cout << "user didn't found, do you want to create a new user for: " << user_name << "? [Y/N]" << std::endl;
    std::cin >> choice;
    if(choice == "Y"){
      current_user = user::createNewUser(user_name);
    }
    else if(choice == "N"){
      return 0;
    }
    else {
      std::cout << "choice should be Y or N, received: " << choice << std::endl;
      std::cout << "terminating the program" << std::endl;
      return 0;
    }
  }
  else {
    std::cout << "user found! Name: " << current_user->getName() << " Max score:" << current_user->getScore() << std::endl;
  }
  // ------------------------------

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);
  game.Run(controller, renderer, kMsPerFrame);
  int game_score = game.GetScore();
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game_score << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";

  current_user->setScore(std::to_string(game_score));
  user::WriteScore(std::move(*current_user));
  return 0;
}