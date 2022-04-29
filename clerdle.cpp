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

#include <iostream>

#include "AppMode.h"
#include "UX.h"
#include "Puzzle.h"
#include "Game.h"
#include "StatsCollection.h"

int main(int argc, char *argv[])
{
  std::vector<std::string> args(argv + 1, argv + argc);
  AppMode mode(args);

  // print logo
  UX::welcome(mode.isTest() ? "test" : "");

  Stats stats{};

  if (mode.isGenerate())
  { // for -g mode, print some answers and exit
    for (int i = 0; i < mode.isGenerate(); i++)
      UX::prints(Puzzle().getAnswer(), '(', i + 1, ')');
    return 0;
  }

  // TODO should this go in a Game() default ctor?
  // get playername if needed
  std::string playerName{mode.getPlayerName()};
  if (!playerName.length())
    playerName = UX::promptPlayerName();
  UX::prints("player name: ", playerName, "\n");

  Puzzle *puzzle{};
  bool playAgain{};
  do
  {
    puzzle = new Puzzle();

    if (mode.isTest()) // in test mode, print the answer first
      UX::printTestAnswer(puzzle->getAnswer());

    Game game(puzzle);
    UX::print("before recording");
    stats.recordGame(playerName, game.won() ? game.getRounds() : 0);
    UX::print("after recording");
    // UX::printHistogram(playerName, stats.getPlayerStats(playerName));

    playAgain = UX::promptReplay();

    delete puzzle;
    puzzle = nullptr;

    UX::print("puzzle deleted");
  } while (playAgain);

  return 0;
}
