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

// CONSTRUCTOR Puzzle() //
Puzzle::Puzzle()
{
  std::srand(std::time(0));
  // int form = rand() % 4;
  int form = 0;
  switch (form)
  {
  case 0: // aa?bb=zz [+-__]
    // char s = (rand() % 2) ? '+' : '-';
    char s = '+';

    int mindbl{op(s, min(2), min(2))};
    int maxdbl{op(s, max(2), min(2))};
    int z{randrange(
        (mindbl > min(2)) ? mindbl : min(2),
        (maxdbl < max(2)) ? maxdbl : max(2))};
    UX::printi((mindbl > min(2)) ? mindbl : min(2));
    UX::printi((maxdbl < max(2)) ? maxdbl : max(2));
    UX::printi(z);

    int a{randrange(
        min(2),
        op(s, z, min(2), true))};
    UX::printi(min(2));
    UX::printi(op(s, z, min(2), true));
    UX::printi(a);
    op(s, z, min(2), true);
    min(2);

    int comp{op(s, z, min(2), true)};
    // UX::printi()

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
