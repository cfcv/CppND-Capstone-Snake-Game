#ifndef USER_H
#define USER_H

#include <string>


class User {
  public: 
    // Constructor
    User(std::string n, std::string s): name(n), score(s) {};
    
    // Getters and setters
    std::string getName();
    std::string getScore();
    int getScoreInt();

    void setScore(std::string new_score);

  private:
    std::string name;
    std::string score; 
};

namespace user {
    User* getUserFromFile(const std::string &user_name);
    User* createNewUser(const std::string &user_name);
    void WriteScore(User &&current_user);
}
#endif