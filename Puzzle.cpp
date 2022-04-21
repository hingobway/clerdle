// /////////////////////////////////////////////////////////
//
// File:   clerdle/Puzzle.cpp
// Author: Michael Foster
// Date:   2022.04.29
//
// This file generates and tracks a new puzzle.
//
// /////////////////////////////////////////////////////////
#include "puzzle.h"
//---------------//

#include <cstdlib>
#include <ctime>
#include <string>
#include <stdexcept>

#include <iostream>

#include "UX.h"

void Puzzle::seed()
{
  static bool done = false;
  if (!done)
  {
    std::srand(std::time(0));
    done = true;
  }
}

// CONSTRUCTOR Puzzle() //
Puzzle::Puzzle()
{
  // int form = rand() % 4;
  int form = 0;
  switch (form)
  {
  case 0: // aa?bb=zz [+-__]
    char s{};
    if (rand() % 2)
    {
      s = '+';
      int z{randrange(min(2) + min(2), max(2))};
      int a{randrange(min(2), z - min(2))};
      int b{z - a};
      this->answer_ = std::to_string(a) + s + std::to_string(b) + "=" + std::to_string(z);
    }
    else
    {
      s = '-';
      int z{randrange(min(2), max(2) - min(2))};
      int a{randrange(z + min(2), max(2))};
      int b{a - z};
      this->answer_ = std::to_string(a) + s + std::to_string(b) + "=" + std::to_string(z);
    }
    break;
    // case 1: // a?bb=zzz [+_*_] [x or y first]
    //   //
    //   break;
    // case 2: // aaa?b=zz [_-_/]
    //   //
    //   break;
    // case 3: // a?b?c=zz [+-*/]
    //   //
    //   break;
  }
  UX::print(this->answer_);
}

int Puzzle::op(char op, int a, int b, bool invert)
{
  int out{};
  switch (op)
  {
  case '+':
    out = (!invert) ? a + b : a - b;
    break;
  case '-':
    out = (!invert) ? a - b : a + b;
    break;
  case '*':
    out = (!invert) ? a * b : a / b;
    break;
  case '/':
    out = (!invert) ? a / b : a * b;
    break;
  }
  return out;
}
int Puzzle::min(int digits)
{
  if (!digits)
    return 0;
  std::string num{"1"};
  for (int i = 1; i < digits; i++)
  {
    num += "0";
  }
  return std::stoi(num);
}
int Puzzle::max(int digits)
{
  if (!digits)
    return 0;
  std::string num{};
  for (int i = 0; i < digits; i++)
  {
    num += "9";
  }
  return std::stoi(num);
}
