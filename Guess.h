// /////////////////////////////////////////////////////////
//
// File:   clerdle/Guess.h
// Author: Michael Foster
// Date:   2022.04.29
//
// This is the header file for Guess.cpp.
// See that file for more information.
//
// /////////////////////////////////////////////////////////

#ifndef GUESS_H
#define GUESS_H

#include <vector>
#include <string>

#define PUZZLE_LENGTH 8

class Guess
{
public:
  enum charState
  {
    null,      // no data - use default/old value
    empty,     // no char assigned yet
    unknown,   // unguessed char (usedChars only)
    incorrect, // no match at all
    nearby,    // right char, wrong place
    correct    // right char, right place
  };

  struct GuessChar
  {
    char character;
    charState state;
  };

  Guess(int length = PUZZLE_LENGTH);
  Guess(std::string, int length = PUZZLE_LENGTH);

  std::string getString() const;
  std::vector<GuessChar> getVector() const;

  void setInd(int, GuessChar);
  void set(const std::vector<GuessChar> &);

private:
  std::vector<GuessChar> guess_;
};

#endif
