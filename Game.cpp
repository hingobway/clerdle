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

  this->play();

  // record stats here
}

void Game::play()
{
  UX::printGameStart(this->puzzle_->getAnswer().length());
  for (int i = 0; i < NUM_ROUNDS; i++)
  {
    std::string guess{};
    int attempt{};
    while (true)
    {
      guess = UX::promptGuess(bool(attempt));
      if (guess.length() == this->puzzle_->getAnswer().length() && Puzzle::verify(guess))
        break;
      attempt++;
    }
    this->rounds_.at(i) = this->puzzle_->compare(guess);
    auto newChars = this->usedChars_.getVector();
    int correctCount{};
    for (auto &c : this->rounds_.at(i).getVector())
    { // TODO clean this
      if (c.state == Guess::correct)
        correctCount++;
      for (auto &c2 : newChars)
      {
        if (c2.character == c.character)
        {
          if (c.state == Guess::correct || !(c2.state == Guess::correct || c2.state == Guess::nearby))
            c2.state = c.state;
          break;
        }
      }
    }
    this->usedChars_.set(newChars);
    this->won_ = correctCount == int(this->rounds_.at(i).getString().length());
    this->completedRounds_++;

    UX::printRound(i + 1, this->rounds_, this->usedChars_, this->won_ ? i : -1);
    if (this->won_)
      break;
  }
  if (!this->won_)
    UX::printLoss(this->puzzle_->getAnswer());
}
