// /////////////////////////////////////////////////////////
//
// File:   clerdle/UX.cpp
// Author: Michael Foster
// Date:   2022.04.29
//
// This class serves as a buffer for all user interactions.
// All formatting and text specifics will be handled in
// these functions.
//
// /////////////////////////////////////////////////////////
#include "UX.h"
//-----------//

#include <iostream>
#include <string>

#include "color.h"
#include "Guess.h"

void UX::welcome()
{
  UX::splash();
}
void UX::welcome(std::string mode)
{
  UX::splash(mode == "test");
}

std::string UX::colorMap(Guess::charState state)
{
  std::string out{};
  switch (state)
  {
  case Guess::empty:
    out = Color::setColor(Color::green, Color::black);
    break;
  case Guess::unknown:
    out = Color::setColor(Color::black, Color::white);
    break;
  case Guess::incorrect:
    out = Color::setColor(Color::white, Color::black);
    break;
  case Guess::nearby:
    out = Color::setColor(Color::white, Color::purple);
    break;
  case Guess::correct:
    out = Color::setColor(Color::black, Color::green);
    break;
  default:
    out = "";
  }
  return out;
}

//-----------------

void UX::printTestAnswer(std::string answer)
{
  std::cout << Color::setColor(Color::green, Color::black)
            << "CORRECT ANSWER:  "
            << Color::setColor(Color::white, Color::black)
            << answer << " "
            << Color::reset() << "\n\n";
}

std::string UX::promptPlayerName()
{
  std::string name{};
  while (true)
  {
    std::cout << "Please enter your name: ";
    std::getline(std::cin, name);
    if (name.length())
      break;

    std::cout << "Name can't be blank.\n";
  }
  return name;
}

void UX::beginRound(int round, const std::vector<Guess> &history, Guess usedChars)
{
  UX::print1("\nAttempt", round, "-");
  for (auto c : usedChars.getVector())
    std::cout << colorMap(c.state) << c.character;
  std::cout << Color::reset() << "\n\n";

  UX::printRound(history, 2);
}

std::string UX::promptGuess(bool showError)
{
  if (showError)
    UX::print("Guesses must compute.");

  std::string guess{};
  std::cout << "> ";
  std::getline(std::cin, guess);
  // TODO validate input
  return guess;
}
void UX::printRound(const std::vector<Guess> &rounds, int buffer)
{
  for (auto round : rounds)
  {
    for (int i = 0; i < buffer; i++)
      std::cout << " ";
    for (auto c : round.getVector())
    {
      std::cout << colorMap(c.state)
                << c.character;
    }
    std::cout << Color::reset() << "\n";
  }
  // std::cout << std::endl;
}

//-----------------

void UX::splash(bool test)
{
  std::cout << Color::setColor(Color::white, Color::green)
            << "                    ";
  if (test)
    std::cout << Color::setColor(Color::red, Color::white)
              << "TEST MODE";
  else
    std::cout << "         ";
  std::cout << Color::reset() << "\n"
            << Color::setColor(Color::white, Color::green)
            << "===  C  L  E  R  D  L  E  ===" << Color::reset() << "\n"
            << Color::setColor(Color::white, Color::green)
            << "                             " << Color::reset() << "\n"
            << Color::setColor(Color::green, Color::white)
            << "command-line nerdle.         " << Color::reset() << "\n"
            << std::endl;
}
