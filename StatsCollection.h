// /////////////////////////////////////////////////////////
//
// File:   clerdle/StatsCollection.h
// Author: Michael Foster
// Date:   2022.04.29
//
// This is the header file for StatsCollection.cpp.
// See that file for more information.
//
// /////////////////////////////////////////////////////////

#ifndef STATSCOLLECT_H
#define STATSCOLLECT_H

#include <vector>
#include <fstream>

#include "Player.h"

class Stats
{
private:
  const std::vector<std::string> HEADER_MAP;
  std::ofstream fileout_;

  std::vector<Player> players_;
  Player &findPlayer(std::string);

public:
  Stats();
  ~Stats();

  void recordGame(std::string, int);
  std::vector<int> getPlayerStats(std::string);
};

#endif
