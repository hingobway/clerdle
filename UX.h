// /////////////////////////////////////////////////////////
//
// File:   clerdle/UX.h
// Author: Michael Foster
// Date:   2022.04.29
//
// This is the header file for UX.cpp.
// See that file for more information.
//
// /////////////////////////////////////////////////////////

#ifndef UX_H
#define UX_H

#include <string>

class UX
{
private:
  static void splash();

public:
  static void welcome();
  static void print(std::string);
  static void printi(int);
};

#endif
