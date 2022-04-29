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
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>

#include "color.h"
#include "Guess.h"

#define HISTOGRAM_WIDTH 50

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

bool UX::promptReplay()
{
  std::cout << "\nPlay again? [y/N]  ";
  std::string input{};
  std::getline(std::cin, input);
  if (input.length() && (input[0] == 'y' || input[0] == 'Y'))
  {
    std::cout << "\n";
    return true;
  }
  return false;
}

//-----------------

void UX::printHistogram(std::string name, std::vector<int> data)
{
  if (!data.size())
    return;

  int total{};
  for (int i : data)
    total += i;
  if (!total)
    return;

  std::stringstream buffer;
  buffer << std::fixed << std::setw(3);
  buffer << "Player:         " << name << "\n";
  buffer << "Games Won:      " << total - data.at(0) << "/" << total;
  UX::streamSingleBar(buffer, total - data.at(0), total);
  for (int i = 1; i < int(data.size()); i++)
  {
    buffer << "Won in " << i << ((i == 1) ? "try:  " : "tries:")
           << data.at(i) << "/" << total;
    UX::streamSingleBar(buffer, data.at(i), total);
  }
  buffer << "\n";
  std::cout << buffer.str();
}
void UX::streamSingleBar(std::stringstream &stream, int x, int total)
{
  double ratio = double(x) / double(total);
  std::string percent = std::to_string((int)std::round(ratio * 100.0)) + "%";

  stream << "    ";
  for (int i = 0; i < HISTOGRAM_WIDTH; i++)
  {
    if (double(i) / double(HISTOGRAM_WIDTH) < ratio)
    {
      stream << Color::setColor(Color::black, Color::green);
    }
    if (i < int(percent.length()))
    {
      stream << percent.at(i);
    }
    else
    {
      stream << " ";
    }
    stream << Color::reset() << "\n";
  }
}

void UX::printCSVParseError()
{
  std::cout << "WARNING: some imported player data values were invalid and have been reset to 0. "
            << "Exit now (Ctrl+C) to avoid overwriting your data file.\n\n";
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
