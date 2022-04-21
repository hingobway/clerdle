// /////////////////////////////////////////////////////////
//
// File:   clerdle/Puzzle.h
// Author: Michael Foster
// Date:   2022.04.29
//
// This is the header file for Puzzle.cpp.
// See that file for more information.
//
// /////////////////////////////////////////////////////////

#ifndef PUZZLE_H
#define PUZZLE_H

#include <string>

class Puzzle
{
private:
  std::string answer_;
  static void seed();

  static int randrange(int a, int b) { return rand() % (1 + b - a) + a; }
  static int op(char, int, int, bool = false);
  static int min(int);
  static int max(int);

public:
  Puzzle();
};

#endif
