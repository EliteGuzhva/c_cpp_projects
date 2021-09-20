/**
 * @author      : Nikita Guzhva (nik_finger@mail.ru)
 * @file        : main
 * @created     : Saturday Sep 18, 2021 22:36:42 MSK
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <utils/utils.h>

#include "problem1.h"
#include "problem2.h"

using namespace std;


TEST_CASE("Problem #1") {
  printTitle("Problem #1: Array union");

  vector<int> v1 = {1, 2, 3, 4, 3, 5};
  vector<int> v2 = {3, 4, 6, 5, 1};
  vector<int> expected = {3, 4, 5, 1};
  vector<int> got = vectorUnion(v1, v2);

  printNamedVariable("Vector 1", v1);
  printNamedVariable("Vector 2", v2);
  printSeparator();
  printGotExpected(got, expected);

  REQUIRE(expected == got);
}

TEST_CASE("Problem #2") {
  printTitle("Problem #2: Square sorted array");

  vector<int> v = {-9, -7, -2, 0, 1, 3, 5};
  vector<int> expected = {0, 1, 4, 9, 25, 49, 81};
  vector<int> got = sqrSorted(v);

  printNamedVariable("Vector", v);
  printSeparator();
  printGotExpected(got, expected);

  REQUIRE(expected == got);
}

