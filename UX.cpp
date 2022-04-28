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
void UX::printGameStart(int problemLength)
{
  std::cout << "Enter your first guess:\n  ";
  for (int i = 0; i < problemLength; i++)
    std::cout << ".";
  std::cout << "\n";
}
void UX::printRound(int round, const std::vector<Guess> &history, Guess usedChars, int won)
{
  UX::print1("\nGuess", round, "-");
  for (auto c : usedChars.getVector())
    std::cout << colorMap(c.state) << c.character;
  std::cout << Color::reset() << "\n\n";

  UX::printHistory(history, won, 2);
}

std::string UX::promptGuess(bool showError)
{
  if (showError)
    UX::print("Guesses must compute and be the correct length.");

  std::string guess{};
  std::cout << "> ";
  std::getline(std::cin, guess);
  // TODO validate input
  return guess;
}
void UX::printHistory(const std::vector<Guess> &rounds, int won, int buffer)
{
  for (int i = 0; i < int(rounds.size()); i++)
  {
    const Guess &round = rounds.at(i);
    for (int j = 0; j < buffer; j++)
      std::cout << " ";
    for (auto c : round.getVector())
    {
      std::cout << colorMap(c.state)
                << c.character;
    }
    std::cout << Color::reset()
              << ((i == won) ? UX::wonMsg() : "")
              << "\n";
  }
}
std::string UX::wonMsg()
{
  return Color::setFg(Color::green) + " << YOU WON!" + Color::reset();
}
void UX::printLoss(std::string answer)
{
  std::cout << "\n"
            << Color::setFg(Color::red)
            << "You lose! " << Color::reset()
            << "Solution: "
            << Color::setColor(Color::black, Color::white)
            << answer << Color::reset() << "\n\n";
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
