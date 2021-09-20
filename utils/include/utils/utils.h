/**
 * @author      : Nikita Guzhva (nik_finger@mail.ru)
 * @file        : utils
 * @created     : Monday Sep 20, 2021 19:20:38 MSK
 */

#ifndef UTILS_H
#define UTILS_H

#include <iostream>

#include "ostream.h"


inline void printSeparator(char s = '-', int length = 30) {
  for (int i = 0; i < length; ++i)
    std::cout << s;
  std::cout << '\n';
}

inline void printTitle(std::string_view title) {
  std::cout << '\n';
  printSeparator('=');
  std::cout << "- " << title << " -\n\n";
}

template<typename T>
void printNamedVariable(std::string_view name, const T& var) {
  std::cout << name << ":\n" << var << std::endl;
}

template<typename T>
void printGotExpected(const T& got, const T& expected) {
  printNamedVariable("Got", got);
  printNamedVariable("Expected", expected);
}


#endif /* end of include guard UTILS_H */

