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
#include "Guess.h"

/* HARDGEN attempts
 *   the number of attempts to brute force "hard-gen" (3-term)
 *   problems before falling back to an algorithmic solution.
 *   Over testing of around 50,000 "hard-gen" generations, the favorite
 *   value was HGA=13, resulting in instantenous performance over 5000
 *   generations, and a 99% success rate.
 *
 *   see http://cpp-moon.s.h-n.me/HGA.png for the data.
 */
#define HARDGEN_ATTEMPTS 13

// percent chance of certain puzzle formats. the 1112 format gets the remainder /100.
#define CHANCE_222 35
#define CHANCE_123 55 // this format contains many sub-formats, so should occur more often

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
  Puzzle::seed();

  // create the puzzle and add it to the object's `answer_` member
  this->generateProblem();
}
Puzzle::Puzzle(std::string answer)
{
  Puzzle::seed();
  this->answer_ = answer;
}

/* generateProblem()
 *   this is the parent function for puzzle generation. note that
 *   throughout this class puzzle formats are referred to with a series
 *   of numbers, denoting the digit length for each term in the equation.
 *
 *   e.g. format 222 ==> aa+bb=zz (but not necessarily "+")
 */
void Puzzle::generateProblem()
{
  int form = rand() % 100;
  if (form < CHANCE_222)
  { // aa?bb=zz [+-]
    this->answer_ = eqnGenerate222();
  }
  else if (form >= CHANCE_222 && form < CHANCE_222 + CHANCE_123)
  { // a?bb=zzz [+*] (a or b first) -OR- zzz?a=bb [/-]
    this->answer_ = eqnGenerate123();
  }
  else
  { // a?b?c=zz [+-*/]
    std::string eqn{eqnGenerate1112()};
    if (eqn.length())
      this->answer_ = eqn;
    else
    { // these solutions are brute forced. If too many attempts failed, switch to a different method.
      this->answer_ = (rand() % 2) ? eqnGenerate123() : eqnGenerate222();
    }
  }
}

std::string Puzzle::eqnGenerate222()
{
  int la{2}, lb{2}, lz{2}; // digit (l)ength of each argument
  int a{}, b{}, z{};       // argument values

  // randomly choose an operator, aka (s)ign
  char s{};
  if (rand() % 2)
  {
    s = '+';

    // read about these custom math utilities at the very bottom of this file
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
  return this->answerToString(a, s, b, z);
}

std::string Puzzle::eqnGenerate123()
{
  int la{1}, lb{2}, lz{3}; // digit (l)ength of each argument
  int a{}, b{}, z{};       // argument values

  // randomly choose an operator, aka (s)ign
  char s{(rand() % 2) ? '+' : '*'};

  // read about these custom math utilities at the very bottom of this file
  a = randrange(op(inv(s), min(lz), max(lb)), max(la));
  b = randrange(op(inv(s), min(lz), a), max(lb));
  z = op(s, a, b);

  if (rand() % 2)
  { // forward case: use given operator, either + or *
    // this case is commutative, so occasionally flip a and b
    bool flip{bool(rand() % 2)};
    return this->answerToString(flip ? a : b,
                                s,
                                flip ? b : a,
                                z);
  }
  else
  { // reverse case: use inversed operator and reorder elements
    return this->answerToString(z, inv(s), a, b);
  }
}

// this generator uses brute force, and *can fail*. always check for blank response.
std::string Puzzle::eqnGenerate1112()
{
  std::vector<std::string> ops{"+", "-", "*", "/"};

  std::vector<std::string> equation{};
  std::string answer{};

  int attempts = 0;
  while (answer.length() != 2 && attempts < HARDGEN_ATTEMPTS)
  { // generate random equations until the desired answer length is found
    equation.clear();
    for (int i = 0; i < 3; i++)
    {
      equation.push_back(std::to_string(randrange(1, 9)));
      equation.push_back(ops.at(rand() % ops.size()));
    }
    equation.pop_back();

    auto iteqn = equation; // opIterate() is destructive to the passed vector
    answer = std::to_string(opIterate(iteqn));
    if (answer[0] == '-')
      answer = ""; // manually reject negative answers

    attempts++;
  }
  if (attempts >= HARDGEN_ATTEMPTS)
  { // stop trying attempts after a given number of tries
    return "";
  }

  std::string out{};
  for (auto s : equation)
  {
    out += s;
  }
  out += "=" + answer;
  return out;
}

/* verify()
 *   verifies that a passed equation actually computes as written.
 *   the passed string is split into a vector of terms and operators,
 *   then the opIterate() function solves the left side of the equation.
 */
bool Puzzle::verify(std::string guess)
{
  std::vector<std::string> elements;
  std::string nbuf{};

  for (char c : guess)
  {
    int tryint{c - '0'};
    if (tryint >= 0 && tryint <= 9)
    {
      nbuf += c;
    }
    else
    {
      elements.push_back(nbuf);
      nbuf = "";
      elements.push_back(std::string(1, c));
    }
  }
  if (!elements.size() || *(elements.end() - 1) != "=") // second to last term must be equals sign
    return false;
  elements.pop_back(); // remove equals sign

  // separate given answer and remove it from elements vector
  int givenAnswer{std::stoi(nbuf)};

  // run the recursive iteration function to find answer to provided calculation
  int computedAnswer{opIterate(elements)};

  return computedAnswer == givenAnswer;
}

/* opIterate()
 *   this is a recursive function that iterates over an equation in
 *   string vector form. the vector contains numbers and operators in
 *   order. the function will return the solution as an integer.
 */
int Puzzle::opIterate(std::vector<std::string> &elements, int stage)
{
  bool broke{false};
  for (int i = 0; i < int(elements.size()); i++)
  {
    std::string el = elements.at(i);

    if ((!stage && (el == "*" || el == "/")) || (stage && (el == "+" || el == "-")))
    { // look for the next operator in PEMDAS order
      int a{}, b{};
      try
      { // parse numbers around operator as integers
        a = std::stoi(elements.at(i - 1));
        b = std::stoi(elements.at(i + 1));
      }
      catch (std::invalid_argument const &err)
      { // if there were 2 operators in a row, immediately exit
        (void)err;
        elements.at(0) = "2147483647"; // max int value will always fail validation
        stage = 1;
        break;
      }
      catch (std::out_of_range const &err)
      { // if there were 2 operators in a row, immediately exit
        (void)err;
        elements.at(0) = "2147483647"; // max int value will always fail validation
        stage = 1;
        break;
      }

      if (el[0] == '/' && a % b)
      { // if any division doesn't result in an integer, immediately exit

        elements.at(0) = "2147483647"; // max int value will always fail validation
        stage = 1;
        break;
      }

      // evaluate this operator and replace it with its solution
      elements.at(i - 1) = std::to_string(op(el[0], a, b));
      for (int j = 0; j < 2; j++)
        elements.erase(elements.begin() + i);

      // if this has been successful we need to start from the beginning
      broke = true;
      break;
    }
  }

  if (!broke && stage) // the equation is solved
    return std::stoi(elements.at(0));
  if (!broke && !stage) // mult. & div. is complete. continue to add. & subt.
    return opIterate(elements, 1);
  return opIterate(elements, stage);
}

Guess Puzzle::compare(std::string input) const
{
  Guess guess(input);
  std::vector<char> nearbys;
  for (int i = 0; i < int(this->answer_.length()); i++)
  {
    if (i >= int(input.length())) // protect against length mismatch
      break;

    Guess::charState state{};
    if (input[i] == this->answer_[i])
    {
      state = Guess::correct;
      nearbys.push_back(input[i]);
    }
    else
    {
      bool found = false;
      for (auto c : this->answer_)
      {

        if (c == input[i])
        {
          int charCount{};
          for (auto n : nearbys)
            if (n == c)
              charCount++;
          if (charCount)
          {
            int actualCharCount{};
            for (auto n : this->answer_)
              if (n == c)
                actualCharCount++;
            if (charCount < actualCharCount)
            {
              found = true;
              nearbys.push_back(c);
              break;
            }
          }
          else
          {
            found = true;
            nearbys.push_back(c);
            break;
          }
        }
      }

      if (found)
      {
        state = Guess::nearby;
      }
      else
      {
        state = Guess::incorrect;
      }
    }
    guess.setInd(i, {0, state});
  }
  return guess;
}

/* answerToString()
 *   this function concats all elements except for the last, converting
 *   to strings along the way. The last element passed will be separated
 *   by an equals sign, allowing for a generic number of operators and
 *   arguments in the equation.
 */
template <typename T, typename... Next>
std::string Puzzle::answerToString(T element, Next... next)
{ // if there are more arguments left, add the current arg to stringstream and call again
  this->answerstream_ << element;
  return this->answerToString(next...);
}
template <typename T>
std::string Puzzle::answerToString(T answer)
{ // if this is the last element, concat this element after an equals sign, then output to a string
  this->answerstream_ << "=" << answer;
  std::string out{this->answerstream_.str()};
  this->answerstream_.str("");
  return out;
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
  // the decision was made to exclude the number 0, as many of the
  // associated puzzles feel "cheap", and not as fun.

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
