//! @author Nikita Guzhva (nik_finger@mail.ru)
//! @file   main.cpp
//! @date   26/08/2021

#ifndef __APPLE__
#  include <memory_resource>
#endif

#include <iostream>

int main()
{
#ifndef __APPLE__
  // do something
#else
  std::cout << "fuck you\n";
#endif

  return 0;
}

