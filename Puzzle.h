// /////////////////////////////////////////////////////////
//
// File:   clerdle/Puzzle.h
// Author: Michael Foster
// Date:   2022.04.29
//
// This is the header file for Puzzle.cpp.
// See that file for more information.
//
// /////////////////////////////////////////////////////////

#ifndef PUZZLE_H
#define PUZZLE_H

#include <string>
#include <sstream>
#include <vector>

#include "Guess.h"

class Puzzle
{
private:
  std::string answer_;
  std::stringstream answerstream_;
  template <typename T>
  std::string answerToString(T);
  template <typename T, typename... Next>
  std::string answerToString(T, Next...);

  void generateProblem();
  std::string eqnGenerate222();
  std::string eqnGenerate123();
  std::string eqnGenerate1112();

  static void seed();

  static int randrange(int a, int b) { return rand() % (1 + b - a) + a; }
  static int op(char, int, int);
  static char inv(char);
  static int min(int);
  static int max(int);

  static int opIterate(std::vector<std::string> &, int = 0);

public:
  Puzzle();
  Puzzle(std::string);

  std::string getAnswer() const { return answer_; }
  Guess compare(std::string) const;

  static bool verify(std::string);
};

#endif
