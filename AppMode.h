// /////////////////////////////////////////////////////////
//
// File:   clerdle/AppMode.h
// Author: Michael Foster
// Date:   2022.04.29
//
// This is the header file for AppMode.cpp.
// See that file for more information.
//
// /////////////////////////////////////////////////////////

#ifndef APPMODE_H
#define APPMODE_H

#include <string>
#include <vector>

#include "StatsCollection.h"

class AppMode
{
private:
  bool test_;
  int generate_;
  bool stats_;
  std::string playerName_;

  bool quit_;

public:
  AppMode(const std::vector<std::string> &);

  bool executeSimpleModes(Stats &);

  bool isTest() const { return test_; }
  int isGenerate() const { return generate_; }
  bool isStats() const { return stats_; }
  std::string getPlayerName() const { return playerName_; }
};

#endif
