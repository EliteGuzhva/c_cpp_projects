/**
 * @author      : Nikita Guzhva (nik_finger@mail.ru)
 * @file        : problem1
 * @created     : Monday Sep 20, 2021 19:30:30 MSK
 */

#ifndef PROBLEM1_H
#define PROBLEM1_H

#include <vector>
#include <unordered_map>


// Problem #1
// Return a union of two arrays
template<typename T>
std::vector<T> vectorUnion(const std::vector<T>& v1, const std::vector<T>& v2) {
  std::vector<T> result;
  result.reserve(std::min(v1.size(), v2.size()));

  using valueType = typename decltype(result)::value_type;
  using sizeType = typename decltype(result)::size_type;

  std::unordered_map<valueType, sizeType> tmpMap;

  for (auto& item : v1)
    tmpMap[item]++;

  for (auto& item : v2) {
    auto iter = tmpMap.find(item);
    if (iter != tmpMap.end() && (*iter).second > 0) {
      result.push_back(item);
      (*iter).second--;
    }
  }

  return result;
}



#endif /* end of include guard PROBLEM1_H */

