#include <catch2/catch.hpp>

static int fact(int number)
{
  return number <= 1 ? 1 : fact(number - 1);
}

TEST_CASE("fact(0) == 1)")
{
  REQUIRE(fact(0) == 1);
}

TEST_CASE("fact works for numbers greater than 1")
{
  REQUIRE(fact(0) == 1);
  REQUIRE(fact(2) == 2);
  REQUIRE(fact(3) == 6);
  REQUIRE(fact(10) == 3628800);
}
