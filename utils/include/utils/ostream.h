/**
 * @author      : Nikita Guzhva (nik_finger@mail.ru)
 * @file        : ostream
 * @created     : Monday Sep 20, 2021 19:57:11 MSK
 */

#ifndef OSTREAM_H
#define OSTREAM_H

#include <iostream>
#include <vector>


template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
  os << "{ ";
  for (size_t i = 0; i < v.size(); ++i) {
    if (i == v.size() - 1)
      os << v[i] << " }";
    else
      os << v[i] << ", ";
  }
  
  return os;
}


#endif /* end of include guard OSTREAM_H */

