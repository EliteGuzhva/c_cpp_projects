/**
 * @author      : Nikita Guzhva (nik_finger@mail.ru)
 * @file        : problem2
 * @created     : Monday Sep 20, 2021 20:17:42 MSK
 */

#ifndef PROBLEM2_H
#define PROBLEM2_H

#include <deque>
#include <vector>


// Problem #2
// array<int> (sorted!) -> array<int> squared (sorted!)
inline std::vector<int> sqrSorted(const std::vector<int>& v) {
  std::vector<int> result;
  result.reserve(v.size());

  if (v.empty())
    return {};

  size_t zeroBorder = -1;
  for (size_t i = 0; i < v.size(); ++i) {
    if (v[i] >= 0) {
      zeroBorder = i;
      break;
    }
  }

  if (zeroBorder == 0) {
    for (auto iter = v.begin(); iter != v.end(); ++iter)
      result.push_back((*iter) * (*iter));

    return result;
  }

  if (zeroBorder == -1) {
    for (auto iter = v.rbegin(); iter != v.rend(); ++iter)
      result.push_back((*iter) * (*iter));

    return result;
  }

  int leftIndex = zeroBorder - 1;
  int rightIndex = zeroBorder;

  while (leftIndex >= 0 || rightIndex < v.size()) {
    if (std::abs(v[leftIndex]) < v[rightIndex]) {
      result.push_back(v[leftIndex] * v[leftIndex]);
      leftIndex--;
    } else {
      result.push_back(v[rightIndex] * v[rightIndex]);
      rightIndex++;
    }
  }

  return result;
}


#endif /* end of include guard PROBLEM2_H */

