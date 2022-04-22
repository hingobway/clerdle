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
#include <cmath>
#include <string>
#include <sstream>
#include <vector>

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
  seed();

  // int form = rand() % 3;
  int form = rand() % 2;
  // int form = 1;
  switch (form)
  {
  case 0: // aa?bb=zz [+-]
  {
    int la{2}, lb{2}, lz{2}; // digit (l)ength of each argument
    int a{}, b{}, z{};       // argument values

    char s{};
    if (rand() % 2)
    {
      s = '+';
      z = randrange(min(la) + min(lb), max(lz));
      a = randrange(min(la), z - min(lb));
      b = z - a;
    }
    else
    {
      s = '-';
      z = randrange(min(lz), max(la) - min(lb));
      a = randrange(z + min(lb), max(la));
      b = a - z;
    }
    this->setAnswer(a, s, b, z);
  }
  break;
  case 1: // a?bb=zzz [+*] (a or b first) -OR- zzz?a=bb [/-]
  {
    int la{1}, lb{2}, lz{3}; // digit (l)ength of each argument
    int a{}, b{}, z{};       // argument values

    char s{(rand() % 2) ? '+' : '*'};

    a = randrange(op(inv(s), min(lz), max(lb)), max(la));
    b = randrange(op(inv(s), min(lz), a), max(lb));
    z = op(s, a, b);

    if (rand() % 2)
    { // forward case: use given operator, either + or *
      // this case is commutative, so occasionally flip a and b
      bool flip{bool(rand() % 2)};
      this->setAnswer(flip ? a : b,
                      s,
                      flip ? b : a,
                      z);
    }
    else
    { // reverse case: use inversed operator and reorder elements
      this->setAnswer(z, inv(s), a, b);
    }
  }
  break;
  case 2: // a?b?c=zz [+-*/]
  {
    //
  }
  break;
  }
}

/* setAnswer()
 *   this function concats all elements except for the last, converting to strings along
 *   the way. The last element passed will be separated by an equals sign, allowing for a
 *   generic number of operators and arguments in the equation.
 */
template <typename T, typename... Next>
void Puzzle::setAnswer(T element, Next... next)
{ // if there are more arguments left, add the current arg to stringstream and call again
  this->answerstream_ << element;
  this->setAnswer(next...);
}
template <typename T>
void Puzzle::setAnswer(T answer)
{ // if this is the last element, concat this element after an equals sign, then output to a string
  this->answerstream_ << "=" << answer;
  this->answer_ = this->answerstream_.str();
  this->answerstream_.str("");

  // DEBUG ONLY
  UX::print("answer set: " + this->answer_);
}

/*   \/ MATH UTILITIES BEGIN HERE \/   */

int Puzzle::op(char op, int a, int b)
{ // do math operation based on passed operator
  int out{};
  switch (op)
  {
  case '+':
    out = a + b;
    break;
  case '-':
    out = a - b;
    break;
  case '*':
    out = a * b;
    break;
  case '/':
    out = int(std::ceil(double(a) / double(b)));
    break;
  }
  return out;
}
char Puzzle::inv(char op)
{ // returns the inverse operator of the given operator
  char out{};
  switch (op)
  {
  case '+':
    out = '-';
    break;
  case '-':
    out = '+';
    break;
  case '*':
    out = '/';
    break;
  case '/':
    out = '*';
    break;
  }
  return out;
}

int Puzzle::min(int digits)
{ // finds the minimum value for an x-digit number
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
{ // finds the maximum value for an x-digit number
  if (!digits)
    return 0;
  std::string num{};
  for (int i = 0; i < digits; i++)
  {
    num += "9";
  }
  return std::stoi(num);
}
