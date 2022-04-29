// /////////////////////////////////////////////////////////
//
// File:   clerdle/Player.cpp
// Author: Michael Foster
// Date:   2022.04.29
//
// The player class holds game history data for a
// particular player. This includes their name and games
// beaten in n number of rounds.
//
// /////////////////////////////////////////////////////////
#include "Player.h"
//---------------//

#include <string>
#include <map>

void Player::setHistory(const std::map<std::string, int> &history)
{
  this->history_ = history;
}
void Player::setOne(std::string id, int value)
{
  // if (this->history_.find(id) != this->history_.end())
  this->history_[id] = value;
}
