//! @author Nikita Guzhva (nik_finger@mail.ru)
//! @file   main.cpp
//! @date   26/08/2021

#if defined(__GNUC__) && !defined(__clang__)
#  include <memory_resource>
#endif

#include <iostream>

int main()
{
#if defined(__GNUC__) && !defined(__clang__)
  // do something
#else
  std::cout << "fuck you\n";
#endif

  return 0;
}

