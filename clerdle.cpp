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
  std::string playerName{mode.getPlayerName()};

  UX::welcome(mode.isTest() ? "test" : ""); // print logo

  Stats stats{};
  if (mode.executeSimpleModes(stats)) // run non-game modes based on cli args
    return 0;

  if (!playerName.length())
    playerName = UX::promptPlayerName();
  UX::printPlayerName(playerName);

  Puzzle *puzzle{};
  bool playAgain{};
  do
  {
    puzzle = new Puzzle();
    Game game(puzzle, mode.isTest() ? Game::testMode : Game::null);

    stats.recordGame(playerName, game.won() ? game.getRounds() : 0);
    UX::printHistogram(playerName, stats.getPlayerStats(playerName));

    playAgain = UX::promptReplay();

    delete puzzle;
    puzzle = nullptr;
  } while (playAgain);

  return 0;
}
