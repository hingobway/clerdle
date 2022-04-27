// /////////////////////////////////////////////////////////
//
// File:   clerdle/Game.h
// Author: Michael Foster
// Date:   2022.04.29
//
// This is the header file for Game.cpp.
// See that file for more information.
//
// /////////////////////////////////////////////////////////

#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>

#include "Puzzle.h"
#include "Guess.h"

class Game
{

private:
  Puzzle *puzzle_;
  std::vector<Guess> rounds_;
  Guess usedChars_;

  int completedRounds_;
  bool won_;

  void play();

public:
  Game(Puzzle *);

  bool won() const { return won_; }
  int getRounds() const { return completedRounds_; }
};

#endif
