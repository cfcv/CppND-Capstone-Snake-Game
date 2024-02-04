#include "user.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

std::string User::getName(){
    return this->name;
}

std::string User::getScore(){
    return this->score;
}

int User::getScoreInt(){
    return std::stoi(this->score);
}

void User::setScore(std::string new_score){
    this->score = new_score;
}

// user namespace functions
User* user::getUserFromFile(const std::string &user_name){
  std::cout << "searching username: " << user_name << std::endl;
  std::ifstream best_scores_file("../data/best_scores.txt");

  std::string name, score;
  while(best_scores_file >> name >> score){
    if(name == user_name){
      best_scores_file.close();
      return new User(name, score);
    }
  }

  // User not found, close file and return null
  best_scores_file.close();
  return nullptr;
}

User* user::createNewUser(const std::string &user_name){
  std::cout << "Creating username: " << user_name << std::endl;
  std::ofstream best_scores_file;
  best_scores_file.open("../data/best_scores.txt", std::ios_base::app); // append instead of overwriting

  std::string initial_score = "0";

  best_scores_file << user_name << " " << initial_score << "\n";
  best_scores_file.close();

  return new User(user_name, initial_score);
}

void user::WriteScore(User &&current_user){
  std::fstream best_scores_file("../data/best_scores.txt");

  std::vector<std::string> lines;
  std::string line, name;
  int score;
  while(getline(best_scores_file, line)){
    std::stringstream strIn(line);
    strIn >> name >> score;

    if(name == current_user.getName() && current_user.getScoreInt() > score){
      std::cout << "New maximum score reached: " << current_user.getScore() << " (previous: " << score << ")" << std::endl;
      lines.push_back(current_user.getName() + " " + current_user.getScore());
    } else {
      lines.push_back(line);
    }
  }

  // rewrite the file
  best_scores_file.close();
  std::ofstream new_scores_file("../data/best_scores.txt");
  for(std::string& line : lines){
    new_scores_file << line << "\n";
  }
  new_scores_file.close();
}