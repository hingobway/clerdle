// /////////////////////////////////////////////////////////
//
// File:   clerdle/Player.h
// Author: Michael Foster
// Date:   2022.04.29
//
// This is the header file for Player.cpp.
// See that file for more information.
//
// /////////////////////////////////////////////////////////

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <map>

class Player
{
private:
  std::string name_;
  std::map<std::string, int> history_;

public:
  Player() : name_{}, history_{} {}

  std::string getName() const { return name_; }
  std::map<std::string, int> getHistory() const { return history_; }

  void setName(std::string name) { name_ = name; }
  void setHistory(const std::map<std::string, int> &);
  void setOne(std::string, int);
};

#endif
