// TODO header block
#include "Guess.h"
//--------------//

#include <vector>
#include <string>

#define EMPTY_CHAR '.'

Guess::Guess(int length)
{
  this->guess_.reserve(length);
  for (int i = 0; i < length; i++)
  {
    this->guess_.push_back({EMPTY_CHAR, charState::empty});
  }
}
Guess::Guess(std::string input, int length)
{
  this->guess_.reserve(length);
  for (int i = 0; i < length; i++)
  {
    if (int(input.length()) >= i)
      input += EMPTY_CHAR; // protect against string length mismatch
    this->guess_.push_back({input[i], charState::empty});
  }
}

void Guess::setInd(int index, GuessChar guesschar)
{
  if (index < int(this->guess_.size()))
  {
    // allow the option to only set state OR character
    if (guesschar.state == charState::null)
      guesschar.state = this->guess_.at(index).state;
    if (guesschar.character == 0)
      guesschar.character = this->guess_.at(index).character;
    this->guess_.at(index) = guesschar;
  }
}
void Guess::set(const std::vector<GuessChar> &guess)
{
  int itlen = (guess.size() < this->guess_.size()) ? guess.size() : this->guess_.size();
  for (int i = 0; i < itlen; i++)
  {
    this->guess_.at(i) = guess.at(i);
  }
}

std::vector<Guess::GuessChar> Guess::getVector() const
{
  return this->guess_;
}
std::string Guess::getString() const
{
  std::string out{};
  for (const GuessChar &c : this->guess_)
  {
    out += c.character;
  }
  return out;
}
