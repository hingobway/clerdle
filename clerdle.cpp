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
#include "Game.h"

int main(int argc, char *argv[])
{

  std::vector<std::string> args(argv + 1, argv + argc);
  AppMode mode(args);

  // print logo
  UX::welcome(mode.test() ? "test" : "");

  if (mode.generate())
  { // for -g mode, print some answers and exit
    for (int i = 0; i < mode.generate(); i++)
      UX::prints(Puzzle().getAnswer(), '(', i + 1, ')');
    return 0;
  }

  // create this puzzle
  // Puzzle *puzzle{new Puzzle("4+8*3=28")};
  // Puzzle *puzzle{new Puzzle("1*14-9=5")};
  Puzzle *puzzle{new Puzzle()};

  if (mode.test()) // in test mode, print the answer first
    UX::printTestAnswer(puzzle->getAnswer());

  // TODO should this go in a Game() default ctor?
  // get playername if needed
  std::string playerName{mode.playerName()};
  if (!playerName.length())
  {
    playerName = UX::promptPlayerName();
  }

  UX::prints("player name: ", playerName, "\n");

  Game game(puzzle);

  return 0;
}
