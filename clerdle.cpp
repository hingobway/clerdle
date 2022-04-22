// /////////////////////////////////////////////////////////
//
// File:   clerdle/clerdle.cpp
// Author: Michael Foster
// Date:   2022.04.29
//
// A command line port of the game Nerdle [nerdlegame.com].
// Guess the random arithmetic equation in 6 guesses or
// less.
//
// This is the program entrypoint.
//
// /////////////////////////////////////////////////////////

#include <vector>
#include <string>

#include "AppMode.h"
#include "UX.h"
#include "Puzzle.h"

int main(int argc, char *argv[])
{

  std::vector<std::string> args(argv + 1, argv + argc);
  auto mode{AppMode(args)};

  UX::welcome(mode.test() ? "test" : "");

  if (mode.generate())
  { // for -g mode, print some answers and exit
    for (int i = 0; i < mode.generate(); i++)
      UX::prints(Puzzle().getAnswer(), '(', i + 1, ')');
    return 0;
  }

  // create this puzzle
  auto puzzle{Puzzle()};

  if (mode.test())
    UX::printTestAnswer(puzzle.getAnswer());

  return 0;
}
