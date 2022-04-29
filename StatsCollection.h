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

#include "Player.h"

class Stats
{
private:
  std::vector<Player> players_;

public:
  Stats();
};

#endif
