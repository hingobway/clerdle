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

#include "UX.h"
#include "Puzzle.h"

int main(int argc, char *argv[])
{
  std::vector<std::string> args(argv, argv + argc);
  (void)args; // TODO enable multiple modes

  UX::welcome();

  for (int i = 0; i < 15; i++)
  {
    Puzzle{};
  }

  return 0;
}
