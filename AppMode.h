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

class AppMode
{
private:
  bool test_;
  int generate_;
  std::string playerName_;

public:
  AppMode(const std::vector<std::string> &);

  bool isTest() const { return test_; }
  int isGenerate() const { return generate_; }
  std::string getPlayerName() const { return playerName_; }
};

#endif
