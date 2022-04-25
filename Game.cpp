// /////////////////////////////////////////////////////////
//
// File:   clerdle/Game.cpp
// Author: Michael Foster
// Date:   2022.04.29
//
// This class contains game logic.
//
// /////////////////////////////////////////////////////////
#include "Game.h"
//-------------//

#include <vector>
#include <string>

#include "UX.h"
#include "Guess.h"
#include "Puzzle.h"

#define NUM_ROUNDS 6

Game::Game(Puzzle *puzzle)
{

  this->puzzle_ = puzzle;

  this->rounds_.reserve(NUM_ROUNDS);
  for (int i = 0; i < NUM_ROUNDS; i++)
  {
    this->rounds_.push_back(Guess{});
  }

  // TODO look at this case in puzzle::verify!! nonsensical equations will break it or get erronius responses.
  this->rounds_.at(0) = this->puzzle_->compare("8+43/=37");
  this->rounds_.at(1) = this->puzzle_->compare(this->puzzle_->getAnswer());

  UX::printRound(this->rounds_);
}
