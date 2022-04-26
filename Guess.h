// TODO header block

#ifndef GUESSCHAR_H
#define GUESSCHAR_H

#include <vector>
#include <string>

#define PUZZLE_LENGTH 8

class Guess
{
public:
  enum charState
  {
    null,
    empty,
    unknown,
    incorrect,
    nearby,
    correct
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

////////////////////////////
// NON-OOP FORM OPTION \/ //

#if 0
namespace
{
  enum charState
  {
    empty,
    unknown,
    incorrect,
    nearby,
    correct
  };

  struct GuessChar
  {
    char character;
    charState state;
  };
}
#endif