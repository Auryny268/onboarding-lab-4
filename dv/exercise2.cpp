#include <catch2/catch_test_macros.hpp>
#include <VExercise2.h>
#include <cstdint>

void step(VExercise2& model) {
  model.clk = 1;
  model.eval();
  model.clk = 0;
  model.eval();
}

void check_init(uint16_t init) {
  VExercise2 model;
  model.reset = 1;
  model.init = init;
  step(model);
  REQUIRE(model.out == ((~model.init) & 0xFFFF));
  model.reset = 0;
  for (int i = 0; i < 10000; ++i) {
    uint16_t taps = model.out & 0x50A;
    uint16_t expected = (model.out << 1) | (std::popcount(taps) & 1);
    step(model);
    REQUIRE(model.out == expected);
  }
}

TEST_CASE("Exercise 2") {
  VExercise2 model;
  check_init(0x11);
  check_init(0x55);
  check_init(0x99);
  check_init(0xDD);
  check_init(0xFF);
}
