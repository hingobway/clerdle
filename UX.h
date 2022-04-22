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
#include <iostream>

class UX
{
private:
  static void splash(bool = false);

public:
  static void welcome();
  static void welcome(std::string);

  static void printTestAnswer(std::string);

  template <typename T>
  static void print(T el) { std::cout << el << "\n"; }
  template <typename T>
  static void prints(T el) { std::cout << el << "\n"; }
  template <typename T>
  static void print1(T el) { std::cout << el << " "; };
  template <typename T, typename... Next>
  static void print(T, Next...);
  template <typename T, typename... Next>
  static void prints(T, Next...);
  template <typename T, typename... Next>
  static void print1(T, Next...);
};

template <typename T, typename... Next>
void UX::print(T el, Next... n)
{
  std::cout << el << "\n";
  print(n...);
}
template <typename T, typename... Next>
void UX::prints(T el, Next... n)
{
  std::cout << el << " ";
  prints(n...);
}
template <typename T, typename... Next>
void UX::print1(T el, Next... n)
{
  std::cout << el << " ";
  print1(n...);
}

#endif
