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
#define ALLOWED_CHARS "1234567890+-*/="

Game::Game(Puzzle *puzzle) : puzzle_{puzzle}, completedRounds_{0}
{
  this->rounds_.reserve(NUM_ROUNDS);
  for (int i = 0; i < NUM_ROUNDS; i++)
  {
    this->rounds_.push_back(Guess{});
  }

  std::vector<Guess::GuessChar> chars;
  for (auto c : ALLOWED_CHARS)
  {
    chars.push_back({c, Guess::unknown});
  }
  this->usedChars_ = Guess(chars.size());
  this->usedChars_.set(chars);

  for (int i = 0; i < NUM_ROUNDS; i++)
  {
    UX::beginRound(i + 1, this->rounds_, this->usedChars_);
    std::string guess{};
    int attempt{};
    while (true)
    {
      guess = UX::promptGuess(bool(attempt));
      if (Puzzle::verify(guess))
        break;
      attempt++;
    }
    this->rounds_.at(i) = this->puzzle_->compare(guess);
    auto newChars = this->usedChars_.getVector();
    for (auto &c : this->rounds_.at(i).getVector())
    {
      for (auto &c2 : newChars)
      {
        if (c2.character == c.character)
        {
          if (!(c2.state == Guess::correct || c2.state == Guess::nearby))
            c2.state = c.state;

          break;
        }
      }
    }
    // TODO clean all this up.
    // TODO actually check if a guess is fully correct
    this->usedChars_.set(newChars);
    // UX::printRound(this->rounds_);
  }

  // this->rounds_.at(0) = this->puzzle_->compare("8+43/=37");
  // this->rounds_.at(1) = this->puzzle_->compare(this->puzzle_->getAnswer());

  // UX::printRound(this->rounds_);
}
