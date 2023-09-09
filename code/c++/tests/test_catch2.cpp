#include <catch2/catch_test_macros.hpp>
#include <vector>

unsigned int Factorial(unsigned int number) {
  return number <= 1 ? number : Factorial(number - 1) * number;
}

TEST_CASE("Factorials are computed", "[factorial]") {
  REQUIRE(Factorial(1) == 1);
  REQUIRE(Factorial(2) == 2);
  REQUIRE(Factorial(3) == 6);
  REQUIRE(Factorial(10) == 3628800);
}

TEST_CASE("Factorials are computed2", "[factorial]") {
  REQUIRE(Factorial(1) == 1);
  REQUIRE(Factorial(2) == 2);
  REQUIRE(Factorial(3) == 6);
  REQUIRE(Factorial(10) == 3628800);
}

TEST_CASE("vectors can be sized and resized", "[vector]") {
  std::vector<int> v(5);

  REQUIRE(v.size() == 5);
  REQUIRE(v.capacity() >= 5);

  SECTION("resizing bigger changes size and capacity") {
    v.resize(10);

    REQUIRE(v.size() == 10);
    REQUIRE(v.capacity() >= 10);
  }
  SECTION("resizing smaller changes size but not capacity") {
    v.resize(0);

    REQUIRE(v.size() == 0);
    REQUIRE(v.capacity() >= 5);
  }
  SECTION("reserving bigger changes capacity but not size") {
    v.reserve(10);

    REQUIRE(v.size() == 5);
    REQUIRE(v.capacity() >= 10);
  }
  SECTION("reserving smaller does not change size or capacity") {
    v.reserve(0);

    REQUIRE(v.size() == 5);
    REQUIRE(v.capacity() >= 5);
  }
}